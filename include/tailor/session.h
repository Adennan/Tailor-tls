#ifndef SESSION_H
#define SESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "sequence.h"
#include "clientPreShareKey.h"

#define MAX_EVENTS 100

namespace tailor {
    class Session {
    private:
        Sequence clientSequence;
        Sequence serverSequence;
        ClientPreShareKey* accessPreShareKey;
        ClientPreShareKey* refreshPreShareKey;
        std::basic_string<uint8_t> clientWriteKey;
        std::basic_string<uint8_t> clientWriteIV;
        std::basic_string<uint8_t> serverWriteKey;
        std::basic_string<uint8_t> serverWriteIV;
        std::basic_string<uint8_t> publicVerifyKey;
        std::basic_string<uint8_t> handshakeHash;

    public:
        Session* createSession(ClientPreShareKey* accessPreShareKey, ClientPreShareKey* refreshPreShareKey, std::basic_string<uint8_t> verifyKey);
        
        void init();

        void createServer();

        
        // handshake
        void handshake(int fd);
    }
}

#endif // SESSION_H