#ifndef PROTO_H
#define PROTO_H

#include <math.h>
#include <time.h>
#include <climits>
#include <iostream>
#include <sstream>

const static uint16_t TlSVersion = 0xf103;
const static uint16_t TLSMaxPackageSize = UINT16_MAX;

namespace tailor {
    int array_copy(uint8_t *main, int startaddr, uint8_t *extra, int extralen) {
        for(int i=startaddr; i <startaddr+extralen; i++){
            *(main+i) = *(extra+(i-startaddr));
        }
        return startaddr+extralen;
    }

    template <typename T_Int> size_t encode(std::basic_ostringstream<uint8_t>& sstr, T_Int val) {
        for (int i = 0; i < sizeof(T_Int); i++) {
            sstr.put(static_cast<uint8_t>((val >> (8 * (sizeof(T_Int) - i - 1))) & 0xFF));
        }
        return sizeof(T_Int);
    }

    template <typename T_Int> T_Int decode(std::basic_istringstream<uint8_t>& sstr) {
        T_Int ret = 0;
        for (int i = 0; i < sizeof(T_Int); i++) {
            ret = ret << 8;
            ret |= sstr.get();
        }
        return ret;
    }

    size_t entityEncode(std::basic_ostringstream<uint8_t>&, Handshake&);
    std::unique_ptr<Handshake> entityDecode(std::basic_istringstream<uint8_t>&);

}

#endif  // PROTO_H