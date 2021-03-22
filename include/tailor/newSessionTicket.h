#ifndef NEW_SESSION_TICKET_H
#define NEW_SESSION_TICKET_H

#include "clientPreShareKey.h"
#include <vector>

namespace tailor {
    typedef struct Keys {
        std::basic_string<uint8_t> accessKey;
        std::basic_string<uint8_t> refreshKey;
    }Keys;

    typedef struct ShareKeys {
        ClientPreShareKey* access;
        ClientPreShareKey* refresh;
    }ShareKeys;

    class NewSessionTicket {
    private:
       std::vector<PreShareKey*> preShareKeys;

    public:
        virtual void deserialize(std::basic_istringstream<uint8_t>&) override;
        virtual ShareKeys createClientPreShareKey(Keys keys, NewSessionTicket* ticket);
    }
}


#endif // NEW_SESSION_TICKET_H