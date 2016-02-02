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
 *  pqTestRegistry.h
 *  pqTestSuiteEngine
 *
 *  Created by Paolo Quadrani on 19/01/15.
 *
 */

#ifndef pqTestRegistry_H
#define pqTestRegistry_H

// Includes list
#include <QtTest/QtTest>

// Class forwarding list

/**
 * A registry of QtTest test classes.
 * All test classes registered with MAF_REGISTER_TEST add
 * themselves to this registry. All registered tests can then be run at
 * once using runTests().
 */
class pqTestRegistry {
public:
    ///!brief Retrieve the single instance of the registry.
    static pqTestRegistry* instance();

    ///!brief Register a QtTest test.
    /** This method is called  by PQ_REGISTER_TEST, and you should
      not use this method directly.
     */
    void registerTest(QObject*);

    ///!brief Run all registered tests using QTest::qExec()
    int runTests(int argc, char* argv[]);

private:
    ///!brief Private constructor for the singletone.
    pqTestRegistry() {}

		private:
    QList<QObject*> m_TestSuite; ///< Test suite list
};

#endif // pqTestRegistry_H
