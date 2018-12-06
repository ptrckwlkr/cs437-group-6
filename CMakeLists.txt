###########################
# CMake Build Environment #
###########################
#
# You can set the following Environment variables:
#
# CMAKE_MODULE_PATH to the search path for cmake modules (e.g., SFML.cmake)
# CMAKE_BUILD_TYPE to override the default build type. Valid options are 'release', 'profile' and 'debug'
#
#########################################

# Project name
project(csci437)

# Minimum Cmake Version
cmake_minimum_required(VERSION 2.6)

#####################
# Setup Environment #
#####################
# set to include custom modules
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${csci437_SOURCE_DIR}/cmake)

# set build type if specified by environment
if((NOT CMAKE_BUILD_TYPE) AND (NOT $ENV{CMAKE_BUILD_TYPE} STREQUAL ""))
    set(CMAKE_BUILD_TYPE $ENV{CMAKE_BUILD_TYPE})
endif()

# Set include directories
include_directories(${csci437_SOURCE_DIR}/include)

# Get CPP files
file(GLOB_RECURSE SRC src/*cpp)

# Get executable files
file(GLOB EXECLIST bin/*cpp)


#################################################
#                                               #
# ADD CUSTOM LIBRARIES HERE.                    #
#                                               #
# Example BOOST:                                #
#  find_package(Boost REQUIRED)                 #
#  include_directories(${Boost_INCLUDE_DIRS})   #
#  link_libraries(${Boost_LIBRARIES})           #
#################################################


#############
# Find SFML #
#############
find_package(SFML COMPONENTS graphics window system audio network)
include_directories(${SFML_INCLUDE_DIR})
link_libraries(${SFML_LIBRARIES})

if(NOT SFML_FOUND)
  # SFML not found
  message(FATAL_ERROR " * Make sure LIB includes the directory where the SFML libraries are installed.\n * Make sure INCLUDE includes the directory where the SFML header files are installed.")	
endif()

###############
# C++ Options #
###############
# Enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# determine build type
# 1) use build type if specified by the user.
# 2) if in-source building, use default (debug) build type.
# 3) if out-source building, determine based on the build directory's name which build type. 
#    If build directory is called 'Release' or 'Profile' then use the 'Release' and 'Profile' 
#    build type respectively, otherwise use 'debug'.
if(CMAKE_BUILD_TYPE)
  string(TOUPPER "${CMAKE_BUILD_TYPE}" TYPE)
  message("-- Using user specified build type: ${TYPE}")
elseif(${csci437_SOURCE_DIR} STREQUAL ${csci437_BINARY_DIR})
  set(CMAKE_BUILD_TYPE Debug)
  message("-- In-source building. Build type set to: Debug")
else()
  get_filename_component(TYPE ${csci437_BINARY_DIR} NAME)
  string(TOUPPER "${TYPE}" TYPE)
  if(${TYPE} STREQUAL "RELEASE")
    set(CMAKE_BUILD_TYPE Release)
  elseif(${TYPE} STREQUAL "PROFILE")
    set(CMAKE_BUILD_TYPE Profile)
  else()
    set(CMAKE_BUILD_TYPE Debug)
 endif()
 message("-- Out-source building. Build type set to: ${TYPE}")
endif()

# Handle non-default build type 'Profile'
string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)
if(${CMAKE_BUILD_TYPE} STREQUAL "PROFILE")
  set(CMAKE_BUILD_TYPE DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
endif()

#######################
# Set Compile Targets #
#######################
# src library (all CPP files in 'src' dir)
if(NOT SRC STREQUAL "")
  get_filename_component(LIBNAME ${csci437_SOURCE_DIR} NAME)
  set(LIBNAME "${LIBNAME}_core")
  add_library(${LIBNAME} ${SRC})
endif()

# executables (any CPP file in 'bin' dir)
foreach(EXEC ${EXECLIST})
  get_filename_component(EXECNAME ${EXEC} NAME_WE)

<<<<<<< HEAD
  add_executable(${EXECNAME} ${EXEC} src/graphics/graphics_shop.cpp include/graphics/graphics_shop.h src/views/player_view_shop.cpp include/views/player_view_shop.h src/graphics/graphics_lost.cpp include/graphics/graphics_lost.h src/views/player_view_lost.cpp include/views/player_view_lost.h src/graphics/graphics_story.cpp include/graphics/graphics_story.h src/views/player_view_story.cpp include/views/player_view_story.h include/entities/enemy.h include/entities/ghost.h src/entities/ghost.cpp include/views/view_ghost.h src/views/view_ghost.cpp include/Animations/GhostAnimation.h src/Animations/GhostAnimation.cpp include/entities/orc.h src/entities/orc.cpp include/Animations/OrcAnimation.h src/Animations/OrcAnimation.cpp include/views/view_orc.h src/views/view_orc.cpp src/entities/boss.cpp include/entities/boss.h src/views/view_boss.cpp include/views/view_boss.h src/graphics/graphics_next_level.cpp include/graphics/graphics_next_level.h src/views/player_next_level.cpp include/views/player_next_level.h)
=======
  add_executable(${EXECNAME} ${EXEC} src/graphics/graphics_shop.cpp include/graphics/graphics_shop.h src/views/player_view_shop.cpp include/views/player_view_shop.h src/graphics/graphics_lost.cpp include/graphics/graphics_lost.h src/views/player_view_lost.cpp include/views/player_view_lost.h src/graphics/graphics_story.cpp include/graphics/graphics_story.h src/views/player_view_story.cpp include/views/player_view_story.h include/entities/enemy.h include/entities/ghost.h src/entities/ghost.cpp include/views/view_ghost.h src/views/view_ghost.cpp include/Animations/GhostAnimation.h src/Animations/GhostAnimation.cpp include/entities/orc.h src/entities/orc.cpp include/Animations/OrcAnimation.h src/Animations/OrcAnimation.cpp include/views/view_orc.h src/views/view_orc.cpp include/entities/potion.h src/entities/potion.cpp src/Animations/PotionAnimation.cpp include/Animations/PotionAnimation.h)
>>>>>>> b6e3974b89ed24aca64d10f70426589870691ec8

  if(NOT SRC STREQUAL "")
    target_link_libraries(${EXECNAME} LINK_PUBLIC ${LIBNAME})
  endif()

  message("-- Adding executable: ${EXECNAME}")
endforeach(EXEC)
