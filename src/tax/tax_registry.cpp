#include "tax_registry.h"
#include <stdexcept>

const TaxRegistration& TaxRegistry::getTaxRegistration(const std::string& taxName){
    if (registrations_.contains(taxName)){
        return registrations_.at(taxName);
    }
    throw std::invalid_argument(taxName + "not registered.");
}