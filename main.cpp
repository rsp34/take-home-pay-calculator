#include<iostream>
#include "./src/uk/uk_tax_code.h"
#include "./src/uk/uk_tax_setup.h"
#include "./src/uk/uk_pay_item_factory.h"
#include "./src/tax/tax_registry.h"
#include "./src/uk/uk_tax_setup.h"
#include "./src/pay/payslip.h"

int main(){
    std::shared_ptr<UKTaxCode> taxCode = std::make_shared<UKTaxCode>("1257L");
    int64_t period = 31;
    std::shared_ptr<TaxRegistry> ukTaxRegistry = createUKTaxRegistry(taxCode, period);
    Payslip payslip = Payslip(ukTaxRegistry);
    int64_t salary = 3000;
    int64_t bonus = 100;
    int64_t pension_contribution_percentage = 5;
    payslip.addItem(std::make_shared<PayItem>(UKPayItemFactory::createSalary(salary)));
    payslip.addItem(std::make_shared<PayItem>(UKPayItemFactory::createEmployeePensionContribution(salary,pension_contribution_percentage)));
    payslip.addItem(std::make_shared<PayItem>(UKPayItemFactory::createEmployerPensionContribution(salary,pension_contribution_percentage)));
    payslip.addItem(std::make_shared<PayItem>(UKPayItemFactory::createBonus(bonus)));
    payslip.printPayslip();
}