#pragma once

#include <vector>
#include <memory>
#include <string>

class PayItem;
class Tax;

class TaxComputationStrategy
{
public:
    virtual ~TaxComputationStrategy() = default;

    virtual void computeTax(
        const std::string &taxName,
        const Tax &calculator,
        std::vector<std::shared_ptr<PayItem>> &payItems) const = 0;
};