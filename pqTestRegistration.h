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
 *  pqTestRegistration.h
 *  pqTestSuiteEngine
 *
 *  Created by Paolo Quadrani on 19/01/15.
 *
 */

#ifndef pqTestRegistration_H
#define pqTestRegistration_H

// Includes list
#include "pqTestRegistry.h"

/**
 * A macro to register a test class.
 *
 * This macro will create a static variable which registers the
 * testclass with the pqTestRegistry, and creates an instance of the
 * test class.
 *
 * Execute this macro in the body of your unit test's .cpp file, e.g.
 *    class MyTest {
 *			...
 *		};
 *
 *		PQ_REGISTER_TEST(MyTest);
 */

#define PQ_REGISTER_TEST(TestClass) \
    static pqTestRegistration<TestClass> TestClass##Registration

    /**
     * A wrapper class around a test to manage registration and static
     * creation of an instance of the test class.
       * This class is used by PQ_REGISTER_TEST(), and you should not
     * use this class directly.
     */
      template<typename T>
      class pqTestRegistration {
  		public:
          ///!brief Registration class constructor.
          /** The constructor also register also the test passed as typename into the test suite registry. */
          pqTestRegistration() {
              m_TestToRegister = new T();
              pqTestRegistry::instance()->registerTest(m_TestToRegister);
    			}

          ///!brief Registration class destructor
          ~pqTestRegistration() {
              delete m_TestToRegister;
    			}

  		private:
          T* m_TestToRegister; ///< Test to be registered into the test suite.
  	};

#endif //pqTestRegistration_H
