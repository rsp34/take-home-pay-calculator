#pragma once
#include <cstdint>
#include <string>
#include <ostream>
#include <iomanip>

inline constexpr int64_t PENNIES_IN_POUND = 100;

class Pennies{
    
    public:
        int64_t value_;
        std::string symbol_ = "£";
        constexpr explicit Pennies(int64_t pennies) : value_{pennies} {};
        constexpr Pennies operator+(const Pennies &p) const {return Pennies(value_ + p.value_);};
        constexpr Pennies operator-(const Pennies &p) const {return Pennies(value_ - p.value_);};
        constexpr Pennies operator*(const int64_t scalar) const {return Pennies(value_/scalar);};
        constexpr Pennies operator/(const int64_t scalar) const {return Pennies(value_/scalar);};
};

constexpr Pennies pounds(int64_t pounds)
{
    return Pennies(PENNIES_IN_POUND * pounds);
}

std::ostream& operator<<(std::ostream& os, const Pennies& p){
    os << p.symbol_ << std::setprecision(2) << p.value_/PENNIES_IN_POUND;
}