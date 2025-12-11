#pragma once
#include <string>
#include <cstdint>
#include <ratio>

class Tax{
    public:
        virtual ~Tax() = default;
        virtual int64_t calculateTax(int64_t amount) const = 0;

        // Helper to apply a tax rate ratio to an amount
        template<typename Rate>
        int64_t applyRate(int64_t amount) const {
            return (amount * Rate::num) / Rate::den;
        }
};