cmake_minimum_required(VERSION 3.10)
project(client)
set(CMAKE_CXX_STANDARD 20)
set(RELATIVE_EXTLIB "~/extlib")
get_filename_component(EXTLIB ${RELATIVE_EXTLIB} ABSOLUTE)

find_package(Protobuf REQUIRED) 
set(PROTO_FILES proto/ping.proto)
set(PROTO_SRCS )
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
message("PROTO_SRCS = ${PROTO_SRCS}")
message("PROTO_HDRS = ${PROTO_HDRS}")



add_executable(client client.cpp ${PROTO_SRCS} ${PROTO_HDRS})

target_include_directories(client PUBLIC
    ~/mylib/abseil-cpp
    ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(client
    ${Protobuf_LIBRARIES}
)