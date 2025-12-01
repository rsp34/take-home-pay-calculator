#include "./uk_tax_model.h"

// TaxCode
bool UKTaxCode::isValidTaxCode() const
{
    if (rawCode.size() < 4)
        return false;

    for (int i = 0; i < 4; ++i)
        if (!std::isdigit(rawCode[i]))
            return false;

    char letter = rawCode.back();
    std::string validLetters = "LMPTY";
    if (validLetters.find(letter) == std::string::npos) return false;
    return true;
}

int readPersonalAllowance(const std::string &code)
{
    return std::stoi(code.substr(0, 4));
};

char readCategoryLetter(const std::string &code){
    return code.back();
}