cmake_minimum_required(VERSION 3.5)

add_executable(test_mutex
	test_mutex.cpp
	)
add_executable(test_thread
	test_thread.cpp
	)
target_link_libraries(test_thread utils pthread log cutils foundation)
add_executable(test_aloop
	test_aloop.cpp
	)
target_link_libraries(test_aloop   foundation log utils cutils pthread)

