#pragma once
#include <memory>

class Tax;
class TaxComputationStrategy;

struct TaxRegistration
{
    std::shared_ptr<Tax> calculator_;
    std::shared_ptr<TaxComputationStrategy> strategy_;
};