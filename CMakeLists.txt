#/***************************************************************************
# Copyright [2015 - 2020] [Paolo Quadrani]
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ***************************************************************************/

cmake_minimum_required(VERSION 3.0)

project("pqTestSuite" VERSION "1.0.0")


set(BUILD_SHARED_LIBS TRUE CACHE BOOL "build shared libraries")
set(FAKEIT_DIR "" CACHE PATH "Path to the FakeIt source directory")

# This will try to find Qt5, if not found then will fall back to Qt4
# It will define QT_VERSION and QT_FOUND variables useful for tests
include("${CMAKE_CURRENT_SOURCE_DIR}/CMake/setup_qt.cmake")

if (NOT QT_FOUND)
  message(FATAL_ERROR
      "pqTestSuite require QtTest to be enabled."
      "Please install Qt4 or Qt5 and run again the CMake on this project.")
endif ()

add_library(pqTestSuite
    "pqTestRegistry.cxx"
)

set_property(TARGET pqTestSuite PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_property(TARGET pqTestSuite PROPERTY AUTOMOC TRUE)
set_property(TARGET pqTestSuite PROPERTY PUBLIC_HEADER
    "pqTestRegistration.h"
    "pqTestSuite.h"
)

if(UNIX)
    target_compile_options(pqTestSuite PRIVATE "-std=c++11")
endif()

target_compile_definitions(pqTestSuite PRIVATE Wall)

target_link_libraries(pqTestSuite
    PRIVATE
        ${QT_LIBS}
)

install(
    TARGETS pqTestSuite
    DESTINATION "lib"
    PUBLIC_HEADER DESTINATION "include"
)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/CMake"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
)
