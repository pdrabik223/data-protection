cmake_minimum_required(VERSION 3.21)
project(data_protection)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-march=native -ffast-math)

add_executable(substitution_cipher
        "simple_substitution_cipher/main.cpp"
        "simple_substitution_cipher/substitution_cipher.cpp"
        "simple_substitution_cipher/substitution_cipher.h"
        "simple_substitution_cipher/statistical_attack.h"
        "simple_substitution_cipher/statistical_attack.cpp" primes/primes.cpp)

add_executable(vingenere_cipher
        "Vigenere/main.cpp"
        "Vigenere/vingenere_cipher.h"
        "Vigenere/vingenere_cipher.cpp"
        "Vigenere/attack_vingenere.h"
        "Vigenere/attack_vingenere.cpp" Vigenere/kasiski_attack.h Vigenere/krasiski_attack.cpp)

add_executable(primes primes/primes.cpp)

add_executable(modulo_power  modulo-power/main.cpp RSE.cpp adler_djb.cpp BW_table.cpp)
add_executable(rse RSE.cpp)
add_executable(adler_djb adler_djb.cpp)
add_executable(bw_table BW_table.cpp)