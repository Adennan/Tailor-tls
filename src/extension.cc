#include "extension.h"
#include "proto.h"

using namespace tailor;

size_t Extension::serialize(std::basic_ostringstream<uint8_t>& sstr) 
{
    size_t ret = 0;

    // encode type
    ret += encode(sstr, this->type);

    // encode data
    size_t len = this->data.size();
    ret += encode(sstr, static_cast<uint16_t>(len));
    sstr.write(this->data.data(), this->data.size());
    ret += this->data.size();

    return ret;
}

void Extension::deserialize(std::basic_istringstream<uint8_t>& sstr) 
{
    // decode type
    this->type = decode<ExtensionType>(sstr);

    // decode data
    size_t len = decode<uint16_t>(sstr);
    this->data.resize(len);
    sstr.read(const_cast<uint8_t *>(this->data.data()), this->data.size());
}

size_t Extension::size() const 
{
    return sizeof(ExtensionType) + 2 + this->data.size();
}