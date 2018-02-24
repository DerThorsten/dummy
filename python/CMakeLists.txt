# dependencies
find_package(xtensor REQUIRED)
find_package(xtensor-python REQUIRED)
find_package(pybind11 REQUIRED)
find_package(NUMPY REQUIRED)



# name of the target 
set(${PROJECT_NAME}_PYTHON_INTERFACE_TARGET python_interface_${PROJECT_NAME})

# all header for the python module
file(GLOB_RECURSE ${PROJECT_NAME}_PYTHON_SRC_FILES 
     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
list(REMOVE_ITEM ${PROJECT_NAME}_PYTHON_SRC_FILES  src/main.cpp)

# add the python module via pybind11 cmake-function
pybind11_add_module( ${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET} 
    src/main.cpp
    ${${PROJECT_NAME}_PYTHON_SRC_FILES})

# set the OUTPUT_NAME to match the python module name
set_target_properties(${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET} 
    PROPERTIES OUTPUT_NAME _cpptools )

# include dependencies directories
target_include_directories(  ${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET} PRIVATE 
    "$<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR};${xtensor_INCLUDE_DIRS};${xtensor-python_INCLUDE_DIR};${pybind11_INCLUDE_DIRS};${PYTHON_NUMPY_INCLUDE_DIR}>"
)


# move the target to a folder with the proper name
# create folder with the proper name
SET(PY_MOD_FOLDER_NAME cpptools)
file(MAKE_DIRECTORY ${PY_MOD_FOLDER_NAME})

add_custom_command(TARGET ${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET} POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET}>"
     "${PY_MOD_FOLDER_NAME}/$<CONFIGURATION>/$<TARGET_FILE_NAME:${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET}>" 
  COMMENT "move python extension")


# move the init file 
add_custom_command(TARGET ${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/py/__init__.py ${PY_MOD_FOLDER_NAME}/
)
#################################
# INSTALL THE PYTHON MODULE
#################################

IF(NOT DEFINED PYTHON_MODULE_INSTALL_DIR OR PYTHON_MODULE_INSTALL_DIR MATCHES "^$")


    execute_process(
      COMMAND "${PYTHON_EXECUTABLE}" -c "if True:
        from distutils import sysconfig as sc
        print(sc.get_python_lib(prefix='', plat_specific=True))"
      OUTPUT_VARIABLE PYTHON_SITE
      OUTPUT_STRIP_TRAILING_WHITESPACE)

    execute_process(
      COMMAND "${PYTHON_EXECUTABLE}" -c "from __future__ import print_function; from distutils.sysconfig import get_python_lib; print(get_python_lib())"
      OUTPUT_VARIABLE PYTHON_SITE
      OUTPUT_STRIP_TRAILING_WHITESPACE)

    SET(PYTHON_MODULE_INSTALL_DIR ${PYTHON_SITE})

ENDIF()

SET(PYTHON_MODULE_INSTALL_DIR ${PYTHON_MODULE_INSTALL_DIR}
    CACHE PATH "where to install the Nifty Python package" FORCE)

# this is the install path relative to CMAKE_INSTALL_PREFIX,
# use this in INSTALL() commands to get packaging right
FILE(RELATIVE_PATH PYTHON_MODULE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX} ${PYTHON_MODULE_INSTALL_DIR})

install(TARGETS  ${${PROJECT_NAME}_PYTHON_INTERFACE_TARGET} DESTINATION ${PYTHON_MODULE_INSTALL_DIR}/${PY_MOD_FOLDER_NAME})