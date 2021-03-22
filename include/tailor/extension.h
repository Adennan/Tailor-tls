#ifndef EXTENSION_H
#define EXTENSION_H

#include "types.h"
#include <string>
#include <sstream>

typedef uint16_t extensionType;

namespace tailor {
    class Extension {
    private:
        extensionType type;
        std::basic_string<uint8_t> data;
    public:
        extensionType& getType()
        { 
            return this->type; 
        }

        std::basic_string<uint8_t>& getData() 
        { 
            return this->data; 
        }
        
        size_t serialize(std::basic_ostringstream<uint8_t>&);
        void deserialize(std::basic_istringstream<uint8_t>&);
        size_t size() const;

        bool operator== (const Extension&) const;
        bool operator!= (const Extension&) const;
    };
}

#endif // EXTENSION_H