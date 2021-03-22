#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <algorithm>
#include <vector>

namespace tailor {
    class Utils
    {
    public:
        template <typename T>
        static T SwapEndian(T val);

        template <typename T>
        static vector<uint8_t> ToBytes(T val);

        template <typename T>
        static vector<uint8_t> GetBigEndianBytes(T val);

    };
};

template<typename T>
T tailor::Utils::SwapEndian(T val)
{
    // auto size = sizeof(val);
    // std::cout << " size : " << size << std::endl;
    T temp = 0;
    while (val > 0)
    {
        temp |= (val & 0xFF);
        temp <<= 8;
        val >>= 8;
    }
    return temp;
}

template <typename T>
vector<uint8_t> tailor::Utils::ToBytes(T val)
{
    auto length = sizeof(val);
    vector<uint8_t> data(length, 0x00);
    for (auto it = data.begin(); it!= data.end(); ++it)
    {
        *it = (val & 0xFF);
        val >>= 8;
    }
    return data;
}

template <typename T>
vector<uint8_t> tailor::Utils::GetBigEndianBytes(T val)
{
    // auto bigEndian = Utils::SwapEndian<T>(val);
    vector<uint8_t> bytes = Utils::ToBytes(val);
    std::reverse(bytes.begin(), bytes.end());
    return bytes;
}

#endif // UTILS_H