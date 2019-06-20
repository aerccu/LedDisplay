cmake_minimum_required(VERSION 3.0.0)
project(leddisp VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR})



set(HEADER_FILES ${PROJECT_SOURCE_DIR}/include/leddisp.h
                ${PROJECT_SOURCE_DIR}/include/canvas.h
                ${PROJECT_SOURCE_DIR}/include/gpio.h
                ${PROJECT_SOURCE_DIR}/include/pmapper.h
                ${PROJECT_SOURCE_DIR}/include/thread.h)


set(LIB_FILES ${PROJECT_SOURCE_DIR}/lib/leddisp.cpp
              )

add_library(leddisp ${HEADER_FILES} ${LIB_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

