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

    // Is this bad practice??

    // I've got a mix of definitions and implementations
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
    std::vector<std::string_view> applicableTaxes_;
    std::map<std::string_view, int64_t> taxAmounts_;

    bool hasTax(std::string_view taxName);

    int64_t getTaxableAmount() const;
};

// How do I think about the header file?
// Ask yourself does somebody using my class need to know this piece of implementation
// If you have a strange implementation of  specific function, you may want to include comments in the header for others to read.
