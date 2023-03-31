cmake_minimum_required(VERSION 3.10)
project(conn)
# 调试必用参数，相当于gcc -g， 不然gdb找不到源文件，也不会报错
set(CMAKE_CXX_FLAGS "-g") 
set(CMAKE_CXX_STANDARD 17)
set(RELATIVE_EXTLIB "~/extlib")
get_filename_component(EXTLIB ${RELATIVE_EXTLIB} ABSOLUTE)

add_executable(conn main.cpp src/conn.cpp)

set(LIBCONTEXT ${EXTLIB}/install/boost/lib/libboost_context.a)

target_include_directories(conn PUBLIC
		${CMAKE_SOURCE_DIR}/include
    	${EXTLIB}/install/boost/include
)
message(${CMAKE_SOURCE_DIR}/include)
target_link_libraries(conn
	${LIBCONTEXT} pthread
)
