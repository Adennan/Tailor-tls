#ifndef CLIENT_PRE_SHARE_KEY_H
#define CLIENT_PRE_SHARE_KEY_H

#include "handshake.h"
#include "extension.h"
#include "preShareKey.h"
#include <cstdint>
#include <string>
#include <vector>

namespace tailor {
    class ClientPreShareKey : public Handshake {
    private:
        PreShareKey* preShareKey;
        time_t expiredTime;
        std::basic_string<uint8_t> resumptionSecret;
    public:
        PreShareKey* getPreShareKey() 
        { 
            return this->preShareKey; 
        }

        time_t getExpiredTime() 
        { 
            return this->expiredTime; 
        }
        
        std::basic_string<uint8_t>& getResumptionSecret() 
        { 
            return this->resumptionSecret; 
        }

        void setPreShareKey(PreShareKey* preShareKey) 
        { 
            this->preShareKey = preShareKey; 
        }

        void setExpiredTime(time_t expiredTime) 
        {
            this->expiredTime = expiredTime; 
        }
        
        void setResumptionSecret(std::basic_string<uint8_t> resumptionSecret) 
        { 
            this->resumptionSecret = resumptionSecret; 
        }

        virtual size_t serialize(std::basic_ostringstream<uint8_t>&) override;
        virtual void deserialize(std::basic_istringstream<uint8_t>&) override;
        virtual bool isExpired(ClientPreShareKey* psk);
        virtual size_t size() const override;
    };
}

#endif // CLIENT_PRE_SHARE_KEY_H