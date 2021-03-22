#include "record.h"
#include "proto.h"

using namespace tailor;

size_t Record::serialize(std::basic_ostringstream<uint8_t>& sstr) 
{
    size_t ret = 0;

    // encode contentType
    ret += encode(sstr, this->contentType);

    // encode version
    ret += encode(sstr, this->version);

    // encode length
    ret += encode(sstr, this->length);

    // encode body
    size_t len = this->body.size();
    ret += encode(sstr, static_cast<uint16_t>(len));
    sstr.write(this->body.data(), this->body.size());
    ret += this->body.size();

    return ret;
}

void Record::deserialize(std::basic_istringstream<uint8_t>& sstr) 
{
    // decode contentType
    this->type = decode<uint8_t>(sstr);

    // decode version
    this->version = decode<uint16_t>(sstr);

    // decode length
    this->length = decode<uint16_t>(sstr);

    // decode body
    size_t len = decode<uint16_t>(sstr);
    this->body.resize(len);
    sstr.read(const_cast<uint8_t *>(this->body.data()), this->body.size());
}