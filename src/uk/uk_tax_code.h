#pragma once
#include <string>
#include <stdexcept>

int readPersonalAllowance(const std::string &code);
char readCategoryLetter(const std::string &code);
std::string validateTaxCode(const std::string &code);

class UKTaxCode
{
public:
    UKTaxCode(const std::string& code) : rawCode{validateTaxCode(code)}, personalAllowance(readPersonalAllowance(code) * 10), categoryLetter(readCategoryLetter(code)) {};

    float personalAllowance;
    char categoryLetter;

private:
    std::string rawCode;
};
