cmake_minimum_required(VERSION 3.5)

add_executable(intro main.cpp)
target_compile_features(intro PRIVATE cxx_lambda_init_captures)