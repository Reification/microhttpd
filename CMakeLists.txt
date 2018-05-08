cmake_minimum_required(VERSION 3.11)

project(microhttpd LANGUAGES C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release" CACHE STRING "" FORCE)

#if we have the default install prefix (which we will never use) set to a reasonable test location
if("${CMAKE_INSTALL_PREFIX}" STREQUAL "C:/Program Files/microhttpd")
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE STRING "" FORCE)
endif()

set(BUILD_TESTS FALSE CACHE BOOL "Build simple manually run tests")
set(BUILD_TESTS_AS_LIBS FALSE)

set(LIB_SRC_DIR "src/microhttpd")
set(API_HDR_DIR "src/include")
set(API_GEN_HDR_DIR "${CMAKE_BINARY_DIR}/include")

set(LINK_LIBS)

if(WIN32)
  configure_file("w32/common/MHD_config.h" "${API_GEN_HDR_DIR}/MHD_config.h" COPYONLY)
  set(LINK_LIBS "ws2_32.lib")
  string(REGEX REPLACE "/W[0-4]" "/W0" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
  add_definitions(-DMHD_W32LIB -D_CRT_NONSTDC_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
elseif(ANDROID)
  set(BUILD_TESTS_AS_LIBS TRUE)
  message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} NYI")
elseif(APPLE)
  message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} NYI")
else()
  message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} NYI")
endif()

file(GLOB LIB_SRC "${LIB_SRC_DIR}/*.c")
file(GLOB LIB_HDR "${LIB_SRC_DIR}/*.h")

list(FILTER LIB_SRC EXCLUDE REGEX "/test_")
list(FILTER LIB_SRC EXCLUDE REGEX "/connection_https")
list(FILTER LIB_HDR EXCLUDE REGEX "/test_")
list(FILTER LIB_HDR EXCLUDE REGEX "/connection_https")

file(GLOB API_HDR "${API_HDR_DIR}/*.h" "${API_GEN_HDR_DIR}/*.h")

include_directories(
 ${PROJECT_NAME}
 ${API_HDR_DIR}
 ${API_GEN_HDR_DIR}
 ${LIB_SRC_DIR}
)

add_library(${PROJECT_NAME} STATIC ${LIB_SRC} ${LIB_HDR} ${API_HDR})
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_FLAGS "-DBUILDING_MHD_LIB")

source_group("API" FILES ${API_HDR})

if(BUILD_TESTS)
  set(TESTS hellobrowser simplepost largepost)
  foreach(TEST ${TESTS})
    if(BUILD_TESTS_AS_LIBS)
      add_library("${TEST}" SHARED doc/examples/${TEST}.c)
    else()
      add_executable("${TEST}" doc/examples/${TEST}.c)
    endif()
    set_target_properties("${TEST}" PROPERTIES FOLDER "Tests")
    target_link_libraries("${TEST}" ${PROJECT_NAME} ${LINK_LIBS})
  endforeach()
endif()

install(FILES $<TARGET_FILE:${PROJECT_NAME}> DESTINATION lib)
install(FILES ${API_HDR} DESTINATION include/${PROJECT_NAME})
