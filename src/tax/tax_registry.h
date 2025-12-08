#pragma once
#include <map>
#include <string>

class TaxRegistration;

struct TaxRegistry{
    std::map<std::string, TaxRegistration> registrations_;

    const TaxRegistration& getTaxRegistration(const std::string& name);
};