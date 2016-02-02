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
 *  pqTestRegistry.cxx
 *  pqTestSuiteEngine
 *
 *  Created by Paolo Quadrani on 19/01/15.
 *
 */

#include "pqTestRegistry.h"

pqTestRegistry* pqTestRegistry::instance() {
    static pqTestRegistry registry;
	return &registry;
}

void pqTestRegistry::registerTest(QObject* test) {
    m_TestSuite += test;
}

int pqTestRegistry::runTests(int argc, char* argv[]) {
	int result = 0;
    Q_FOREACH(QObject* test, m_TestSuite) {
		result |= QTest::qExec(test, argc, argv);
	}
	return result;
}
