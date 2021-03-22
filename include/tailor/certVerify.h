#ifndef CERT_VERIFY_H
#define CERT_VERIFY_H

#include "handshake.h"
#include "types.h"
#include <cstdint>
#include <string>
#include <iostream>
#include <openssl/x509.h>

namespace tailor 
{
    class CertVerify : public Handshake
    {
    private:
        x509::sign_algo _sign_algo;
        std::basic_string<uint8_t> sign;
    public:
        virtual HandshakeType type() const override { return handshakeCertificatedVerify; }
        virtual size_t serialize(std::basic_ostringstream<uint8_t>&) override;
        virtual void deserialize(std::basic_istringstream<uint8_t>&) override;
        virtual size_t size() const override;
    }
}

#endif // CERT_VERIFY_H