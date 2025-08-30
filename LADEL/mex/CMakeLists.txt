cmake_minimum_required(VERSION 3.23...4.1)
project(LADEL-mex)

# Find the Matlab MEX compiler:
find_package(Matlab REQUIRED COMPONENTS MEX_COMPILER)

# Compile the utility library
add_library(mex_util STATIC src/ladel_mex_util.c)
target_link_libraries(mex_util PUBLIC LADEL::ladel Matlab::mex)
target_sources(mex_util PUBLIC FILE_SET HEADERS
    BASE_DIRS "include"
    FILES "include/ladel_mex_util.h")
add_library(LADEL::mex_util ALIAS mex_util)

# Create a target for compiling a MEX function:
matlab_add_mex(
    NAME ladel_mex                    # Name for use in Matlab
    SRC src/ladel_mex.c               # Source files to compile
    LINK_TO LADEL::mex_util           # Dependencies
)

# Install the final MEX file
install(FILES $<TARGET_FILE:ladel_mex>
        ladel.m
        EXCLUDE_FROM_ALL
        COMPONENT mex_interface
        DESTINATION @ladel)