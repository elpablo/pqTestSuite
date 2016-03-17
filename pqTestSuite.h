/***************************************************************************
 Copyright [2015 - 2020] [Paolo Quadrani]

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 ***************************************************************************/

/*
 *  pqTestSuite.h
 *  pqTestSuiteEngine
 *
 *  Created by Paolo Quadrani on 19/01/15.
 *
 */

#ifndef pqTestSuite_H
#define pqTestSuite_H

// Includes list
#include "pqTestRegistration.h"
#include "pqTestConfig.h"

#define PQ_TESTSUITE_MAIN() \
int main(int argc, char *argv[]) \
{ \
    QCoreApplication app(argc, argv); \
    int result= pqTestRegistry::instance()->runTests(argc, argv); \
    return result; \
}
#define PQ_GUI_TESTSUITE_MAIN() \
int main(int argc, char *argv[]) \
{ \
    QApplication app(argc, argv); \
    int result= pqTestRegistry::instance()->runTests(argc, argv); \
    return result; \
}

// Define check macros
#define pqVERIFY QVERIFY2
#define pqVERIFY_FALSE(false_stm, comment) QVERIFY2(!(false_stm), comment)
#define pqVERIFY_NULL(null_ptr, comment) QVERIFY2((null_ptr) == NULL, comment)
#define pqVERIFY_NOT_NULL(null_ptr, comment) QVERIFY2((null_ptr) != NULL, comment)
#define pqVERIFY_GREATER_THEN(value, ref_val, comment) QVERIFY2((value) > (ref_val), comment)
#define pqVERIFY_GREATER_THEN_OR_EQUAL(value, ref_val, comment) QVERIFY2((value) >= (ref_val), comment)
#define pqVERIFY_LOWER_THEN(value, ref_val, comment) QVERIFY2((value) < (ref_val), comment)
#define pqVERIFY_LOWER_THEN_OR_EQUAL(value, ref_val, comment) QVERIFY2((value) <= (ref_val), comment)
#define pqCOMPARE QCOMPARE

#endif // pqTestSuite_H
