#pragma once
#include "uk_tax_names.h"

class PayItem;

class UKPayItemFactory
{
    static PayItem createSalary(int64_t amount);
    static PayItem createPension(int64_t amount);
    static PayItem createBonus(int64_t amount);
};