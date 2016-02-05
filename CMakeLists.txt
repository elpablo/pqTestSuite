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

cmake_minimum_required(VERSION 2.8.11)

project(pqTestSuite)

add_definitions("-Wall")

enable_testing()
set(QT_VERSION "4")

# This library is based on Qt
set (QT_REQUIRED TRUE)
if (NOT QT_FOUND)
  # Search for installed Qt
  find_package(Qt5Test)
  if (NOT Qt5Test_DIR)
    find_package(Qt4)
  else()
    set(QT_FOUND TRUE)
    set(QT_VERSION "5")
  endif()
endif()

if (NOT QT_FOUND)
  message(FATAL_ERROR
      "pqTestSuite require QtTest to be enabled."
      "Please install Qt4 or Qt5 and run again the CMake on this project.")
endif ()

if (QT_VERSION VERSION_GREATER "4")
  include_directories(${Qt5Test_INCLUDE_DIRS})
  add_definitions(${Qt5Test_DEFINITIONS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Test_EXECUTABLE_COMPILE_FLAGS}")
else()
  include (${QT_USE_FILE})
  include_directories(BEFORE ${QT_INCLUDES})
endif()
mark_as_advanced(QT_QMAKE_EXECUTABLE)

SET (TEST_SUITE_SOURCE_FILES
    pqTestRegistration.h
    pqTestRegistry.cxx
    pqTestSuite.h
)

set(TEST_DATA_DIR "" CACHE PATH "Path to the root directory of the data used for tests")

add_library(${PROJECT_NAME} SHARED ${TEST_SUITE_SOURCE_FILES} ${TEST_SUITE_MOC_SRCS} ${TEST_SUITE_UI_SOURCES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${QT_QTTEST_LIBRARY})

# Configure the Config file containing pqTestSuite and Test Data useful variables.
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/pqTestConfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/pqTestConfig.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

# Configure the Use file
set(PQTESTSUITE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})

if (QT_VERSION VERSION_GREATER "4")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/UsepqTestSuite-Qt5.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/UsepqTestSuite.cmake)
else()
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/UsepqTestSuite-Qt4.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/UsepqTestSuite.cmake)
endif()

# Install the library
install(TARGETS pqTestSuite DESTINATION ${CMAKE_INSTALL_PREFIX}/lib INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pqTestConfig.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/UsepqTestSuite.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/CMake DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
