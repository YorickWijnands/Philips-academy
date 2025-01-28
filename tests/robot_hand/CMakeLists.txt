file(GLOB TEST_SOURCES "*.cpp")

add_executable(runRobotHandTests ${TEST_SOURCES}
    ${CMAKE_SOURCE_DIR}/src/robot_hand/Finger.cpp
)

target_include_directories(runRobotHandTests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/robot_hand
    ${CMAKE_SOURCE_DIR}/amp-embedded-infra-lib/hal/interfaces
    ${CMAKE_SOURCE_DIR}/src/robot_hand/tests/mocks
)

target_link_libraries(runRobotHandTests gtest gmock gtest_main pthread)

enable_testing()

gtest_discover_tests(runRobotHandTests)
