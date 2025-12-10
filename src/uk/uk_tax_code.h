#pragma once
#include <string>
#include <stdexcept>
#include <cctype>
#include <cstdint>

int64_t readPersonalAllowance(const std::string &code);
char readCategoryLetter(const std::string &code);
std::string validateTaxCode(const std::string &code);

inline constexpr int64_t PENNIES_IN_POUND = 100;
inline constexpr int64_t PERSONAL_ALLOWANCE_TO_POUNDS = 10;

class UKTaxCode
{
public:
    UKTaxCode(const std::string &code) : personalAllowance(readPersonalAllowance(code) * PERSONAL_ALLOWANCE_TO_POUNDS * PENNIES_IN_POUND), categoryLetter(readCategoryLetter(code)) {};

    const int64_t personalAllowance;
    const char categoryLetter;
};
