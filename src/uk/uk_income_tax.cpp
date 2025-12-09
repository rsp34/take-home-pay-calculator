#include "uk_income_tax.h"
#include "uk_tax_code.h"
#include "../time/period.h"

int64_t UKIncomeTax::calculateTax(int64_t taxableAmount) const
{
    // Calculate all period_-adjusted thresholds once
    const int64_t periodPersonalAllowance = (taxCode_->personalAllowance * period_) / Period::Year;
    const int64_t periodBasicThreshold = (BASIC_RATE_THRESHOLD * period_) / Period::Year;
    const int64_t periodHigherThreshold = (HIGHER_RATE_THRESHOLD * period_) / Period::Year;
    const int64_t periodTaperingThreshold = (PERSONAL_ALLOWANCE_LOSS_THRESHOLD * period_) / Period::Year;
    const int64_t periodAdditionalThreshold = (ADDITIONAL_RATE_THRESHOLD * period_) / Period::Year;

    if (taxableAmount <= periodPersonalAllowance) {
        return NO_INCOME_TAX_DUE;
    }

    if (taxableAmount <= periodHigherThreshold) {
        int64_t taxableIncome = taxableAmount - periodPersonalAllowance;
        return applyRate<BASIC_RATE>(taxableIncome);
    }

    if (taxableAmount <= periodTaperingThreshold) {
        int64_t basicBandIncome = periodHigherThreshold - periodPersonalAllowance;
        int64_t higherBandIncome = taxableAmount - periodHigherThreshold;

        return applyRate<BASIC_RATE>(basicBandIncome) + applyRate<HIGHER_RATE>(higherBandIncome);
    }

    if (taxableAmount <= periodAdditionalThreshold) {
        int64_t excessIncome = taxableAmount - periodTaperingThreshold;
        int64_t allowanceReduction = excessIncome / 2;
        int64_t reducedAllowance = periodPersonalAllowance - allowanceReduction;

        int64_t basicBandIncome = periodHigherThreshold - reducedAllowance;
        int64_t higherBandIncome = taxableAmount - periodHigherThreshold;

        return applyRate<BASIC_RATE>(basicBandIncome) + applyRate<HIGHER_RATE>(higherBandIncome);
    }

    // Additional rate - personal allowance fully tapered away
    int64_t basicBandIncome = periodHigherThreshold - periodBasicThreshold;
    int64_t higherBandIncome = periodAdditionalThreshold - periodHigherThreshold;
    int64_t additionalBandIncome = taxableAmount - periodAdditionalThreshold;

    return applyRate<BASIC_RATE>(basicBandIncome) +
           applyRate<HIGHER_RATE>(higherBandIncome) +
           applyRate<ADDITIONAL_RATE>(additionalBandIncome);
}
