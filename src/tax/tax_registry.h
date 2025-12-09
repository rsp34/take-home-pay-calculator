#pragma once
#include <map>
#include <string>

class TaxRegistration;

class TaxRegistry
{
public:
    std::map<std::string_view, TaxRegistration> registrations_;
    const TaxRegistration& getTaxRegistration(std::string_view name) const;
};