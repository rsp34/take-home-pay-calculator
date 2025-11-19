#pragma once
#include<string>

enum class EffectType
{
    TaxableAddition,
    NonTaxableAddition,
    PreTaxDeduction,
    PostTaxDeduction
};

class PayItem{
    
    private:
        std::string name;
        float amount;
        EffectType effectType;
        bool oneOff;      

    public:
        PayItem(const std::string name, float amount, EffectType effectType, bool oneOff = false) : name(name), amount(amount), effectType(effectType), oneOff(oneOff) {} ;

        const std::string getName() const {return name; };
        float getAmount() const {return amount; };
        EffectType getEffect() const { return effectType; };
};