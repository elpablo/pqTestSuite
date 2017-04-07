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
#  pqCreateTestSuite.cmake
#
#  Created by Paolo Quadrani on 11/11/15.
#
#

MACRO(pqCreateTestSuite)

include_directories(
    "${PQTESTSUITE_INCLUDE_DIR}"
    "${INCLUDE_PATH}"
    "${PROJECT_BINARY_DIR}"
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${MY_MOC_CXX})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES} ${QT_QTTEST_LIBRARY} ${PQTESTSUITE_LIBRARY} ${LIBRARIES_DEPENDENCIES})

ENDMACRO()
