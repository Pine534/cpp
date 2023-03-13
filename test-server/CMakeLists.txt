cmake_minimum_required(VERSION 3.10)
project(server)
# 调试必用参数，相当于gcc -g， 不然gdb找不到源文件，也不会报错
# set(CMAKE_CXX_FLAGS "-g") 
set(CMAKE_CXX_STANDARD 20)
set(RELATIVE_EXTLIB "~/extlib")
get_filename_component(EXTLIB ${RELATIVE_EXTLIB} ABSOLUTE)

find_package(Protobuf REQUIRED) 
find_package(gRPC CONFIG REQUIRED)
set(PROTO_FILES proto/ping.proto)
set(PROTO_SRCS )
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
message("PROTO_SRCS = ${PROTO_SRCS}")
message("PROTO_HDRS = ${PROTO_HDRS}")



add_executable(server server.cpp ${PROTO_SRCS} ${PROTO_HDRS})

set(LIBEVENT ${EXTLIB}/install/libevhtp/lib/libevhtp.a ${EXTLIB}/install/libevent/lib/libevent.a ${EXTLIB}/install/libevent/lib/libevent_core.a ${EXTLIB}/install/libevent/lib/libevent_extra.a ${EXTLIB}/install/libevent/lib/libevent_pthreads.a ${EXTLIB}/install/libevent/lib/libevent_openssl.a)

target_include_directories(server PUBLIC
    ${EXTLIB}/install/libevent/include
    ~/mylib/abseil-cpp
    ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(server
	${LIBEVENT}
    ${Protobuf_LIBRARIES}
    # gRPC::grpc++
)