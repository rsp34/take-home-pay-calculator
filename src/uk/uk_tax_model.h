#pragma once
#include "../tax/tax_model.h"
#include <string>

int readPersonalAllowance(const std::string &code);
std::string readCategoryLetter(const std::string &code);

class TaxCode
{
public:

    TaxCode(const std::string code) : rawCode{code}, personalAllowance(readPersonalAllowance(code)*10), categoryLetter(readCategoryLetter(code)) {};

    float personalAllowance;
    std::string categoryLetter;

    bool isValidTaxCode() const;

private:

    std::string rawCode;

};

class UKNIModel : public TaxModel{
    ~UKNIModel() = default;
    std::string name = "UK National Insurance";
};

class UKNIModel : public TaxModel{
    ~UKNIModel() = default;
    std::string name = "UK National Insurance";
};
