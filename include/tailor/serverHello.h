#ifndef SERVER_HELLO_H
#define SERVER_HELLO_H

#include <string>
#include <vector>
#include "handshake.h"
#include "extension.h"

typedef uint16_t CipherSuite;

namespace tailor {
    class ServerHello : public Handshake {
    public:
        uint16_t version;
        std::basic_string<uint8_t> random;
        std::basic_string<uint8_t> session;
        CipherSuite cipherSuites;
        std::vector<Extension> extensions;

    public:
        ServerHello();

        virtual HandshakeType getType() const override 
        { 
            return handshakeServerHello; 
        }

        uint16_t& getVersion() 
        { 
            return this->version; 
        }

        std::basic_string<uint8_t>& getRandom() 
        { 
            return this->random; 
        }

        std::basic_string<uint8_t>& getSession() 
        { 
            return this->session; 
        }

        CipherSuite& getCipherSuites() 
        { 
            return this->cipherSuites; 
        }

        vector<Extension>& getExtensions() 
        { 
            return this->extensions; 
        }
        
        virtual size_t serialize(std::basic_ostringstream<uint8_t>&) override;
        virtual void deserialize(std::basic_istringstream<uint8_t>&) override;
        virtual size_t size() const override;

        bool operator== (const ServerHello&) const;
        bool operator!= (const ServerHello&) const;
    };
};

#endif // SERVER_HELLO_H