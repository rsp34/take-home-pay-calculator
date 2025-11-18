#include "pay_item.h"

// Constructor
PayItem::PayItem(const std::string& lbl, int val, EffectType t, Frequency f, int start)
    : label(lbl), annualValue(val), type(t), freq(f), startPeriod(start) {}

// getValueForPeriod: period-aware, handles start offsets
int PayItem::getValueForPeriod(int periodNumber, int periodsPerYear) const {
    // Before start period → value is 0
    if (periodNumber < startPeriod) return 0;

    // Remaining periods for this item
    int remainingPeriods = periodsPerYear - startPeriod + 1;

    int valuePerPeriod = 0;
    switch (freq) {
        case Frequency::Annual:
            // Spread remaining annual value evenly over remaining periods
            valuePerPeriod = annualValue / remainingPeriods;
            break;
        case Frequency::Monthly:
            valuePerPeriod = annualValue / 12;
            break;
        case Frequency::Weekly:
            valuePerPeriod = annualValue / 52;
            break;
    }

    return valuePerPeriod;
}
