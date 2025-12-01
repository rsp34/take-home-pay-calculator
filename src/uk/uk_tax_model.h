#pragma once
#include "../tax/tax_model.h"
#include <string>
#include <cctype>
#include <stdexcept>

int readPersonalAllowance(const std::string &code);
char readCategoryLetter(const std::string &code);

class UKTaxCode
{
public:
    UKTaxCode(const std::string code) : rawCode{code}, personalAllowance(readPersonalAllowance(code) * 10), categoryLetter(readCategoryLetter(code)) {};

    float personalAllowance;
    char categoryLetter;

    bool isValidTaxCode() const;

private:
    std::string rawCode;
};

class UKIncomeTaxModel : public TaxModel
{
    ~UKIncomeTaxModel() = default;
    std::string name = "UK Income Tax";

public:
    float calculateTax(float monthlyAmount) const override
    {

        float annualAmount = monthlyAmount * 12;

        if (annualAmount <= 12570)
        {
            return 0;
        }
        else if (annualAmount <= 50270)
        {
            return (annualAmount - 12570) * 0.2;
        }
        else if (annualAmount <= 100000)
        {
            return ((annualAmount - 50270) * 0.4 + (50270 - 12570) * 0.2);
        }
        else if (annualAmount <= 125140)
        {
            return ((annualAmount - 50270) * 0.4 + (50270 - (12570 - (annualAmount - 100000) / 2)) * 0.2);
        }
        else
        {
            return ((annualAmount - 125140) * 0.45 + (125140 - 50270) * 0.4 + (50270 - 12570) * 0.2);
        }
    };
};

class UKNIModel : public TaxModel
{
    ~UKNIModel() = default;
    std::string name = "UK National Insurance";

public:
    float calculateTax(float monthlyAmount) const override
    {

        if (monthlyAmount <= 1048)
        {
            return 0;
        }
        else if (monthlyAmount <= 4189)
        {
            return (monthlyAmount - 1048) * 0.08;
        }
        else
        {
            return ((monthlyAmount - 4189) * 0.02 + (4189 - 1048) * 0.08);
        }
    };
};
