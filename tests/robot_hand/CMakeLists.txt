add_executable(TestHand TestHand.cpp 
        ${CMAKE_SOURCE_DIR}/src/robot_hand/Message.cpp
        ${CMAKE_SOURCE_DIR}/src/robot_hand/Finger.cpp
        ${CMAKE_SOURCE_DIR}/src/robot_hand/Hand.cpp)

add_executable(TestFinger TestFinger.cpp ${CMAKE_SOURCE_DIR}/src/robot_hand/Finger.cpp)

target_link_libraries(TestHand gtest gmock gtest_main pthread)
target_link_libraries(TestFinger gtest gmock gtest_main pthread)

target_include_directories(TestHand PRIVATE
    ${CMAKE_SOURCE_DIR}/src/robot_hand       
    ${CMAKE_SOURCE_DIR}/amp-embedded-infra-lib/hal/interfaces
    ${CMAKE_SOURCE_DIR}/src/robot_hand/tests/mocks
)

target_include_directories(TestFinger PRIVATE
    ${CMAKE_SOURCE_DIR}/src/robot_hand
    ${CMAKE_SOURCE_DIR}/amp-embedded-infra-lib/hal/interfaces
    ${CMAKE_SOURCE_DIR}/src/robot_hand/tests/mocks
)

# Enable testing
enable_testing()

# Register your tests with CTest
add_test(NAME TestHand COMMAND TestHand)
add_test(NAME TestFinger COMMAND TestFinger)
