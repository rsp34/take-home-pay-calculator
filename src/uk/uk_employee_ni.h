#pragma once
#include <memory>
#include <ratio>
#include "../tax/tax.h"
#include "uk_tax_code.h"

using PRIMARY_RATE = std::ratio<8, 100>;
using UPPER_RATE = std::ratio<2, 100>;

// Weekly thresholds
constexpr int64_t LOWER_EARNINGS_LIMIT = 125;
constexpr int64_t PRIMARY_RATE_THRESHOLD = 242;
constexpr int64_t UPPER_RATE_THRESHOLD = 967;

class UKEmployeeNI : public Tax
{
public:
    UKEmployeeNI(std::shared_ptr<UKTaxCode> taxCode, int period) : taxCode_{taxCode}, period_{period} {};
    ~UKEmployeeNI() = default;
    const int period_;
    const std::shared_ptr<UKTaxCode> taxCode_;

public:
    int64_t calculateTax(int64_t taxableIncome) const override;
    UKEmployeeNI operator+(const UKEmployeeNI);
    UKEmployeeNI operator-(const UKEmployeeNI);
    UKEmployeeNI operator/(const UKEmployeeNI);
    UKEmployeeNI operator*(const UKEmployeeNI);
};