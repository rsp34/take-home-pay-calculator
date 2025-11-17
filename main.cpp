#include<iostream>
#include "uk_tax_model.h"

using namespace std; 

int main(){
    std::string code;
    std::cout << "Enter tax code: ";
    std::cin >> code;

    TaxCode tc(code);
    
    if (!tc.isValidTaxCode()) {
        std::cerr << "Error: Invalid tax code!" << std::endl;
    } else {
        std::cout << "Personal allowance: " << tc.getPersonalAllowance() << std::endl;
    }
}