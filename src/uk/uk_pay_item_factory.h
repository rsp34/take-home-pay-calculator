#pragma once
#include "uk_tax_names.h"
#include "../pay/pay_item.h"

// TODO: Where do these belong? In a namespace?
class UKPayItemFactory
{
public:
    static PayItem createSalary(int64_t amount);
    static PayItem createEmployerPensionContribution(int64_t amount, int64_t percentage);
    static PayItem createEmployeePensionContribution(int64_t amount, int64_t percentage);
    static PayItem createBonus(int64_t amount);
};