#include "finished.h"
#include "proto.h"

using namespace tailor;

void Finished::deserialize(std::basic_istringstream<uint8_t>& sstr) 
{
    // decode verifyData
    size_t len = decode<uint16_t>(sstr);
    this->verifyData.resize(len);
    sstr.read(const_cast<uint8_t *>(this->verifyData.data()), this->verifyData.size());
}