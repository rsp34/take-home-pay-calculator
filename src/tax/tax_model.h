#pragma once
#include "../pay/frequency.h"
#include <string>

class TaxModel{
    public:
        virtual float calculateTax() = 0;
        virtual ~TaxModel() = default;
};

// For simple, non-cumulative calculations (flat fees, simple percentages)
class SimpleTaxModel:TaxModel
{
public:
    virtual ~SimpleTaxModel() = default;
    virtual float calculateTax(float amount) const = 0;
};

// For cumulative, year-to-date calculations
class CumulativeTaxModel:TaxModel
{
public:
    virtual ~CumulativeTaxModel() = default;
    virtual float calculateTax(float periodAmount, Frequency frequency) = 0;

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