#pragma once
#include "../pay/frequency.h"
#include <string>

class TaxModel{
    public:
        virtual ~TaxModel() = default;
        virtual float calculateTax(float periodAmount, Frequency frequency) = 0;
        std::string name = "Tax Model";
};

// For cumulative, year-to-date calculations
class CumulativeTaxModel:public TaxModel
{
public:
    virtual ~CumulativeTaxModel() = default;
    std::string name = "Cumulative Tax Model";

protected:
    float cumulativeTaxableIncome = 0;
    float cumulativeTaxPaid = 0;
    int   daysElapsed = 0;

    void accumulatePeriod(float periodAmount, Frequency frequency) {
        cumulativeTaxableIncome += periodAmount;
        daysElapsed += static_cast<int>(frequency);
    }

    float finalizeTax(float totalTaxDue) {
        float taxThisPeriod = totalTaxDue - cumulativeTaxPaid;
        cumulativeTaxPaid = totalTaxDue;
        return taxThisPeriod;
    }

    float yearFraction(){ return daysElapsed/365.0; }
};