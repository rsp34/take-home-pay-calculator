# Take Home Pay Calculator

## Requirements
- A user may predict their payslip, inlcuding for multiple jobs.
- Specific month selection.
- Daily, weekly and monthly options are available.

## Technologies
A focus of this project is understanding the features of C++.

## Design
The project is split into 2 components.

1. A `pay` section which includes a `Payslip` and `PayItem` classes to abstract how pay items are aggregated.
2. A set of classes to model various pay items.

Design Approach: Tax Calculator Architecture
Core Principles
1. Separation of Concerns
PayItem: Domain model - represents a line item (salary, bonus, pension, etc.)
TaxModel: Tax calculation logic - knows how to compute one specific tax
Factory: Construction logic - knows which taxes apply to which items
Payslip: Orchestration - manages items, triggers calculations, displays results
2. Polymorphism for Extensibility
TaxModel is an abstract interface
Each country implements its own concrete tax models (e.g., UKIncomeTaxModel, USFederalTaxModel)
PayItem doesn't care what kind of tax it is - just calls calculateTax()
3. Composition Over Hardcoding
PayItems contain tax models (via std::vector<std::shared_ptr<TaxModel>>)
Not hardcoded like "if UK then calculate income tax"
Flexible: different items can have different combinations of taxes
4. Factory Pattern for Construction
Factories encapsulate country-specific rules
UKPayItemFactory knows: "salary gets income tax + NI + student loan"
USPayItemFactory knows: "salary gets federal tax + social security"
Client code just calls factory.createSalary(3000) - factory handles the complexity
Data Flow
1. Factory creates PayItem with appropriate TaxModels attached
   └─> UKPayItemFactory.createSalary(3000)
       └─> PayItem { amount: 3000, taxModels: [IncomeTax, NI, StudentLoan] }

2. Payslip receives the PayItem
   └─> payslip.addItem(item)

3. Payslip computes taxes
   └─> For each PayItem:
       └─> For each TaxModel in item.taxModels:
           └─> tax = model.calculateTax(item.amount)
           └─> Accumulate totals

4. Payslip displays results
   └─> Shows items, taxes, net pay
Country Extensibility
Adding a new country (e.g., France):
Create FRIncomeTaxModel : TaxModel
Create FRSocialChargesModel : TaxModel
Create FRPayItemFactory
Done - no changes to PayItem or Payslip
Key Design Decisions
PayItem stores tax models as pointers - allows polymorphism, shared ownership
Factory owns tax model instances - configured once per person's circumstances
Multiple items share same tax model instances - efficient, models are stateless calculators
EffectType separate from tax treatment - EffectType is for accounting (gross/net), TaxModels are for actual tax rules