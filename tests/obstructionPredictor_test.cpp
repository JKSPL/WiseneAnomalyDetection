#include <gtest/gtest.h>
#include <obstructionPredictor/obstructionPredictor.hpp>

// Demonstrate some basic assertions.
TEST(ObstructionPredictorTest, AllZeros3h) {
    ObstructionPredictor p;

    for (int i = 0; i < 100; i++) {
        p.Insert(i * 3 * 60 * 60 * 1000, 0, 0);
        EXPECT_FLOAT_EQ(p.ObstructionValue(), 0);
    }
}

TEST(ObstructionPredictorTest, OneSuperSpike) {
    ObstructionPredictor p;

    for (int i = 0; i < 100; i++) {
        uint64_t t = i * 3 * 60 * 60 * 1000;
        if (i != 60) {
            p.Insert(t, 0, 0);
            EXPECT_FALSE(p.IsObstructed());
            EXPECT_FLOAT_EQ(p.ObstructionValue(), 0);
        } else {
            p.Insert(t, 10000, 0);
            EXPECT_TRUE(p.IsObstructed());
            EXPECT_FLOAT_EQ(p.ObstructionValue(), -10000);
        }
    }
}

TEST(ObstructionPredictorTest, OneSmallSpike) {
    ObstructionPredictor p;

    for (int i = 0; i < 100; i++) {
        uint64_t t = i * 3 * 60 * 60 * 1000;
        if (i != 60) {
            p.Insert(t, 0, 0);
            EXPECT_FALSE(p.IsObstructed());
            EXPECT_FLOAT_EQ(p.ObstructionValue(), 0);
        } else {
            p.Insert(t, 100, 0);
            EXPECT_TRUE(p.IsObstructed());
            EXPECT_FLOAT_EQ(p.ObstructionValue(), -100);
        }
    }
}

TEST(ObstructionPredictorTest, SmallChanges) {
    ObstructionPredictor p;
    uint64_t t_step = 3 * 60 * 60 * 1000;
    uint64_t t = 0;
    int h = 200;
    for (int i = 0; i < 25; i++) {
        p.Insert(t, h--, 200);
        EXPECT_FALSE(p.IsObstructed());
        EXPECT_FLOAT_EQ(p.ObstructionValue(), 0);
        t += t_step;
    }
    for (int i = 0; i < 25; i++) {
        p.Insert(t, h++, 200);
        EXPECT_FALSE(p.IsObstructed());
        EXPECT_FLOAT_EQ(p.ObstructionValue(), 0);
        t += t_step;
    }
}