#include <iostream>
#include <fstream>
#include <string>
#include "./test.pb.h"

using namespace std;

void PromptForAddress(test::Person* person) {
    cout << "input person ID " << endl;
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');
    cout << "input person Name " << endl;
    string name;
    getline(cin, name);
    person->set_name(name);
    cout << "input person Email " << endl;
    string email;
    getline(cin, email);
    if (!email.empty())
        person->set_email(email);

    while(true) {
        cout << "input a phone number" <<endl;
        string number;
        getline(cin, number);
        if (number.empty())
            return;
        test::Person::PhoneNumber* phone_number = person->add_phone();
        phone_number->set_number(number);
        cout << "select form mobile/home/work" <<endl;
        string type; 
        getline(cin, type);
        if (type == "home")
            phone_number->set_type(test::Person::HOME);
        else if (type == "work")
            phone_number->set_type(test::Person::WORK);
        else if (type == "mobile")
            phone_number->set_type(test::Person::MOBILE);
    }
}

int main(int argc, char* argv[]) {
    test::AddressBook address_book;
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
        cerr << "has no file, create it." << endl;
    }else if (!address_book.ParseFromIstream(&input)) {
        cerr << "invalid address book database" << endl;
        return -1;
    }
    PromptForAddress(address_book.add_person());
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!address_book.SerializeToOstream(&output)) {
        cerr << "Failed to write to file." << endl;
    }
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
