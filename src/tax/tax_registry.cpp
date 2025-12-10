#include "tax_registry.h"
#include <stdexcept>
#include <string>

const TaxRegistration &TaxRegistry::getTaxRegistration(const std::string_view taxName) const
{
    if (registrations_.contains(taxName))
    {
        return registrations_.at(taxName);
    }
    throw std::invalid_argument(std::string(taxName) + "not registered.");
}