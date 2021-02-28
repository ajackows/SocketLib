cmake_minimum_required(VERSION 2.8)
project( socketTest )


#add h file directory
include_directories("${PROJECT_SOURCE_DIR}/include")

#add external source files
aux_source_directory(src APP_SRC_FILES)

#comple and link everything
add_executable(socketTest socketTest.cpp ${APP_SRC_FILES})
