#include "uk_employee_ni.h"
#include "../time/period.h"

int64_t UKEmployeeNI::calculateTax(int64_t taxableAmount) const
{
    const int64_t weeklyTaxableAmount = (taxableAmount * period_) / Period::Week;

    int64_t primaryRateIncome = 0;
    int64_t upperRateIncome = 0;
    if (weeklyTaxableAmount > PRIMARY_RATE_THRESHOLD)
    {
        if (weeklyTaxableAmount < HIGHER_RATE_THRESHOLD)
        {
            primaryRateIncome = weeklyTaxableAmount - PRIMARY_RATE_THRESHOLD;
        }
        else
        {
            primaryRateIncome = HIGHER_RATE_THRESHOLD - PRIMARY_RATE_THRESHOLD;
            upperRateIncome = weeklyTaxableAmount - HIGHER_RATE_THRESHOLD;
        }
    }

    const int64_t primaryRateNI = applyRate<PRIMARY_RATE>(primaryRateIncome);
    const int64_t upperRateNI = applyRate<UPPER_RATE>(upperRateIncome);
    const int64_t weeklyNI = primaryRateNI + upperRateNI;

    return (weeklyNI * period_) / Period::Week;
};