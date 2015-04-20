########################
# Florent Baudon
########################

cmake_minimum_required(VERSION 2.6)

project(Trebuchet)
SET(CMAKE_CXX_FLAGS "-std=c++0x")
set(EXECUTABLE_OUTPUT_PATH bin/)

file(

        GLOB_RECURSE

        source_files

        src/*
)

add_executable(

	trebuchet
	
	${source_files}
	
)
