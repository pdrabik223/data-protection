cmake_minimum_required(VERSION 3.21)
project(data_protection)

set(CMAKE_CXX_STANDARD 14)

add_executable(substitution_cipher
        "simple_substitution_cipher/main.cpp"
        "simple_substitution_cipher/substitution_cipher.cpp"
        "simple_substitution_cipher/substitution_cipher.h"
        "simple_substitution_cipher/statistical_attack.h"
        "simple_substitution_cipher/statistical_attack.cpp")
