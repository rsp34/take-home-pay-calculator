#pragma once
#include "../tax/tax_model.h"
#include "../pay/frequency.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <memory>

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

class UKIncomeTaxModel : public CumulativeTaxModel
{
    ~UKIncomeTaxModel() = default;
    std::string name = "UK Income Tax";
    std::shared_ptr<UKTaxCode> taxCode;

public:
    float calculateTax(float periodAmount, Frequency frequency) override
    {
        accumulatePeriod(periodAmount, frequency);

        float totalTaxDue = 0;

        if (cumulativeTaxableIncome <= taxCode->personalAllowance * yearFraction())
        {
            totalTaxDue = 0;
        }
        else if (cumulativeTaxableIncome <= 50270 * yearFraction())
        {
            totalTaxDue = (cumulativeTaxableIncome - taxCode->personalAllowance * yearFraction()) * 0.2;
        }
        else if (cumulativeTaxableIncome <= 100000 * yearFraction())
        {
            totalTaxDue = ((cumulativeTaxableIncome - 50270 * yearFraction()) * 0.4 + (50270 - 12570) * yearFraction() * 0.2);
        }
        else if (cumulativeTaxableIncome <= 125140 * yearFraction())
        {
            totalTaxDue = ((cumulativeTaxableIncome - 50270 * yearFraction()) * 0.4 + (50270 * yearFraction() - (12570 * yearFraction() - (cumulativeTaxableIncome - 100000 * yearFraction()) / 2)) * 0.2);
        }
        else
        {
            totalTaxDue = ((cumulativeTaxableIncome - 125140 * yearFraction()) * 0.45 + (125140 - 50270) * yearFraction() * 0.4 + (50270 - 12570) * yearFraction() * 0.2);
        }

        return finalizeTax(totalTaxDue);
    };
};

class UKNIModel : public CumulativeTaxModel
{
    ~UKNIModel() = default;
    std::string name = "UK National Insurance";

public:
    float calculateTax(float periodAmount, Frequency frequency) override
    {
        accumulatePeriod(periodAmount, frequency);

        float totalTaxDue = 0;
        float yf = yearFraction();

        if (cumulativeTaxableIncome <= 1048 * 12 * yf)
        {
            totalTaxDue = 0;
        }
        else if (cumulativeTaxableIncome <= 4189 * 12 * yf)
        {
            totalTaxDue = (cumulativeTaxableIncome - 1048 * 12 * yf) * 0.08;
        }
        else
        {
            totalTaxDue = ((cumulativeTaxableIncome - 4189 * 12 * yf) * 0.02 + (4189 - 1048) * 12 * yf * 0.08);
        }

        return finalizeTax(totalTaxDue);
    };
};