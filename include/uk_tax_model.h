#pragma once
#include <string>

class PersonalAllowance
{
public:
    PersonalAllowance(int v = 1257);
    void set(int v);
    int get() const;

private:
    int value;
};

class TaxCode
{
public:
    TaxCode(const std::string &code);

    int getPersonalAllowance() const;
    bool isValidTaxCode() const;
    const std::string& getRawCode() const;

private:
    int parseDigits(const std::string &code);
    
    PersonalAllowance pa;
    std::string rawCode;
};