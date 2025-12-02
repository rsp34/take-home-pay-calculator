#pragma once
#include <string>
#include <vector>
#include <memory>
#include "./tax/tax_model.h"

enum class EffectType
{
    TaxableAddition,
    NonTaxableAddition,
    PreTaxDeduction,
    PostTaxDeduction
};

struct PayItem
{
    PayItem(const std::string name, float amount, EffectType effectType, bool oneOff = false)
        : name(name), amount(amount), effectType(effectType), oneOff(oneOff) {};

    std::string name;
    float amount;
    EffectType effectType;
    bool oneOff;
    std::vector<std::shared_ptr<TaxModel>> taxModels;
};