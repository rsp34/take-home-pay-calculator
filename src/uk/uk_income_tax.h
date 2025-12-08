#pragma once
#include <memory>
#include <cstdint>
#include <ratio>
#include "../time/period.h"
#include "../tax/tax.h"
#include "uk_tax_code.h"

constexpr int NO_INCOME_TAX_DUE = 0;
using BASIC_RATE = std::ratio<2,10>;
using HIGHER_RATE = std::ratio<4,10>;
using ADDITIONAL_RATE = std::ratio<9,20>;

constexpr int64_t BASIC_RATE_THRESHOLD = 12570;
constexpr int64_t HIGHER_RATE_THRESHOLD = 50270;
constexpr int64_t PERSONAL_ALLOWANCE_LOSS_THRESHOLD = 100000;
constexpr int64_t ADDITIONAL_RATE_THRESHOLD = 125140;

class UKIncomeTax : public Tax
{
    UKIncomeTax(std::shared_ptr<UKTaxCode> taxCode, int period) : taxCode{taxCode}, period{period} {}
    ~UKIncomeTax() = default;
    const std::string name = "UK Income Tax";
    const std::shared_ptr<UKTaxCode> taxCode;
    const int period;

    // Helper to apply a tax rate ratio to an amount
    template<typename Rate>
    int64_t applyRate(int64_t amount) const {
        return (amount * Rate::num) / Rate::den;
    }

public:
    int64_t calculateTax(int64_t cumulativeIncome) const override;
    UKIncomeTax operator+(const UKIncomeTax);
    UKIncomeTax operator/(const UKIncomeTax);
};