// Quotes mean relative to project root
// <> means from include path

#include <iostream>
#include "./src/uk/uk_tax_code.h"
#include "./src/uk/uk_tax_setup.h"
#include "./src/uk/uk_pay_item_factory.h"
#include "./src/tax/tax_registry.h"
#include "./src/uk/uk_tax_setup.h"
#include "./src/pay/payslip.h"
#ifdef _WIN32
    #include <windows.h>
#endif

// Why would I use a diretive over a function
// Replace with a function
#define PENCE_IN_POUND 100
#define PENCE(pounds,pence) (PENCE_IN_POUND*pounds)+pence

int64_t pence(int64_t pounds, int64_t pence){
    return (pounds*100)+pence;
}

int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    std::shared_ptr<UKTaxCode> taxCode = std::make_shared<UKTaxCode>("1257L");
    int64_t period = 31;
    std::shared_ptr<TaxRegistry> ukTaxRegistry = createUKTaxRegistry(taxCode, period);
    Payslip payslip = Payslip(ukTaxRegistry);
    int64_t salary = PENCE(3000,0);
    int64_t bonus = PENCE(100,0);
    int64_t pension_contribution_percentage = 5;
    payslip.addItem(std::make_shared<PayItem>(UKPayItemFactory::createSalary(salary)));
    payslip.addItem(std::make_shared<PayItem>(UKPayItemFactory::createEmployeePensionContribution(salary,pension_contribution_percentage)));
    payslip.addItem(std::make_shared<PayItem>(UKPayItemFactory::createEmployerPensionContribution(salary,pension_contribution_percentage)));
    payslip.addItem(std::make_shared<PayItem>(UKPayItemFactory::createBonus(bonus)));
    payslip.applyTaxes();
    payslip.printPayslip();
}