#include "uk_tax_model.h"
#include <cctype>
#include <stdexcept>
#include <string>



// TaxCode


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