#include "newSessionTicket.h"

using namespace tailor;

void NewSessionTicket::deserialize(std::basic_istringstream<uint8_t>& sstr)
{

}

ShareKeys NewSessionTicket::createClientPreShareKey(Keys keys, NewSessionTicket* ticket)
{
    ShareKeys sharekey;
    for (auto psk : ticket->preShareKeys)
    {
        if (psk->getType() == 1)
        {
            time_t now = time(NULL);
            now += psk->ticketLifeTimeHint;
            sharekey.access->setPreShareKey(psk);
            sharekey.access->setExpiredTime(now);
            sharekey.access->setResumptionSecret(keys.accessKey);
        }

        if (psk->getType() == 2)
        {
            time_t now = time(NULL);
            now += psk->ticketLifeTimeHint;
            sharekey.access->setPreShareKey(psk);
            sharekey.access->setExpiredTime(now);
            sharekey.access->setResumptionSecret(keys.refreshKey);
        }
    }
    return sharekey;
}