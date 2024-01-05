#include "../src/Variable.h"
#include <gtest/gtest.h>
#include "windows.h"
#include "psapi.h"

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

TEST(TheSame, double_double) {
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

// Memory usage

SIZE_T getPhysicalMemoryUsage(PROCESS_MEMORY_COUNTERS &pmc) {
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.WorkingSetSize;
}

TEST(Memory, testForMemoryLeak) {
    PROCESS_MEMORY_COUNTERS pmc;
    SIZE_T memoryBefore = getPhysicalMemoryUsage(pmc);
    Variable varP;

    for (int i = 0; i < 1000 * 100; ++i) {
        Variable var;
        var.setDouble(5.13);
        var.setUnsigned(500);
        var.getInt();
        var.getUnsigned();
        var.setInt();

        varP.setDouble(5.13);
        varP.setUnsigned(500);
        varP.getInt();
        varP.getUnsigned();
        varP.setInt();

        SIZE_T memoryUsage = getPhysicalMemoryUsage(pmc);
        EXPECT_LT(memoryUsage, 100 * 1024 * 1024);
    }

    SIZE_T memoryUsage = getPhysicalMemoryUsage(pmc);
    EXPECT_LT(memoryUsage - memoryBefore, 5 * 1024 * 1024);
}

//Test name: MemoryLeak*
