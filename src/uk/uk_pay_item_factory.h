#pragma once
#include "uk_tax_names.h"

class PayItem;

class UKPayItemFactory
{
    static PayItem createSalary(int64_t amount);
    static PayItem createEmployerPensionContribution(int64_t amount, int64_t percentage);
    static PayItem createEmployeePensionContribution(int64_t amount, int64_t percentage);
    static PayItem createBonus(int64_t amount);
};