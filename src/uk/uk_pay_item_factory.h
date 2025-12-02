#pragma once
#include "../pay/pay_item.h"
#include "../uk/uk_tax_model.h"

class UKPayItemFactory
{
    static PayItem createSalary(float amount, std::shared_ptr<UKIncomeTaxModel> incomeTax, std::shared_ptr<UKNIModel> nationalInsurance);
    static PayItem createPension(float amount);
    static PayItem createBonus(float amount);
};

PayItem createSalary(float amount, std::shared_ptr<UKIncomeTaxModel> incomeTax, std::shared_ptr<UKNIModel> nationalInsurance)
{
    PayItem payItem = PayItem("Salary", amount, EffectType::TaxableAddition, false);
    payItem.taxModels = {incomeTax, nationalInsurance};
    return payItem;
}

PayItem createEmployerPensionContribution(float amount, float percentage)
{
    return PayItem("Employer Pension Contribution", amount * percentage, EffectType::NonTaxableAddition, false);
}

PayItem createEmployeePensionContribution(float amount, float percentage)
{
    return PayItem("Employee Pension Contribution", amount * percentage, EffectType::PreTaxDeduction, false);
}

PayItem createBonus(float amount, std::shared_ptr<UKIncomeTaxModel> incomeTax, std::shared_ptr<UKNIModel> nationalInsurance)
{
    PayItem payItem = PayItem("Bonus", amount, EffectType::TaxableAddition, true);
    payItem.taxModels = {incomeTax, nationalInsurance};
    return payItem;
}