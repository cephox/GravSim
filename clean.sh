#!/bin/bash

# Removing files:
rm -f gravsim
rm -f Makefile
find . -type f -name "Makefile" -delete
find . -type f -name "CMakeCache.txt" -delete
find . -type f -name "cmake_install.cmake" -delete

# Removing directories:
find . -type d -name "CMakeFiles" -exec rm -rv {} +