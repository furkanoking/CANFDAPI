add_executable(test_main test.cpp)


target_include_directories(test_main PRIVATE /usr/src/gtest/include)
target_include_directories(test_main PRIVATE ${CMAKE_SOURCE_DIR}/include/private_include)
target_include_directories(test_main PRIVATE ${CMAKE_SOURCE_DIR}/include/public_include)

target_link_libraries(test_main  CANFDLib)
target_link_libraries(test_main gtest gtest_main)
