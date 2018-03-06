#include <iostream>
#include <fstream>
#include <string>
#include "./test.pb.h"

using namespace std;

void ListPeople(const test::AddressBook& book) {
    for(int i=0; i< book.person_size(); i++) {
        const test::Person& person = book.person(i);
        cout << "ID " << person.id() << endl;
        cout << "Name " << person.name() << endl;
        if (person.has_email())
            cout << "Email " << person.email() << endl;
        for(int j=0; j<person.phone_size(); j++) {
            const test::Person::PhoneNumber& number = person.phone(j);
            switch(number.type()) {
                case test::Person::MOBILE:
                    cout << "Mobile Phone: ";
                    break;
                case test::Person::WORK:
                    cout << "Work Phone: ";
                    break;
                case test::Person::HOME:
                    cout << "Home Phone: ";
                    break;
            }
            cout << number.number() << endl;
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {

    test::AddressBook address_book;
    fstream input(argv[1], ios::in | ios::binary);
    if (!address_book.ParseFromIstream(&input)) {
        cerr << "invalid address book database" << endl;
        return -1;
    }
    ListPeople(address_book);
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
