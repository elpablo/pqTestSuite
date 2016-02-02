# pqTestSuite

[![Twitter: @KauseFx](http://img.shields.io/badge/contact-@quadrani-blue.svg?style=flat)](https://twitter.com/quadrani)
[![License](https://img.shields.io/hexpm/l/plug.svg?style=flat)](http://www.apache.org/licenses/LICENSE-2.0)

-------
### Requirements
- **CMake** (version greater then 2.8.11)
- **Qt4** or greater

### Description
**pqTestSuite** is a library that improve the Qt framework used for testing: *QTest*. It creates a unique executable for all the test cases of the test suite. At the end of the execution of the test suite it will print a report for the passed and failed tests.

To compile and install the library do the following steps:
```
# Clone the sources
git clone https://github.com/elpablo/pqTestSuite.git

# Create the build and install directory
mkdir -p pqTestSuite_Build/Install

# Run the CMake
cmake-gui &
```
When CMake GUI appears, assign the **CMAKE_BUILD_TYPE** to Debug or Release, assign to the **CMAKE_INSTALL_PREFIX** the path of the Install directory you have created in the previous step and if you have a directory used to contains the test data assign it to the **TEST_DATA_DIR** key.

Press the *Configure* button until all the red CMake entries are white and all the information are filled, then press the *Generate* button to create the Makefile to compile the library.

Now go into the **pqTestSuite_Build** directory you have created before and run the following command:
```
make && make install
```
In the **Install** directory you will find the use-file of the library and the directories that contains the compiled shared library and the include files.

### Usage
The easiest way to use the library is with CMake.

In your CMakeLists.txt file of your project you should include the **UsepqTestSuite.cmake** file (that you will find in the install directory of the library) in this way:

```
# Add the lines below in your CMakeLists.txt file
set(PQTESTSUITE_INSTALL_DIR "" CACHE PATH "Path to the pqTestSuite install directory")
include(${PQTESTSUITE_INSTALL_DIR}/UsepqTestSuite.cmake)
```

Now to add a new test suite in your project simply follow these steps:
- Create a directory that will contains all your tests. The directory name will be the name of the executable that will be generated (your test suite's name))
- Put in it a file **main.cxx** that contains the following code:

```
# main.cxx file
#include <QCoreApplication>
#include "pqTestSuite.h"

PQ_TESTSUITE_MAIN()
```

Create inside your test suite's directory also a **CMakeLists.txt** file containing the following code (fill the **INCLUDE_PATH** and **LIBRARIES_DEPENDENCIES** as needed by your code):

```
# Set minimal cmake version which can be used
cmake_minimum_required(VERSION 2.8.11)

pqInitTestSuiteProject()

add_definitions("-Wall")

# Directory of the source files to test relative to the Test suite directory (or as absolute path)
set(INCLUDE_PATH
    # write here your custom include paths for the code to be tested...
)

# Libraries to be linked by the test suite
set(LIBRARIES_DEPENDENCIES
    # write here your custom libraries that the test depends on.
)

pqCreateTestSuite()
```

Now you can start adding your files (with extension .cxx or .cpp) containing the test cases. The test files are added to the test suite as soon as you create them and put them into the directory (**you don't need to edit anymore the CMakeLists.txt file**).

Suppose that you have created a test file called **MyFirstTest.cxx**. The basic content of the file will be:

```
#include "pqTestSuite.h"
// Add here your needed includes

/**
 Class name: MyFirstTest
 This class implements the test suite for TestedClass.
 */
class MyFirstTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  /// Initialize test variables
  void initTestCase()
  {
      // Put here your variable initialization
      // ...
  }

  /// Cleanup test variables memory allocation.
  void cleanupTestCase()
  {
      // Put here your cleanup code
      // ...
  }

  /// Example of test case method
  void myTest();

  // Add here other test cases
  // ...

private:
  // Put here your member variable used by the test suite
};

void MyFirstTest::startTest()
{
  // Vrite here your test conditions...
  int a = 0
  QVERIFY(a == 0);

  QString s = "test";
  QCOMPARE(s, QString("test"));
}

// If you want to disable the test execution from the test engine, just comment the line below of the registration macro.
PQ_REGISTER_TEST(MyFirstTest);
#include "MyFirstTest.moc"
```
