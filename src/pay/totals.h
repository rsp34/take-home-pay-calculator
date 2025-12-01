#pragma once

struct Totals{
    float taxableAdditions = 0;
    float nonTaxableAdditions = 0;
    float preTaxDeductions = 0;
    float postTaxDeductions = 0;
    
    float taxableIncome() const {
        return taxableAdditions - preTaxDeductions;
    }
    
    float grossIncome() const {
        return taxableAdditions + nonTaxableAdditions;
    }
};