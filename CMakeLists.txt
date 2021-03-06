project(TyaLogger)

set(CMAKE_CXX_STANDARD 11)

######### Common settings#########
set(BINDIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINDIR})


######### #########
add_subdirectory(spdlog)

set(TyaLogger_SOURCES
    TyaLoggerExport.h
    Logger.cpp
    )

add_definitions(-DYTA_BUILD_LOGGER)
add_library(TyaLogger SHARED ${TyaLogger_SOURCES})
remove_definitions(-DYTA_BUILD_LOGGER)

add_library(TyaLogger_s STATIC ${TyaLogger_SOURCES})
include_directories(spdlog/include)

######### for unit tests #########
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
enable_testing()

find_package(Qt5Test REQUIRED)

set(testfiles
    tests/loggingTest.cpp
    )

foreach(testfile ${testfiles})
    get_filename_component(testname ${testfile} NAME_WE)
    add_executable(${testname} ${testfile})
    target_link_libraries(${testname} TyaLogger_s)
    QT5_USE_MODULES(${testname} Test)

    add_test(${testname} ${BINDIR}/${testname})
endforeach(testfile)
