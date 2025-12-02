#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "pay_item.h"
#include "frequency.h"

class Payslip
{

private:
    std::vector<std::unique_ptr<PayItem>> payItems;
    Frequency frequency;

public:
    Payslip(Frequency freq) : frequency(freq) {};

    void addItem(std::unique_ptr<PayItem> item)
    {
        payItems.push_back(std::move(item));
    };

    void print_payslip()
    {
        std::cout << "Description, Amount\n";
        for (const auto &payItem : payItems)
        {
            std::cout << payItem->name << ", " << payItem->amount << "\n";
            for (const auto &taxModel : payItem->taxModels)
            {
                std::cout << taxModel->name << ", " << taxModel->calculateTax(payItem->amount, frequency) << "\n";
            }
        }
    }
};