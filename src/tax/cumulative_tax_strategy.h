#pragma once

#include "tax_computation_strategy.h"

class CumulativeTaxStrategy : public TaxComputationStrategy{
    public:
    virtual ~CumulativeTaxStrategy() = default;

    void applyTax(
        const std::string& taxName,
        const Tax& calculator,
        std::vector<std::shared_ptr<PayItem>>& payItems
    ) const override;
};
