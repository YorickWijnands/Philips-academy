#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cstdint>

// Include your interfaces (assuming they are located in the same directory)
#include "IPca9685Controller.hpp"
#include "Message.hpp"
#include "Hand.hpp"

// Mock class for IPca9685Controller
class MockPca9685Controller : public IPca9685Controller {
public:
    MOCK_METHOD(void, SetAddress, (uint16_t newAddress), (override));
    MOCK_METHOD(uint16_t, GetRawAddress, (), (const, override));
    MOCK_METHOD(uint16_t, GetAddress, (), (const, override));
    MOCK_METHOD(Channels, ConnectChannel, (), (override));
    MOCK_METHOD(bool, IsInitialized, (), (const, override));
    MOCK_METHOD(Channels, GetChannel, (uint8_t index), (override));
    MOCK_METHOD(void, EnqueueMessage, (const Message& message), (override));
    MOCK_METHOD(void, Configure, (), (override));
};

// Test class
class HandTest : public ::testing::Test {
protected:
    MockPca9685Controller mockController;
    Hand hand{&mockController};

    HandTest() {
        // This constructor can be used to set up any common test state
    }
};

// Test the `isInitialized` method
TEST_F(HandTest, TestIsInitializedWhenAllFingersConnected) {
    // Mock the behavior of ConnectChannel to return valid channels for all fingers
    EXPECT_CALL(mockController, ConnectChannel())
        .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_0))
        .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_1))
        .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_2))
        .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_3))
        .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_4));

    // Ensure that Hand has been properly initialized
    EXPECT_TRUE(hand.isInitialized());
}

// TEST_F(HandTest, TestIsInitializedWhenFingerNotConnected) {
//     // Mock the behavior to simulate a case where one finger is not connected
//     EXPECT_CALL(mockController, ConnectChannel())
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_0))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_1))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_2))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_3))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_none));  // Finger 4 is not connected

//     // Ensure that Hand is not initialized if not all fingers are connected
//     EXPECT_FALSE(hand.isInitialized());
// }

// // Test the `OpenHand` method
// TEST_F(HandTest, TestOpenHand) {
//     // Mock the behavior of the controller to return valid channels
//     EXPECT_CALL(mockController, ConnectChannel())
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_0))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_1))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_2))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_3))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_4));

//     // Expect the `EnqueueMessage` method to be called for each finger
//     EXPECT_CALL(mockController, EnqueueMessage(testing::_)).Times(5); // 5 times, once for each finger

//     // Call `OpenHand` method
//     hand.OpenHand(0);  // No delay
// }

// // Test the `CloseHand` method
// TEST_F(HandTest, TestCloseHand) {
//     // Mock the behavior of the controller to return valid channels
//     EXPECT_CALL(mockController, ConnectChannel())
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_0))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_1))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_2))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_3))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_4));

//     // Expect the `EnqueueMessage` method to be called for each finger
//     EXPECT_CALL(mockController, EnqueueMessage(testing::_)).Times(5); // 5 times, once for each finger

//     // Call `CloseHand` method
//     hand.CloseHand(0);  // No delay
// }

// // Test the `MoveFinger` method
// TEST_F(HandTest, TestMoveFinger) {
//     // Mock the behavior of the controller to return valid channels
//     EXPECT_CALL(mockController, ConnectChannel())
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_0))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_1))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_2))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_3))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_4));

//     // Expect the `EnqueueMessage` method to be called for each finger
//     EXPECT_CALL(mockController, EnqueueMessage(testing::_)).Times(5); // 5 times, once for each finger

//     // Call `MoveFinger` method
//     hand.MoveFinger(IPca9685Controller::FingerType::Thumb, 50, 100);
// }

// // Test the `Wiggle` method
// TEST_F(HandTest, TestWiggle) {
//     // Mock the behavior of the controller to return valid channels
//     EXPECT_CALL(mockController, ConnectChannel())
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_0))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_1))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_2))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_3))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_4));

//     // Expect the `EnqueueMessage` method to be called multiple times as per the wiggle movement
//     EXPECT_CALL(mockController, EnqueueMessage(testing::_)).Times(10); // 10 times (for each move)

//     // Call `Wiggle` method
//     hand.Wiggle();
// }

// // Test the `WaveMotion` method
// TEST_F(HandTest, TestWaveMotion) {
//     // Mock the behavior of the controller to return valid channels
//     EXPECT_CALL(mockController, ConnectChannel())
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_0))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_1))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_2))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_3))
//         .WillOnce(testing::Return(IPca9685Controller::Channels::Channel_4));

//     // Expect the `EnqueueMessage` method to be called multiple times as part of the wave motion
//     EXPECT_CALL(mockController, EnqueueMessage(testing::_)).Times(20); // 20 times (10 steps * 2 cycles)

//     // Call `WaveMotion` method
//     hand.WaveMotion(10, 5, 2);
// }

// // Main function to run the tests
// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
