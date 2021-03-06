cmake_minimum_required(VERSION 3.11)

project(microhttpd LANGUAGES C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(INSTALL_TO_REIFY_OMNIBUS FALSE CACHE BOOL "Set install location for iterative testing with ReifyOminbus project")

#if we want to iterate on this library in ReifyOmnibus install it to the unpacked 3rd party location for that project
if(INSTALL_TO_REIFY_OMNIBUS AND (NOT "${CMAKE_INSTALL_PREFIX}" MATCHES "ReifyOmnibus"))
	if(WIN32)
		set(_PLAT "win64")
	elseif(ANDROID)
		set(_PLAT "android")
	endif()
  	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../ReifyOmnibus/build/${_PLAT}/ext" CACHE STRING "" FORCE)
	unset(_PLAT)
#if we have the default install prefix (which we will never use) set to a reasonable test location
elseif((NOT CMAKE_INSTALL_PREFIX) OR ("${CMAKE_INSTALL_PREFIX}" MATCHES "/Program Files"))
	set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE STRING "" FORCE)
endif()

set(BUILD_TESTS FALSE CACHE BOOL "Build simple manually run tests")
set(BUILD_TESTS_AS_LIBS FALSE)

set(LIB_SRC_DIR "src/microhttpd")
set(API_HDR_DIR "src/include")

set(LINK_LIBS)

if(WIN32)
  set(API_PLAT_HDR_DIR "w32/common")
  string(REGEX REPLACE "/W[0-4]" "/W0" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
  add_definitions(-DMHD_W32LIB -D_CRT_NONSTDC_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
elseif(ANDROID)
  set(API_PLAT_HDR_DIR "android")
  #set(LINK_LIBS "libsocket.a")
  set(BUILD_TESTS_AS_LIBS TRUE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-tautological-constant-out-of-range-compare")
elseif(APPLE)
  set(API_PLAT_HDR_DIR "darwin")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-tautological-constant-out-of-range-compare")
else()
  message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} NYI")
endif()

set(API_CONFIG_HDR ${API_PLAT_HDR_DIR}/MHD_config.h)

file(GLOB LIB_SRC "${LIB_SRC_DIR}/*.c")
file(GLOB LIB_HDR "${LIB_SRC_DIR}/*.h")

list(FILTER LIB_SRC EXCLUDE REGEX "/test_")
list(FILTER LIB_SRC EXCLUDE REGEX "/connection_https")
list(FILTER LIB_HDR EXCLUDE REGEX "/test_")
list(FILTER LIB_HDR EXCLUDE REGEX "/connection_https")

#promoting these to API
list(FILTER LIB_HDR EXCLUDE REGEX "/mhd_str.h")
list(FILTER LIB_HDR EXCLUDE REGEX "/mhd_limits.h")

file(GLOB API_HDR "${API_HDR_DIR}/*.h" ${API_CONFIG_HDR} ${LIB_SRC_DIR}/mhd_str.h ${LIB_SRC_DIR}/mhd_limits.h)

include_directories(
 ${PROJECT_NAME}
 ${API_HDR_DIR}
 ${API_PLAT_HDR_DIR}
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
