#ifndef ENCRYPTED_EXTENSION_H
#define ENCRYPTED_EXTENSION_H

#include "handshake.h"
#include "extension.h"
#include <vector>

namespace tailor {
    class EncryptedExtension : public Handshake {
    private:
        std::vector<Extension> extensions;
    public:
        std::vector<Extension>& getExtensions() 
        { 
            return this->extensions; 
        }

        virtual HandshakeType getType() const override 
        { 
            return handshakeEncryptedExtentions; 
        }
        
        virtual size_t serialize(std::basic_ostringstream<uint8_t>&);
        virtual void deserialize(std::basic_istringstream<uint8_t>&);
        virtual size_t size() const override;
    };
}

#endif // ENCRYPTED_EXTENSION_H