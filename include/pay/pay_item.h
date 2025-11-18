#pragma once
#include<string>

// Add a start period


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
        EffectType effect;
        Frequency frequency;
        int startingPeriod;


    public:
        PayItem(const std::string &n, float ya, EffectType e, Frequency f, int sp);

        const std::string& getName() const {return name; };
        float getYearlyAmount() const {return yearlyAmount; };
        EffectType getEffect() const { return effect; };
        Frequency getFrequency() const {return frequency; };
        int getStartingPeriod() const {return }

        float getValueForPeriod(int periodNumber, int periodsPerYear) const;
        
};