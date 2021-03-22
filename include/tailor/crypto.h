#ifndef CRYPTO_H
#define CRYPTO_H

#include <openssl/hmac.h>
#include <openssl/aes.h>
#include <openssl/ec.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <signal.h>

namespace tailor
{
    void envInit()
    {
        #if OPENSSL_VERSION_NUMBER >= 0x10100003L

                    if (!OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CONFIG
        #ifndef OPENSSL_NO_AUTOLOAD_CONFIG
                                            | OPENSSL_INIT_LOAD_CONFIG
        #endif
                                            | OPENSSL_INIT_ADD_ALL_CIPHERS
                                            | OPENSSL_INIT_ADD_ALL_DIGESTS,
                                            NULL))

                perror("error");

        #else

                OPENSSL_config(NULL);
                OpenSSL_add_all_algorithms();

        #endif
            perror("error");

    }
}

#endif // CRYPTO_H