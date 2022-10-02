#include "gtest/gtest.h"

#include "ntp.h"

using namespace datetime;
TEST(ntp, build){

    auto ntp_value = pack({0x01020304, 0x05060708});

    EXPECT_EQ(0x0102030405060708, ntp_value);
}

TEST(ntp, unpack){

    auto ntp = unpack(0x0102030405060708);
    EXPECT_EQ(0x01020304, ntp.seconds);
    EXPECT_EQ(0x05060708, ntp.fraction);
}

TEST(ntp, from_iso8601){

    ntp_t value = from_iso8601("1900-01-0