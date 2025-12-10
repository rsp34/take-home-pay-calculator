#include "payslip.h"
#include "pay_item.h"
#include "..\tax\tax_registry.h"
#include "..\tax\tax_registration.h"
#include "..\tax\tax_computation_strategy.h"
#include "..\tax\tax.h"
#include <iostream>
#include <iomanip>

void Payslip::addItem(std::shared_ptr<PayItem> item)
{
    payItems_.push_back(std::move(item));
};

void Payslip::applyTaxes(){
    for (const auto& [taxName, registration] : registry_->registrations_){
        registration.strategy_->applyTax(taxName,*registration.calculator_,payItems_);
    }
}

void Payslip::printPayslip() const
{
    std::cout << "\n========== PAYSLIP ==========\n\n";
    
    int64_t grossTotal = 0;
    int64_t taxTotal = 0;
    
    for (const std::shared_ptr<PayItem>& item : payItems_)
    {
        std::cout << std::left << std::setw(30) << item->name_ 
                  << std::right << "£" << std::setw(8) 
                  << std::fixed << std::setprecision(2)
                  << (item->amount_ / 100.0) << "\n";
        
        grossTotal += item->amount_;
        
        for (const std::pair<const std::string, int64_t>& taxEntry : item->taxAmounts_)
        {
            std::cout << "  " << std::left << std::setw(28) << taxEntry.first 
                      << std::right << "-£" << std::setw(7)
                      << std::fixed << std::setprecision(2)
                      << (taxEntry.second / 100.0) << "\n";
            
            taxTotal += taxEntry.second;
        }
    }
    
    std::cout << "\n-----------------------------\n";
    std::cout << std::left << std::setw(30) << "Gross Total:" 
              << std::right << "£" << std::setw(8)
              << std::fixed << std::setprecision(2)
              << (grossTotal / 100.0) << "\n";
    
    std::cout << std::left << std::setw(30) << "Total Tax:" 
              << std::right << "-£" << std::setw(7)
              << std::fixed << std::setprecision(2)
              << (taxTotal / 100.0) << "\n";
    
    std::cout << std::left << std::setw(30) << "Net Pay:" 
              << std::right << "£" << std::setw(8)
              << std::fixed << std::setprecision(2)
              << ((grossTotal - taxTotal) / 100.0) << "\n";
    
    std::cout << "=============================\n\n";
}
