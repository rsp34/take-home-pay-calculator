cmake_minimum_required(VERSION 3.10.0)
project(take-home-pay-calculator VERSION 0.1.0 LANGUAGES C CXX)

include_directories("include")

add_executable(take-home-pay-calculator
    main.cpp
    src/uk_tax_model.cpp)

