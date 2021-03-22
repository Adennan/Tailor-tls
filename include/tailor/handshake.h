#ifndef HANDSHAKE_H
#define HANDSHAKE_H

#include <iostream>
#include <sstream>
#include <cstdint>
#include "types.h"
#include "record.h"

namespace tailor {
    class Handshake : public Record {
    public:
        virtual HandshakeType getType() const = 0;
        virtual size_t serialize(std::basic_ostringstream<uint8_t>&) = 0;
        virtual void deserialize(std::basic_istringstream<uint8_t>&) = 0;
        virtual size_t size() const = 0;
    };
}

#endif // HANDSHAKE_H