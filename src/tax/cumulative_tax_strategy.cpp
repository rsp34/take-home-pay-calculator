#include "cumulative_tax_strategy.h"
#include "../pay/pay_item.h"
#include "../tax/tax.h"

void CumulativeTaxStrategy::computeTax(
    const std::string &taxName,
    const Tax &calculator,
    std::vector<std::shared_ptr<PayItem>> &payItems) const
{
    int64_t cumulativeAmount = 0;
    std::vector<std::pair<std::shared_ptr<PayItem>, int64_t>> eligibleItems;

    for (std::shared_ptr<PayItem>& item : payItems)
    {
        if (item->hasTax(taxName)){
            int64_t taxableAmount = item->amount_;
            cumulativeAmount += taxableAmount;
            eligibleItems.push_back({item, taxableAmount});
        }
    }

    int64_t totalTax = calculator.calculateTax(cumulativeAmount);

    for (const auto &[item, amount] : eligibleItems)
    {
        int64_t itemTax = (cumulativeAmount > 0)
                              ? (amount * totalTax) / cumulativeAmount
                              : 0;
        item->taxAmounts_[taxName] = itemTax;
    }
};