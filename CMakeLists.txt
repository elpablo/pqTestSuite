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

#[====================================================================[
#In ${PROJECT_SOURCE_DIR}/cmake/include add a cmake script to setup the
#project specific include search path
#]====================================================================]
include("${PROJECT_SOURCE_DIR}/cmake/include/${PROJECT_NAME}_setup_cmake_include.cmake")

set(BUILD_SHARED_LIBS TRUE CACHE BOOL "build shared libraries")
set(TEST_DATA_DIR "" CACHE PATH "Path to the dir containing the data used for the test suites")
#set(FAKEIT_DIR "" CACHE PATH "Path to the FakeIt source directory")

# This will try to find Qt5, if not found then will fall back to Qt4
# It will define QT_VERSION and QT_FOUND variables useful for tests
include("${PROJECT_NAME}_setup_qt")

add_library(pqTestSuite
    "pqTestRegistry.cxx"
)

set_property(TARGET pqTestSuite PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_property(TARGET pqTestSuite PROPERTY AUTOMOC TRUE)
set_property(TARGET pqTestSuite PROPERTY PUBLIC_HEADER
    "pqTestRegistration.h"
    "pqTestRegistry.h"
    "pqTestSuite.h"
)

if(UNIX)
    target_compile_options(pqTestSuite PRIVATE
        "-std=c++11"
    )
endif()

target_compile_definitions(pqTestSuite PRIVATE
    Wall
)

target_include_directories(pqTestSuite
    INTERFACE
        # for the dependers within the build
        #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        # for the external CMake dependers that use find_package to
        # import the target
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(pqTestSuite PUBLIC
    ${QT_LIBS}
)

configure_file(
    "${PROJECT_SOURCE_DIR}/pqTestConfig.h.in"
    "${PROJECT_BINARY_DIR}/pqTestConfig.h"
    @ONLY
)

########
## install/deploy phase of the library
install(
    TARGETS pqTestSuite EXPORT ${PROJECT_NAME}-targets
    DESTINATION "lib"
    PUBLIC_HEADER DESTINATION "include"
)

install(
    FILES
    "${PROJECT_BINARY_DIR}/pqTestConfig.h"
    DESTINATION "include"
)

install(
    FILES
    "${PROJECT_SOURCE_DIR}/cmake/include/${PROJECT_NAME}_setup_suite.cmake"
    DESTINATION "share/cmake/include"
)

# Generate and install the package configuration files ----------------
include("${PROJECT_NAME}_setup_package")
