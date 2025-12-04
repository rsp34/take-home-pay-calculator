#pragma once
#include <string>
#include <stdexcept>
#include <cctype>

int readPersonalAllowance(const std::string &code);
char readCategoryLetter(const std::string &code);
std::string validateTaxCode(const std::string &code);

class UKTaxCode
{
public:
    UKTaxCode(const std::string &code) : personalAllowance(readPersonalAllowance(code) * 10), categoryLetter(readCategoryLetter(code)) {};

    const float personalAllowance;
    const char categoryLetter;
};
