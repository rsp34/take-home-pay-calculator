#pragma once
#include <string>

class TaxModel
{
public:
    virtual ~TaxModel() = default;

    virtual float calculateTax(float amount) const = 0;
    std::string name;
};