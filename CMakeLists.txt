cmake_minimum_required(VERSION 3.20)
project(web)


set(CMAKE_CXX_STANDARD 23)

add_executable(web test/main.cpp http/httpheader.h http/linux_httpserve.h http/router/router.h Cmdoule.h)


