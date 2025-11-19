#include "pay_item.h"

PayItem::PayItem(const std::string& name, float yearlyAmount, EffectType effectType, Frequency frequency, int startingPeriod)
    : name(name), yearlyAmount(yearlyAmount), effectType(effectType), frequency(frequency), startingPeriod(startingPeriod) {}

float PayItem::getValueForPeriod(int periodNumber, int periodsPerYear) const {

    int startingPeriod = getStartingPeriod();

    if (periodNumber < startingPeriod) return 0;

    int remainingPeriods = periodsPerYear - startingPeriod + 1;

    int valuePerPeriod = 0;
    switch (getFrequency()) {
        case Frequency::Annual:
            valuePerPeriod = getYearlyAmount() / remainingPeriods;
            break;
        case Frequency::Monthly:
            valuePerPeriod = getYearlyAmount() / 12;
            break;
        case Frequency::Weekly:
            valuePerPeriod = getYearlyAmount() / 52;
            break;
    }

    return valuePerPeriod;
}
