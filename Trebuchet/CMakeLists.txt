########################
# Florent Baudon
########################

cmake_minimum_required(VERSION 2.6)

project(Trebuchet)
SET(CMAKE_CXX_FLAGS "-std=c++0x")
set(EXECUTABLE_OUTPUT_PATH bin/)

option(BUILD_DYNAMIC "Build with dynamic lib of Box2D" OFF)

option(BUILD_STATIC "Build with static lib of Box2D" ON)



#repertoire des includes
include_directories (lib)

file(

        GLOB_RECURSE

        source_files

        src/*
)

if(BUILD_STATIC)
    #Librairie statique
    set(BOX2DLIB lib/Box2D/libBox2D.a)

    add_executable(

            trebuchet
            
            ${source_files}
            #Inclusion de statique
            ${BOX2DLIB}
            
    )
endif(BUILD_STATIC)

if(BUILD_DYNAMIC)

    add_executable(

            trebuchet
            
            ${source_files}
            
    )

    #repertoire de la librairie dynamique
    link_directories(lib/Box2D)
    #link dynamique
    target_link_libraries (trebuchet Box2D)
    
endif(BUILD_DYNAMIC)