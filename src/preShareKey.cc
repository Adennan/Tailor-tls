#include "preShareKey.h"

using namespace tailor;

size_t PreShareKey::serialize(std::basic_ostringstream<uint8_t>& sstr)
{
    size_t ret = 0;
    size_t len = 0;

    // encode type
    ret += encode(sstr, this->type);

    // encode ticketLifeTimeHint
    ret += encode(sstr, this->ticketLifeTimeHint);

    // encode macValue
    size_t len = this->macValue.size();
    ret += encode(sstr, static_cast<uint16_t>(len));
    sstr.write(this->macValue.data(), this->macValue.size());
    ret += this->macValue.size();

    // encode keyVersion
    ret += encode(sstr, this->keyVersion);

    // encode iv
    size_t len = this->iv.size();
    ret += encode(sstr, static_cast<uint16_t>(len));
    sstr.write(this->iv.data(), this->iv.size());
    ret += this->iv.size();

    // encode encryptedTicket
    size_t len = this->encryptedTicket.size();
    ret += encode(sstr, static_cast<uint16_t>(len));
    sstr.write(this->encryptedTicket.data(), this->encryptedTicket.size());
    ret += this->encryptedTicket.size();

    return ret;
}

void PreShareKey::deserialize(std::basic_istringstream<uint8_t>& sstr)
{
    // decode type
    this->type = decode<uint8_t>(sstr);

    // decode ticketLifeTimeHint
    this->ticketLifeTimeHint = decode<uint32_t>(sstr);

    // decode macValue
    size_t len = decode<uint16_t>(sstr);
    this->macValue.resize(len);
    sstr.read(const_cast<uint8_t *>(this->macValue.data()), this->macValue.size());

    // decode keyVersion
    this->keyVersion = decode<uint32_t>(sstr);

    // decode iv
    size_t len = decode<uint16_t>(sstr);
    this->iv.resize(len);
    sstr.read(const_cast<uint8_t *>(this->iv.data()), this->iv.size());

    // decode encryptedTicket
    size_t len = decode<uint16_t>(sstr);
    this->encryptedTicket.resize(len);
    sstr.read(const_cast<uint8_t *>(this->encryptedTicket.data()), this->encryptedTicket.size());
}