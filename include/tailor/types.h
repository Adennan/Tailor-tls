#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <stdint.h>

enum HandshakeType : uint8_t
{
    handshakeClientHello = 0x01,
    handshakeServerHello = 0x02,
    handshakeNewSessionTicket = 0x04,
    handshakeEncryptedExtentions = 0x08,
    handshakeCertificatedVerify = 0x0f,
    handshakeFinished = 0x14
};

enum ExtensionType : uint16_t
{
    server_name = 0,
    supported_groups = 10,
    signature_algorithms = 13,
    application_layer_protocol_negotiation = 16,
    token_binding = 24,
    key_share_old = 40,
    pre_shared_key = 41,
    early_data = 42,
    supported_versions = 43,
    cookie = 44,
    psk_key_exchange_modes = 45,
    certificate_authorities = 47,
    post_handshake_auth = 49,
    signature_algorithms_cert = 50,
    key_share = 51,

    compress_certificate = 0xff02
};

#endif // TYPES_H