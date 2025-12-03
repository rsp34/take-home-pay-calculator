#include "./uk_tax_code.h"

// TaxCode
std::string validateTaxCode(std::string rawCode)
{
    if (rawCode.size() != 5){
        throw std::invalid_argument("UK tax codes are five characters in length");
    };
        
    for (int i = 0; i < 4; ++i){
        if (!std::isdigit(rawCode[i])){
            throw std::invalid_argument("UK tax codes begin with four digits.");
        };
    }

    char letter = rawCode.back();
    std::string validLetters = "LMPTY";
    if (validLetters.find(letter) == std::string::npos){
        throw std::invalid_argument("UK tax codes must end with one of " + validLetters);
    };

    return rawCode;

}

int readPersonalAllowance(const std::string &code)
{
    return std::stoi(code.substr(0, 4));
};

char readCategoryLetter(const std::string &code){
    return code.back();
}