#include <algorithm>
#include "pay_item.h"

bool PayItem::hasTax(std::string taxName){
    return (std::find(applicableTaxes_.begin(),applicableTaxes_.end(),taxName) != applicableTaxes_.end());
};

int64_t PayItem::getTaxableAmount() const{
    switch (effectType_)
    {
    case EffectType::TaxableAddition:
        return amount_;
    case EffectType::PreTaxDeduction:
        return amount_;
    case EffectType::NonTaxableAddition:
    case EffectType::PostTaxDeduction:
        return 0;
    }
}