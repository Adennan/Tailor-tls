#include "encryptedExtension.h"
#include "proto.h"

using namespace tailor;

size_t EncryptedExtension::serialize(std::basic_ostringstream<uint8_t>& sstr)
{
    size_t ret = 0;

    // encode extension
    size_t len = 0;
    for (auto c : this->extensions) 
    { 
        len += c.size(); 
    }
    ret += encode(sstr, static_cast<uint16_t>(len));
    for (auto c : this->extensions)
    { 
        ret += c.serialize(sstr); 
    }

    return ret;
}

void EncryptedExtension::deserialize(std::basic_istringstream<uint8_t>& sstr)
{
    // decode extension
    this->extensions.clear();
    int len = decode<uint16_t>(sstr);
    while (len > 0) {
        Extension ext;
        ext.deserialize(sstr);
        this->extensions.push_back(ext);

        len -= ext.size();
    }
}

size_t EncryptedExtension::size() const
{
    size_t ret = 2;

    for (auto& c : this->extensions) 
    { 
        ret += c.size(); 
    }

    return ret;
}