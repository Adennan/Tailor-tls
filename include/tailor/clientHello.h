#ifndef CLIENT_HELLO_H
#define CLIENT_HELLO_H

#include <iostream>
#include <vector>
#include "handshake.h"
#include "extension.h"

typedef uint16_t CipherSuite;

const static CipherSuite CipherSuiteEcdheEcdsaWithAes128GcmSha256 = 0xc02b;
const static CipherSuite CipherSuitePskWithAes128GcmSha256 = 0xa8;

namespace tailor {
    class ClientHello : public Handshake {
    private:
        uint16_t version;
        std::basic_string<uint8_t> random;
        std::basic_string<uint8_t> session;
        std::vector<CipherSuite> cipherSuites;
        uint32_t timestamp; // timestamp uinx
        std::vector<Extension> extensions;

    public:
        ClientHello();

        virtual HandshakeType getType() const override 
        { 
            return handshakeClientHello; 
        }

        uint16_t getVersion() 
        { 
            return this->version; 
        }

        std::basic_string<uint8_t> getRandom() 
        { 
            return this->random; 
        }

        std::basic_string<uint8_t> getSession() 
        { 
            return this->session; 
        }

        vector<CipherSuite> getCipherSuites() 
        { 
            return this->cipherSuites; 
        }

        uint32_t getTimestamp() 
        { 
            return this->timestamp; 
        }

        vector<Extension> getExtensions() 
        { 
            return this->extensions; 
        }
        
        virtual size_t serialize(std::basic_ostringstream<uint8_t>&) override;
        virtual void deserialize(std::basic_istringstream<uint8_t>&) override;
        virtual size_t size() const override;

    };
};

#endif // CLIENT_HELLO_H