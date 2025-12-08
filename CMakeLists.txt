cmake_minimum_required(VERSION 3.10.0)
project(take-home-pay-calculator VERSION 0.1.0 LANGUAGES C CXX)

# Enable C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(take-home-pay-calculator
    main.cpp
    src/uk/uk_tax_code.cpp)

