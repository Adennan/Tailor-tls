#include <iostream>
#include "clientHello.h"
#include "types.h"
#include "proto.h"

using namespace tailor;

ClientHello::ClientHello()
{
    std::srand(int(time(0)));
    this->random.resize(32, 0);
    for (auto& c : this->random) 
    {
        c = std::rand() % 256;
    }
}

size_t ClientHello::serialize(std::basic_ostringstream<uint8_t>& sstr)
{
    size_t len = 0;
    size_t ret = 0;
    
    // encode version
    ret += encode(sstr, this->version);
    
    // encode random
    if (this->random.size() != 32)
    {
        throw std::bad_exception();
    }
    sstr.write(this->random.data(), this->random.size());
    ret += this->random.size();
    
    // encode session
    len = this->session.size();
    if (len > 32)
    {
        throw std::out_of_range("session id out of range");
    }
    ret += encode(sstr, static_cast<uint8_t>(len));
    sstr.write(this->session.data(), this->session.size());
    ret += this->session.size();
    
    // encode cipherSuites
    len = this->cipherSuites.size();
    if (len * 2 < 1)
    {
        throw std::bad_exception();
    }
    ret += encode(sstr, static_cast<uint16_t>(len * 2));
    for (auto c : this->cipherSuites)
    {
        ret += encode(sstr, c);
    }

    // encode timestamp
    ret += encode(sstr, this->timestamp);
    
    // encode extensions
    len = 0;
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

void ClientHello::deserialize(std::basic_istringstream<uint8_t>& sstr) 
{
    int len = 0;

    // decode version
    this->version = decode<uint16_t>(sstr);

    // decode random
    this->random.resize(32, 0);
    sstr.read(const_cast<uint8_t *>(this->random.data()), this->random.size());
    
    // decode session
    len = decode<uint8_t>(sstr);
    this->session.resize(len);
    sstr.read(const_cast<uint8_t *>(this->session.data()), this->session.size());

    // decode cipher suites
    len = decode<uint16_t>(sstr);
    this->cipherSuites.resize(len / 2);
    for (auto& c : this->cipherSuites)
    {
        c = decode<CipherSuite>(sstr);
    }

    // decode timestamp
    this->timestamp = decode<uint32_t>(sstr);

    // decode extensions
    this->extensions.clear();
    len = decode<Extension>(sstr);
    while (len > 0)
    {
        Extension extension;
        extension.deserialize(sstr);
        len -= extension.size();

        this->extensions.push_back(extension);
    }
}

size_t ClientHello::size() const
{
    size_t ret = sizeof(uint16_t) 
                + 32
                + 1
                + this->session.size()
                + 2
                + this->cipherSuites.size() * sizeof(uint16_t)
                + 1
                + sizeof(uint32_t)
                + 2;
    for (auto& c : this->extensions)
    {
        ret += c.size();
    }
    return ret;
}