#include<vector>
#include<memory>
#include<iostream>
#include "pay_item.h"
#inclde

struct Totals
{
    float taxableAdditions; // Is this more of a ordering rule? Kind of a type and an order.
    float nonTaxableAdditions;
    float preTaxDeductions;
    float postTaxDeductions;
};

enum class Frequency
{
    Annual,
    OneOff,
    Monthly,
    Weekly,
    WorkingDay,
    Daily
};


class Payslip
{

private:
    std::vector<std::unique_ptr<PayItem>> payItems;
    std::vector<std::vector<std::shared_ptr<TaxModel>>> taxModels;
    std::vector<std::vector<float>> taxes;
    Frequency frequency;

public:
    void addItem(std::unique_ptr<PayItem> item, std::vector<std::shared_ptr<TaxModel>>  itemTaxModels)
    {    
        payItems.push_back(std::move(item));
        taxModels.push_back(std::move(itemTaxModels));
    };

    void computeTaxes()

    void print_payslip(){
        // Convert to padding as a table would be nice here...
        for (const auto& item : items){
            std::cout << item->getName() << ", " << item->getValueForPeriod(0) << "\n";
        }
    }

};