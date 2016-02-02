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

#
#  pqInitTestSuiteProject.cmake
#
#  Created by Paolo Quadrani on 22/10/15.
#
#

MACRO(pqInitTestSuiteProject)

# Extract current directory name to use as project name
file(GLOB CUR_FILE "CMakeLists.txt")
get_filename_component(CUR_ABSOLUTE_DIR ${CUR_FILE} PATH)
get_filename_component(DIR_NAME ${CUR_ABSOLUTE_DIR} NAME)

# Add new project
PROJECT(${DIR_NAME})

add_definitions("-Wall")

FILE(GLOB implementation_file_list_cpp "${PROJECT_SOURCE_DIR}/*.cpp")
FILE(GLOB implementation_file_list_cxx "${PROJECT_SOURCE_DIR}/*.cxx")

SET (SOURCE_FILES
    ${implementation_file_list_cpp}
    ${implementation_file_list_cxx}
)

####################################################################
# Add test
####################################################################

foreach(FILE_NAME_ABS ${SOURCE_FILES})
    ## extract the base file name.
    get_filename_component(FILE_NAME ${FILE_NAME_ABS} NAME_WE)
    ## Exclude the main.cpp file (it doesn't ned to be 'mocced')
    if(NOT ${FILE_NAME} STREQUAL "main")
        ## Assign the moc custom filename
        set(MOC_FILE "${FILE_NAME}.moc")
        if (QT_VERSION_MAJOR VERSION_GREATER "4")
          QT5_GENERATE_MOC(${FILE_NAME_ABS} ${MOC_FILE})
        else ()
          QT4_GENERATE_MOC(${FILE_NAME_ABS} ${MOC_FILE})
        endif()
        LIST(APPEND MY_MOC_CXX "${PROJECT_BINARY_DIR}/${MOC_FILE}")
    endif(NOT ${FILE_NAME} STREQUAL "main")
endforeach()

ENDMACRO()
