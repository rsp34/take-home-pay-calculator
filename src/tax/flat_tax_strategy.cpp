#include "flat_tax_strategy.h"
#include "../pay/pay_item.h"
#include "../tax/tax.h"

void FlatTaxStrategy::computeTax(
    const std::string &taxName,
    const Tax &calculator,
    std::vector<std::shared_ptr<PayItem>> &payItems) const
{
    for (std::shared_ptr<PayItem>& item : payItems)
    {
        if (item->hasTax(taxName))
        {
            item->taxAmounts_[taxName] = calculator.calculateTax(item->amount_);
        }
    }
};