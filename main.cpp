#include<iostream>
#include "./src/uk/uk_tax_code.h"

using namespace std; 

int main(){
    std::string code;
    std::cout << "Enter tax code: ";
    std::cin >> code;

    UKTaxCode tc(code);
}