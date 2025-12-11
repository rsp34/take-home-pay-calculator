cmake_minimum_required(VERSION 3.10.0)
project(take-home-pay-calculator VERSION 0.1.0 LANGUAGES C CXX)

# Enable C++20
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(take-home-pay-calculator
    main.cpp
    
    # Tax framework
    src/tax/tax_registry.cpp
    src/tax/cumulative_tax_strategy.cpp
    src/tax/flat_tax_strategy.cpp
    
    # Pay system
    src/pay/pay_item.cpp
    src/pay/payslip.cpp
    
    # UK specific
    src/uk/uk_income_tax.cpp
    src/uk/uk_employee_ni.cpp
    src/uk/uk_tax_code.cpp
    src/uk/uk_tax_setup.cpp
    src/uk/uk_pay_item_factory.cpp
)
