cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(3rdPartyPath "3rdParty/")
get_filename_component(3rdPartyPath "${3rdPartyPath}" ABSOLUTE)
message(STATUS "Current 3rd party path: ${3rdPartyPath}")

project(
	SMPLTools
	DESCRIPTION "Tools for handling SMPL Models"
	VERSION 0.1.0
	LANGUAGES CXX
)
# Gather source files
