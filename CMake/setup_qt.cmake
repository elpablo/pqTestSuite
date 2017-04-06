set(QT_VERSION "4")

find_package(Qt5Test)

set(QT_FOUND Qt5Test_FOUND)
set(QT_VERSION "5")
set(QT_LIBS "Qt5::Test")

if(NOT Qt5Test_FOUND)
    mark_as_advanced(Qt5Test_DIR)

    find_package(Qt4)
    set(QT_FOUND Qt4_FOUND)

    if(Qt4_FOUND)
        set(QT_USE_QTEST ON)
        set(QT_VERSION "4")

        set(QT_LIBS ${QT_LIBRARIES} ${QT_QTTEST_LIBRARY})

        # Add manually the include directories because Qt4 has an old style CMake package
        include (${QT_USE_FILE})
        include_directories(BEFORE ${QT_INCLUDES})

        message(STATUS "The project will use Qt4 because Qt5 is not found.")
    endif()

endif()
