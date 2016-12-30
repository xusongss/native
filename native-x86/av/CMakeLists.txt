cmake_minimum_required(VERSION 3.5)
include (CheckIncludeFiles)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/media/stagefright/foundation)
set(foundation_source_base_dir media/libstagefright/foundation)
add_library(foundation
	${foundation_source_base_dir}/AAtomizer.cpp                 
    ${foundation_source_base_dir}/ABitReader.cpp                
    ${foundation_source_base_dir}/ABuffer.cpp                   
    ${foundation_source_base_dir}/AHandler.cpp                  
    ${foundation_source_base_dir}/AHierarchicalStateMachine.cpp 
    ${foundation_source_base_dir}/ALooper.cpp                   
    ${foundation_source_base_dir}/ALooperRoster.cpp             
    ${foundation_source_base_dir}/AMessage.cpp                  
    ${foundation_source_base_dir}/AString.cpp                   
    ${foundation_source_base_dir}/base64.cpp                    
    ${foundation_source_base_dir}/hexdump.cpp
	)

