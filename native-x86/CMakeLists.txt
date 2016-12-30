cmake_minimum_required(VERSION 3.5)
include (CheckIncludeFiles)

##atomic.c need this
add_definitions(-D__x86_64__ -g)
##定义内存屏障 http://blog.csdn.net/u013234805/article/details/24796503
add_definitions(-DANDROID_SMP=0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/native/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/av/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/system/core/include)
CHECK_INCLUDE_FILES(pthread.h HAVE_PTHREADS)
CHECK_INCLUDE_FILES("sys/uio.h" HAVE_SYS_UIO_H)
CHECK_INCLUDE_FILES("endian.h" HAVE_ENDIAN_H)
add_definitions(-DHAVE_POSIX_CLOCKS)

if(HAVE_PTHREADS)
	add_definitions(-DHAVE_PTHREADS)
	message(STATUS "------have pthread.h")
endif()
if(HAVE_SYS_UIO_H)
	add_definitions(-DHAVE_SYS_UIO_H)
	message(STATUS "------have sys/uio.h")
endif()
if(HAVE_ENDIAN_H)
	add_definitions(-DHAVE_ENDIAN_H)
	message(STATUS "------have endian.h")
endif()
#CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_subdirectory(native/libs)
add_subdirectory(system)
add_subdirectory(av)
add_subdirectory(test)
