#ifndef PRE_SHARE_KEY_H
#define PRE_SHARE_KEY_H

#include "handshake.h"
#include "extension.h"
#include <cstdint>
#include <string>
#include <vector>

namespace tailor {
    class PreShareKey : public Handshake {
    private:
        uint8_t type;
        uint32_t ticketLifeTimeHint;
        std::basic_string<uint8_t> macValue;
        uint32_t keyVersion;
        std::basic_string<uint8_t> iv;
        std::basic_string<uint8_t> encryptedTicket;
    public:
        uint8_t& getType() 
        { 
            return this->type; 
        }

        uint32_t& getTicketLifeTimeHint() 
        { 
            return this->ticketLifeTimeHint; 
        }

        std::basic_string<uint8_t>& getMacValue() 
        { 
            return this->macValue; 
        }

        uint32_t& getKeyVersion() 
        { 
            return this->keyVersion; 
        }

        std::basic_string<uint8_t>& getIV() 
        { 
            return this->iv; 
        }

        std::vector<tls_extension>& getEncryptedTicket() 
        { 
            return this->encryptedTicket; 
        }

        virtual HandshakeType getType() const override 
        { 
            return handshakeNewSessionTicket; 
        }
        
        virtual size_t serialize(std::basic_ostringstream<uint8_t>&) override;
        virtual void deserialize(std::basic_istringstream<uint8_t>&) override;
        virtual size_t size() const override;
    };
}

#endif // PRE_SHARE_KEY_H