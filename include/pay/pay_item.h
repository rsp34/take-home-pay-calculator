#pragma once
#include<string>

enum class EffectType
{
    TaxableAddition,
    NonTaxableAddition,
    PreTaxDeduction,
    PostTaxDeduction
};

enum class Frequency
{
    Annual,
    Monthly,
    Weekly,
    Daily
};

class PayItem{
    
    private:
        std::string name;
        float yearlyAmount;
        EffectType effectType;
        Frequency frequency;
        int startingPeriod;


    public:
        PayItem(const std::string &n, float ya, EffectType e, Frequency f, int sp);

        const std::string& getName() const {return name; };
        float getYearlyAmount() const {return yearlyAmount; };
        EffectType getEffect() const { return effectType; };
        Frequency getFrequency() const {return frequency; };
        int getStartingPeriod() const {return startingPeriod; };

        float getValueForPeriod(int periodNumber, int periodsPerYear) const;
        
};