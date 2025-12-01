#pragma once
#include "../pay/pay_item.h"
#include "../uk/uk_tax_model.h"

class UKPayItemFactory{
    static PayItem createSalary(float amount, std::shared_ptr<UKIncomeTaxModel> incomeTax, std::shared_ptr<UKNIModel> nationalInsurance);
    static PayItem createPension(float amount);
    static PayItem createBonus(float amount);
}

createSalary(float amount, std::shared_ptr<UKIncomeTaxModel> incomeTax, std::shared_ptr<UKNIModel> nationalInsurance){
    PayItem payItem = PayItem("Salary", amount, EffectType::TaxableAddition, false);
    payItem.taxModels = {incomeTax, nationalInsurance};
    return payItem;
}