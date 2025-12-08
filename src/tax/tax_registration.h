#pragma once
#include <memory>

class Tax;
class TaxCalculationStrategy;

struct TaxRegistration
{
    std::shared_ptr<Tax> calculator_;
    std::shared_ptr<TaxCalculationStrategy> strategy_;
};