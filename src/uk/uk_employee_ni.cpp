#include "uk_employee_ni.h"
#include "../time/period.h"

int64_t UKEmployeeNI::calculateTax(int64_t taxableAmount)
{   
    const int64_t weeklyTaxableAmount = (taxableAmount * period_) / Period::Week;
    const int64_t higherRateIncome = (weeklyTaxableAmount - HIGHER_RATE_THRESHOLD)
    const int64_t higherRateIncome = (HIGHER_RATE_THRESHOL
    
    if (taxableAmount<)
};