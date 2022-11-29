cmake_minimum_required(VERSION 3.10)
project(server)
set(CMAKE_CXX_STANDARD 20)
set(RELATIVE_EXTLIB "~/extlib")
get_filename_component(EXTLIB ${RELATIVE_EXTLIB} ABSOLUTE)

add_executable(server server.cpp)


set(LIBEVENT ${EXTLIB}/install/libevhtp/lib/libevhtp.a ${EXTLIB}/install/libevent/lib/libevent.a ${EXTLIB}/install/libevent/lib/libevent_core.a ${EXTLIB}/install/libevent/lib/libevent_extra.a ${EXTLIB}/install/libevent/lib/libevent_pthreads.a ${EXTLIB}/install/libevent/lib/libevent_openssl.a)

target_include_directories(server PUBLIC
    ${EXTLIB}/install/libevent/include
    ~/mylib/abseil-cpp
)

target_link_libraries(server
	${LIBEVENT}
)