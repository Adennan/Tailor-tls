#include "certVerify.h"
#include "proto.h"

using namespace tailor;

size_t CertVerify::serialize(std::basic_ostringstream<uint8_t>& sstr) 
{
    size_t ret = 0;
    size_t len = 0;

    // encode algo
    ret += encode(sstr, this->_sign_algo);

    // encode sign
    len = this->sign.size();
    ret += encode(sstr, static_cast<uint16_t>(len));
    sstr.write(this->sign.data(), this->sign.size());
    ret += this->sign.size();

    return ret;
}

void CertVerify::deserialize(std::basic_istringstream<uint8_t>& sstr) {
    size_t len = 0;

    // decode algo
    this->_sign_algo = decode<x509::sign_algo>(sstr);

    // decode sign
    len = decode<uint16_t>(sstr);
    this->sign.resize(len);
    sstr.read(const_cast<uint8_t *>(this->sign.data()), this->sign.size());
}

size_t CertVerify::size() const {
    return sizeof(x509::sign_algo) + 2 + this->sign.size();
}