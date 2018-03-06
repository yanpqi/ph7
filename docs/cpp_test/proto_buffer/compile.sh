#!/bin/bash
protoc -I=./ --cpp_out=./ ./test.proto
g++ -o wr address_book_reader.cc test.pb.cc test.pb.h `pkg-config --cflags --libs protobuf`
g++ -o wr address_book_writer.cc test.pb.cc test.pb.h `pkg-config --cflags --libs protobuf`
