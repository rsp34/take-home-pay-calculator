#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <map>
#include <cstdint>
#include <stdexcept>

enum class EffectType
{
    TaxableAddition,
    NonTaxableAddition,
    PreTaxDeduction,
    PostTaxDeduction
};

struct PayItem
{
    PayItem(const std::string name, int64_t amount, EffectType effectType, bool oneOff = false)
        : name_(name), amount_(amount), effectType_(effectType), oneOff_(oneOff)
    {
        if (amount <= 0)
        {
            throw std::invalid_argument("PayItem amount must be positive");
        }
    };

    std::string name_;
    int64_t amount_;
    EffectType effectType_;
    bool oneOff_;
    std::vector<std::string> taxes_;
    std::map<std::string, int64_t> taxAmounts_;

    bool hasTax(std::string taxName);

    int64_t getTaxableAmount() const;
};