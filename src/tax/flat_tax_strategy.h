#pragma once

#include "tax_computation_strategy.h"

class FlatTaxStrategy : public TaxComputationStrategy{
    public:
    virtual ~FlatTaxStrategy() = default;

    void applyTax(
        const std::string_view& taxName,
        const Tax& calculator,
        std::vector<std::shared_ptr<PayItem>>& payItems
    ) const override;
};
