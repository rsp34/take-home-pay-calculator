#pragma once
#include <string>

enum class EffectType
{
    TaxableAddition,
    NonTaxableAddition,
    PreTaxDeduction,
    PostTaxDeduction
};

struct PayItem
{
    PayItem(const std::string name, float amount, EffectType effectType, bool oneOff = false) : name(name), amount(amount), effectType(effectType), oneOff(oneOff) {};
    std::string name;
    float amount;
    EffectType effectType;
    bool oneOff;
};