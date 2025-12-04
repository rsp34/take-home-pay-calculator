#pragma once
#include <string>
#include <cstdint>

class Tax{
    public:
        virtual ~Tax() = default;
        virtual int64_t calculateTax(int64_t amount) const = 0;
        std::string name = "Tax";
};