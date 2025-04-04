target_include_directories(CANFDLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE sources 
                    ${CMAKE_SOURCE_DIR}/src/*.cpp
                    ${CMAKE_SOURCE_DIR}/src/*.cxx
                    ${CMAKE_SOURCE_DIR}/src/*.c)


set(lib_sources sources)

target_link_libraries(CANFDLib PRIVATE ${lib_sources})