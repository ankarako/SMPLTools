cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# cmake project
project(
	SMPLToolsLibTests
	DESCRIPTION "Unit Tests for SMPL Tools library"
	VERSION 0.1.0
	LANGUAGES CXX
)

add_executable(
	TestLoad
	"TestLoad.cpp"
)
set_target_properties(TestLoad PROPERTIES FOLDER "Tests")