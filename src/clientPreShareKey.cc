#include "clientPreShareKey.h"
#include <time.h>
#include <sys/time.h>

using namespace tailor;

size_t ClientPreShareKey::serialize(std::basic_ostringstream<uint8_t>& sstr)
{
    size_t ret = 0;

    // encode preShareKey
    size_t len = this->preShareKey.size();
    ret += encode(sstr, static_cast<uint16_t>(len));
    sstr.write(this->preShareKey.data(), this->preShareKey.size());
    ret += this->preShareKey.size();

    // encode expiredTime
    size_t len = this->expiredTime.size();
    ret += encode(sstr, static_cast<uint16_t>(len));
    sstr.write(this->expiredTime.data(), this->expiredTime.size());
    ret += this->expiredTime.size();

    // encode resumptionSecret
    size_t len = this->resumptionSecret.size();
    ret += encode(sstr, static_cast<uint16_t>(len));
    sstr.write(this->resumptionSecret.data(), this->resumptionSecret.size());
    ret += this->resumptionSecret.size();

    return ret;
}

void ClientPreShareKey::deserialize(std::basic_istringstream<uint8_t>& sstr)
{
    // decode preShareKey
    size_t len = decode<uint16_t>(sstr);
    this->preShareKey.resize(len);
    sstr.read(const_cast<uint8_t *>(this->preShareKey.data()), this->preShareKey.size());

    // decode expiredTime
    size_t len = decode<uint16_t>(sstr);
    this->expiredTime.resize(len);
    sstr.read(const_cast<uint8_t *>(this->expiredTime.data()), this->expiredTime.size());

    // decode resumptionSecret
    size_t len = decode<uint16_t>(sstr);
    this->resumptionSecret.resize(len);
    sstr.read(const_cast<uint8_t *>(this->resumptionSecret.data()), this->resumptionSecret.size());
}

bool ClientPreShareKey::isExpired(ClientPreShareKey* psk)
{
    time_t now = time(NULL);  
    // 获取本地时间  
    tm* t_tm = localtime(&now);
    cout << t_tm << endl;
    now -= 10*60;
    return now > psk->expiredTime;
}