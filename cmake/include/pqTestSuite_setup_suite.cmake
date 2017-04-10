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

macro(pqSetupTestSuite)
    # Extract current directory name to use as project name
    file(GLOB CUR_FILE "CMakeLists.txt")
    get_filename_component(CUR_ABSOLUTE_DIR ${CUR_FILE} PATH)
    get_filename_component(TEST_SUITE_NAME ${CUR_ABSOLUTE_DIR} NAME)

    file(GLOB implementation_file_list_cpp "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    file(GLOB implementation_file_list_cxx "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx")

    set(SOURCE_FILES
        ${implementation_file_list_cpp}
        ${implementation_file_list_cxx}
    )

    add_executable(${TEST_SUITE_NAME}
        ${SOURCE_FILES}
    )

    set_property(TARGET ${TEST_SUITE_NAME} PROPERTY AUTOMOC TRUE)

    target_compile_definitions(${TEST_SUITE_NAME} PRIVATE
        Wall
    )

    target_include_directories(${TEST_SUITE_NAME}
        PRIVATE
            "${INCLUDE_PATH}"
            "${CMAKE_CURRENT_BINARY_DIR}"
    )

    target_link_libraries(${TEST_SUITE_NAME} PUBLIC
        ${QT_LIBRARIES}
        pqTestSuite::pqTestSuite
        ${LIBRARIES_DEPENDENCIES}
    )

    install(TARGETS ${TEST_SUITE_NAME} DESTINATION "bin")

endmacro()
