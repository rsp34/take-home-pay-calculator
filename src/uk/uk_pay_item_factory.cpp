#include "uk_pay_item_factory.h"
// #include "../pay/pay_item.h"

// Be precise about includes?

PayItem UKPayItemFactory::createSalary(int64_t amount)
{
    PayItem payItem = PayItem("Salary", amount, EffectType::TaxableAddition, false);
    payItem.applicableTaxes_ = {UKTaxNames::EMPLOYEE_NI, UKTaxNames::INCOME_TAX};
    return payItem;
}

PayItem UKPayItemFactory::createEmployerPensionContribution(int64_t amount, int64_t percentage)
{
    return PayItem("Employer Pension Contribution", amount * percentage/100, EffectType::NonTaxableAddition, false);
}

PayItem UKPayItemFactory::createEmployeePensionContribution(int64_t amount, int64_t percentage)
{
    PayItem payItem = PayItem("Employee Pension Contribution", amount * percentage/100, EffectType::PreTaxDeduction, false);
    payItem.applicableTaxes_ = {UKTaxNames::EMPLOYEE_NI, UKTaxNames::INCOME_TAX};
    return payItem;
}

PayItem UKPayItemFactory::createBonus(int64_t amount)
{
    PayItem payItem = PayItem("Bonus", amount, EffectType::TaxableAddition, true);
    payItem.applicableTaxes_ = {UKTaxNames::EMPLOYEE_NI, UKTaxNames::INCOME_TAX};
    return payItem;
}