#ifndef RECORD_H
#define RECORD_H

#include <iostream>
using namespace std;

// TLS Record Content Type
const static uint16_t RecordHeaderLen = 5;
const static uint16_t RecordMaxBodySize = 65535;  // Maybe the simple logic to 4096 or less than this number
const static uint8_t RecordChangeCipherSuite = 0x14;
const static uint8_t RecordAlert = 0x15;
const static uint8_t RecordHandshake = 0x16;
const static uint8_t RecordApplicationData = 0x17;
const static uint8_t RecordShortLinkHandshake = 0x19; // only used in short link first package

namespace tailor {
    class Record {
    public:
        uint8_t contentType;
        uint16_t version;
        uint16_t length;
        std::basic_string<uint8_t> body;

    public:
        virtual size_t serialize(std::basic_ostringstream<uint8_t>&) = 0;
        virtual void deserialize(std::basic_istringstream<uint8_t>&) = 0;
    };
};

#endif // RECORD_H