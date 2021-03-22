#include "serverHello.h"
#include "gtest/gtest.h"

TEST(ServerHello, encode_1) {
    using namespace tailor;

    ServerHello e;

    e.version = 0x0303;
    for (int i = 0; i < 32; i++) { e.random[i] = i; }
    e.session.resize(8);
    for (int i = 0; i < 8; i++) { e.session[i] = i; }
    e.cipherSuites = 0xABCD;
    std::basic_ostringstream<uint8_t> sstr;

    e.serialize(sstr);
    auto ret = sstr.str();
    uint8_t expect[] = {
        0x03, 0x03,
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
        8, 0, 1, 2, 3, 4, 5, 6, 7,
        0xAB, 0xCD,
        0, 0
    };
    EXPECT_EQ(ret.size(), sizeof(expect));
    for (size_t i = 0; i < sizeof(expect); i++) {
        EXPECT_EQ(ret[i], expect[i]);
    }
}

int main() {
    return RUN_ALL_TESTS();
}