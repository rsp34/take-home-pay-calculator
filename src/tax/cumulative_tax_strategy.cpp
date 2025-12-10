#include "cumulative_tax_strategy.h"
#include "../pay/pay_item.h"
#include "../tax/tax.h"

void CumulativeTaxStrategy::applyTax(
    const std::string &taxName,
    const Tax &calculator,
    std::vector<std::shared_ptr<PayItem>> &payItems) const
{
    int64_t cumulativeAmount = 0;
    int64_t cumulativeTaxableAmount = 0;
    std::vector<std::pair<std::shared_ptr<PayItem>, int64_t>> eligibleItems;

    for (std::shared_ptr<PayItem> &item : payItems)
    {
        if (item->hasTax(taxName))
        {

            cumulativeAmount += item->amount_;

            int64_t taxableAmount = item->getTaxableAmount();
            cumulativeTaxableAmount += taxableAmount;
            eligibleItems.push_back({item, taxableAmount});
        }
    }

    int64_t totalTax = calculator.calculateTax(cumulativeTaxableAmount);

    for (const auto &[item, taxableAmount] : eligibleItems)
    {

        int64_t itemTax = 0;

        if (cumulativeAmount > 0){
            itemTax = (totalTax * item->amount_) / cumulativeAmount;
            if (taxableAmount < 0){
                // Our taxable amount was negative so behaves as a relief
                itemTax = -itemTax;
            }
        }

        item->taxAmounts_[taxName] = itemTax;
    }
};