#ifndef FINISH_H
#define FINISH_H

#include <iostream>
#include "types.h"

namespace tailor {
    class Finished {
    private:
        std::basic_string<uint8_t> verifyData;

    public:
        std::basic_string<uint8_t> getVerifyData() 
        { 
            return this->verifyData; 
        }
        
        virtual HandshakeType type() const override 
        { 
            return handshakeFinished; 
        }
        
        virtual size_t serialize(std::basic_ostringstream<uint8_t>&) override;
        virtual void deserialize(std::basic_istringstream<uint8_t>&) override;
    };
}

#endif // FINISH_H