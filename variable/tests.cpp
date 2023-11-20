#include "../Variable.h"
#include <gtest/gtest.h>

TEST(TheSame, int_int) {
    Variable var;

    var.setInt(102);
    EXPECT_EQ(102, var.getInt());
}

TEST(TheSame, short_short) {
    Variable var;

    var.setShort(50);
    EXPECT_EQ(50, var.getShort());
}

TEST(TheSame, unsigned_unsigned) {
    Variable var;

    var.setUnsigned(123456789);
    EXPECT_EQ(123456789, var.getUnsigned());
}

TEST(TheSame, char_char) {
    Variable var;

    var.setChar('u');
    EXPECT_EQ('u', var.getChar());
}

TEST(TheSame, char_char) {
    Variable var;

    var.setDouble(3.1415);
    EXPECT_EQ(3.1415, var.getDouble());
}

// -----------------------------------------

TEST(NoConversion, oneTypeToSecond) {
    Variable var;

    var.setUnsigned(4294967295);
    EXPECT_EQ(-1, var.getInt());
}

// ---------------------------------------------