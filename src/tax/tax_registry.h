#pragma once
#include <map>
#include <string>
#include "tax_registration.h"

class TaxRegistry
{
public:
    std::map<std::string_view, TaxRegistration> registrations_;
    const TaxRegistration& getTaxRegistration(std::string_view name) const;
};