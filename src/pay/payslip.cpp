#include "payslip.h"
#include "..\tax\tax_registry.h"
#include "..\tax\tax_registration.h"
#include "..\tax\tax_computation_strategy.h"
#include "..\tax\tax.h"

void Payslip::addItem(std::shared_ptr<PayItem> item)
{
    payItems_.push_back(std::move(item));
};

void Payslip::computeTaxes(){
    for (const auto& [taxName, registration] : registry_->registrations_){
        registration.strategy_->computeTax(taxName,*registration.calculator_,payItems_);
    }
}