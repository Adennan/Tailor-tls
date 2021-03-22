#include "session.h"
#include "handshake.h"
#include "record.h"
#include "clientPreShareKey.h"
#include "sequence.h"
#include "serverHello.h"
#include "epoll.h"
#include <iostream>

using namespace tailor;
using namespace std;

Session* Session::createSession(ClientPreShareKey* accessPreShareKey, ClientPreShareKey* refreshPreShareKey, std::basic_string<uint8_t> verifyKey)
{
    Session session;
    // confirm the access pre share key is available
    if (accessPreShareKey != NULL && accessPreShareKey->isExpired())
    {
        accessPreShareKey = NULL
    }
    // confirm the refresh pre share key is available
    if (refreshPreShareKey != NULL && refreshPreShareKey->isExpired())
    {
        refreshPreShareKey = NULL
    }

    session.clientSequence = Sequence::CreateSequence(1);
    session.serverSequence = Sequence::CreateSequence(1);
    session.accessPreShareKey = accessPreShareKey;
    session.refreshPreShareKey = refreshPreShareKey;
    session.publicVerifyKey = verifyKey;
    session.handshakeHash = NULL;
    
    return session;
}

void Session::createServer()
{
    ServerHello serverHello;
    serverHello.version = 0x0303;
    
}

void Session::handshake(int fd)
{
    Handshake* shake;
    Record record;
    ClientPreShareKey* clientWriteKey = NULL;

    ServerHello serverHello;
    serverHello.version = 0x0303;
    // serverHello.
}