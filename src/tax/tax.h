#pragma once
#include <string>

class Tax{
    public:
        virtual ~Tax() = default;
        virtual float calculateTax(float amount) const = 0;
        std::string name = "Tax";
};