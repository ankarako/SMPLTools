cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# 3rd Party Path
set(3rdPartyPath "../../3rdParty")
get_filename_component(3rdPartyPath "${3rdPartyPath}" ABSOLUTE)
message(STATUS "Current 3rd party path: ${3rdPartyPath}")
# cmake modules path
set(ModulesPath "../../cmake")
get_filename_component(ModulesPath "${ModulesPath}" ABSOLUTE)
message(STATUS "Current cmake modules path: ${ModulesPath}")
set(CMAKE_MODULE_PATH "${ModulesPath}")
# modules
include(GroupSource)
include(PrintList)
# cmake project
project(
	SMPLToolsLib
	DESCRIPTION "Library for SMPL Tools"
	VERSION 0.1.0
	LANGUAGES CXX
)
# Gather source files
# configure the Config.inl file
set(RESOURCES_DIR "../../Resources")
get_filename_component(RESOURCES_DIR "${RESOURCES_DIR}" ABSOLUTE)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Public/Config.inl" "${CMAKE_CURRENT_SOURCE_DIR}/Public/Config.hpp" @ONLY)
# Public files
file(GLOB LibPublicFiles "Public/*.hpp")
GroupSource("${LibPublicFiles}" "Public")
PrintList("${LibPublicFiles}" "Gathered SMPLTool public library files")
# Private files
file(GLOB LibPrivateFiles "Private/*.cpp")
GroupSource("${LibPrivateFiles}" "Private")
PrintList("${LibPrivateFiles}" "Gathered SMPLTool private library files")
# library
add_library(
	SMPLToolsLib
	STATIC
	"${LibPublicFiles}"
	"${LibPrivateFiles}"
)
# set properties
set_target_properties(SMPLToolsLib PROPERTIES FOLDER "Lib")
target_include_directories(SMPLToolsLib PUBLIC "Public")

# dependencies
set(PYTHON_INCLUDE_DIR CACHE STRING "Python include directory")
set(PYTHON_LIBRARY_DIR CACHE STRING "Python libraries directory")
STRING(REGEX REPLACE "\\\\" "/" PYTHON_INCLUDE_DIR "${PYTHON_INCLUDE_DIR}")
STRING(REGEX REPLACE "\\\\" "/" PYTHON_LIBRARY_DIR "${PYTHON_LIBRARY_DIR}")
target_include_directories(SMPLToolsLib PRIVATE ${PYTHON_INCLUDE_DIR})
target_link_libraries(SMPLToolsLib PRIVATE debug "${PYTHON_LIBRARY_DIR}/python3_d.lib")
target_link_libraries(SMPLToolsLib PRIVATE debug "${PYTHON_LIBRARY_DIR}/python37_d.lib")
target_link_libraries(SMPLToolsLib PRIVATE optimized "${PYTHON_LIBRARY_DIR}/python3.lib")
target_link_libraries(SMPLToolsLib PRIVATE optimized "${PYTHON_LIBRARY_DIR}/python37.lib")
# fbx sdk (is in 3rdParty Path)
set(FBXSDK_INCLUDE_DIR "${3rdPartyPath}/FBXSDK\\include")
set(FBXSDK_LIBRARY_DIR "${3rdPartyPath}/FBXSDK\\lib\\vs2017\\x64")
target_include_directories(SMPLToolsLib PRIVATE ${FBXSDK_INCLUDE_DIR})
target_link_libraries(SMPLToolsLib PRIVATE debug "${FBXSDK_LIBRARY_DIR}/debug/libfbxsdk.lib")
target_link_libraries(SMPLToolsLib PRIVATE optimized "${FBXSDK_LIBRARY_DIR}/release/libfbxsdk.lib")
####################################################################################################
# Build Test
option(BUILD_TESTS "Set to additionally build unit tests" ON)
if(BUILD_TESTS)
	cmake_policy(SET CMP0079 NEW)
	add_subdirectory("Test")
	target_link_libraries(TestLoad PRIVATE SMPLToolsLib)
endif(BUILD_TESTS)

