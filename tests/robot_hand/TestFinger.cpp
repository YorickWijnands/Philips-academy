#include "gtest/gtest.h"
#include "Finger.hpp"


TEST(FingerTest, ConstructorInitialPosition) {
    Finger finger(10, 90);
    EXPECT_EQ(finger.GetPosition(), 10);
}

TEST(FingerTest, ConstructorDefaultValues) {
    Finger finger;
    EXPECT_EQ(finger.GetPosition(), 0);
}


TEST(FingerTest, MoveWithinBounds) {
    Finger finger(10, 90);

    EXPECT_EQ(finger.Move(50), finger.GetPwmFromPercentage(50));
    EXPECT_EQ(finger.GetPosition(), 50);
}

TEST(FingerTest, MoveBelowMinimum) {
    Finger finger(10, 90);

    EXPECT_EQ(finger.Move(5), finger.GetPwmFromPercentage(10));
    EXPECT_EQ(finger.GetPosition(), 10);
}

TEST(FingerTest, MoveAboveMaximum) {
    Finger finger(10, 90);

    EXPECT_EQ(finger.Move(95), finger.GetPwmFromPercentage(90));
    EXPECT_EQ(finger.GetPosition(), 90);
}


TEST(FingerTest, OpenAndClose) {
    Finger finger(10, 90);

    EXPECT_EQ(finger.Open(), finger.GetPwmFromPercentage(90));
    EXPECT_EQ(finger.GetPosition(), 90);

    EXPECT_EQ(finger.Close(), finger.GetPwmFromPercentage(10));
    EXPECT_EQ(finger.GetPosition(), 10);
}


TEST(FingerTest, PwmCalculation) {
    Finger finger(0, 100);

    EXPECT_EQ(finger.GetPwmFromPercentage(0), 102);
    EXPECT_EQ(finger.GetPwmFromPercentage(50), 307);
    EXPECT_EQ(finger.GetPwmFromPercentage(100), 512);
}
