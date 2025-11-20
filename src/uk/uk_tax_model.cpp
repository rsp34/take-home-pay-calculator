#include "uk_tax_model.h"
#include <cctype>
#include <stdexcept>
#include <string>

// PersonalAllowance
PersonalAllowance::PersonalAllowance(int v) { set(v); }
void PersonalAllowance::set(int v) { value = v * 10; }
int PersonalAllowance::get() const { return value; }

// TaxCode
TaxCode::TaxCode(const std::string &code) : rawCode{code}, pa(parseDigits(code)) {};

int TaxCode::getPersonalAllowance() const { return pa.get(); };

bool TaxCode::isValidTaxCode() const
{
    if (rawCode.size() < 4)
        return false;
    for (int i = 0; i < 4; ++i)
        if (!std::isdigit(rawCode[i]))
            return false;
    return true;
}

int TaxCode::parseDigits(const std::string &code)
{
    return std::stoi(code.substr(0, 4));
};