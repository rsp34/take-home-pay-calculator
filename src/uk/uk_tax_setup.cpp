#include <memory>
#include "uk_tax_setup.h"
#include "../tax/tax_registry.h"
#include "../tax/tax_registration.h"
#include "../tax/cumulative_tax_strategy.h"
#include "uk_tax_names.h"
#include "uk_tax_code.h"
#include "uk_income_tax.h"
#include "uk_employee_ni.h"

std::shared_ptr<TaxRegistry> createUKTaxRegistry(std::shared_ptr<UKTaxCode> taxCode, int period){
    std::shared_ptr<TaxRegistry> registry = std::make_shared<TaxRegistry>();
    registry->registrations_[UKTaxNames::INCOME_TAX] = TaxRegistration {std::make_shared<UKIncomeTax>(taxCode,period), std::make_shared<CumulativeTaxStrategy>()};
    registry->registrations_[UKTaxNames::EMPLOYEE_NI] = TaxRegistration {std::make_shared<UKEmployeeNI>(taxCode,period), std::make_shared<CumulativeTaxStrategy>()};
    return registry;
}