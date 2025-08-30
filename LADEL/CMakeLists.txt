cmake_minimum_required(VERSION 3.23...4.1)
project(LADEL VERSION 0.0.4)

option (LADEL_SIMPLE_COL_COUNTS
    "Simplify symbolic analysis (worse asymptotic time complexity)" On)
option (LADEL_USE_AMD
    "Use approximate minimum degree ordering" On)
option (LADEL_64BIT_INDICES
    "Use 64-bit integers for indexing" On)
option (LADEL_SINGLE_PRECISION
    "Use single precision floats instead of double" Off)
option (LADEL_WITH_MEX
    "Compile the MATLAB interface" Off)

if (LADEL_WITH_MEX AND LADEL_SINGLE_PRECISION)
    message(FATAL_ERROR "The MEX interface is not available in single-precision")
endif()

# Main LADEL library
add_library(ladel 
    "src/ladel_debug_print.c"
    "src/ladel_scale.c"
    "src/ladel_upper_diag.c"
    "src/ladel_col_counts.c"
    "src/ladel_ldl_symbolic.c"
    "src/ladel_global.c"
    "src/ladel_ldl_numeric.c"
    "src/ladel_add.c"
    "src/ladel_transpose.c"
    "src/ladel_etree.c"
    "src/ladel_permutation.c"
    "src/ladel_matvec.c"
    "src/ladel_postorder.c"
    "src/ladel_copy.c"
    "src/ladel_pattern.c"
    "src/ladel_submatrix.c"
    "src/ladel_row_mod.c"
    "src/ladel.c"
    "src/ladel_matmat.c"
    "src/ladel_rank1_mod.c"
)
target_sources(ladel PUBLIC FILE_SET HEADERS
    BASE_DIRS "include"
    FILES "include/ladel_add.h"
          "include/ladel_col_counts.h"
          "include/ladel_constants.h"
          "include/ladel_copy.h"
          "include/ladel_debug_print.h"
          "include/ladel_etree.h"
          "include/ladel_global.h"
          "include/ladel.h"
          "include/ladel_ldl_numeric.h"
          "include/ladel_ldl_symbolic.h"
          "include/ladel_matmat.h"
          "include/ladel_matvec.h"
          "include/ladel_pattern.h"
          "include/ladel_permutation.h"
          "include/ladel_postorder.h"
          "include/ladel_rank1_mod.h"
          "include/ladel_row_mod.h"
          "include/ladel_scale.h"
          "include/ladel_submatrix.h"
          "include/ladel_transpose.h"
          "include/ladel_types.h"
          "include/ladel_upper_diag.h"
)
target_compile_definitions(ladel PUBLIC 
    $<$<BOOL:${LADEL_SIMPLE_COL_COUNTS}>:LADEL_SIMPLE_COL_COUNTS>
    $<$<BOOL:${LADEL_64BIT_INDICES}>:LADEL_64BIT_INDICES>
    $<$<BOOL:${LADEL_SINGLE_PRECISION}>:LADEL_SINGLE_PRECISION>)
if (LADEL_USE_AMD)
    target_compile_definitions(ladel PUBLIC LADEL_USE_AMD)
    add_subdirectory(../thirdparty/SuiteSparse SuiteSparse EXCLUDE_FROM_ALL)
    target_link_libraries(ladel PRIVATE ladel_amd)
endif()
# TODO: this is probably too much
set_target_properties(ladel PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS True)
add_library(${PROJECT_NAME}::ladel ALIAS ladel)

# Sanity check
include(CheckTypeSize)
CHECK_TYPE_SIZE("long long" LONG_LONG_SIZE BUILTIN_TYPES_ONLY LANGUAGE C)
if (NOT LONG_LONG_SIZE EQUAL 8)
    message(WARNING "The C type long long does not appear to be 64 bits wide, "
                    "make sure that the integer types are compatible with "
                    "SuiteSparse.")
endif()

# MATLAB interface
if (LADEL_WITH_MEX)
    add_subdirectory(mex)
endif()

# Installation
include(cmake/Install.cmake)

# Packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../README.md")
SET(CPACK_GENERATOR "DEB;TGZ")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Pieter P")
include(CPack)