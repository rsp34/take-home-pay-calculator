#include <vector>
#include <memory>
#include <iostream>

class PayItem;
class TaxRegistry;

class Payslip
{
public:
    Payslip(std::shared_ptr<TaxRegistry> registry) : registry_(registry) {};

    void addItem(std::shared_ptr<PayItem> item);
    void applyTaxes();
    void printPayslip() const;

private:
    std::vector<std::shared_ptr<PayItem>> payItems_;
    std::shared_ptr<TaxRegistry> registry_;
};