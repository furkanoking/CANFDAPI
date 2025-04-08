target_include_directories(CANFDLib PUBLIC ${CMAKE_SOURCE_DIR}/include/public_include)

target_include_directories(CANFDLib PRIVATE ${CMAKE_SOURCE_DIR}/include/private_include)

file(GLOB_RECURSE sources 
                    ${CMAKE_SOURCE_DIR}/src/*.cpp
                    ${CMAKE_SOURCE_DIR}/src/*.cxx
                    ${CMAKE_SOURCE_DIR}/src/*.c)


set(lib_sources sources)

file(GLOB_RECURSE pu_headers 
                    ${CMAKE_SOURCE_DIR}/include/public_include/*.h
                    ${CMAKE_SOURCE_DIR}/include/public_include/*.hpp
)
set(PUBLIC_headers ${pu_headers})

file(GLOB_RECURSE pri_headers 
                    ${CMAKE_SOURCE_DIR}/include/private_include/*.h
                    ${CMAKE_SOURCE_DIR}/include/private_include/*.hpp
)
set(PRIVATE_headers ${pri_headers})

set_target_properties(CANFDLib PROPERTIES 
    PUBLIC_HEADER   ${PUBLIC_headers}
    PRIVATE_HEADER  ${PRIVATE_headers})

target_link_libraries(CANFDLib PRIVATE ${lib_sources})