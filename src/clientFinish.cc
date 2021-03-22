#include "finished.h"

using namespace tailor;

size_t Finished::serialize(std::basic_ostringstream<uint8_t>& sstr)
{
    size_t ret = 0;
    // encode verifyData
    size_t len = this->verifyData.size();
    ret += encode(sstr, static_cast<uint16_t>(len));
    sstr.write(this->verifyData.data(), this->verifyData.size());
    ret += this->verifyData.size();

    return ret;
}
