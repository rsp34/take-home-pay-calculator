# Take Home Pay Calculator

## Requirements
- A user may predict their payslip, including for multiple jobs, by entering their annual salary and benefits.
- A user may enter their current payslip, including for multiple jobs, and see this scaled to other frequencies.
- Frequencies of interest are daily, work day, weekly, monthly and annually.
- Looping over the would be interesting.

## Design

### Key Design Decisions
The project is split into 4 components: 

1. PayItem: Domain model - represents a line item (salary, bonus, pension, etc.)
2. TaxModel: Tax calculation logic - knows how to compute one specific tax
3. Factory: Construction logic - knows which taxes apply to which items
4. Payslip: Orchestration - manages items, triggers calculations, displays results

TaxModel is an abstract interface where each jurisdiction implements its own concrete tax models (e.g., `UKIncomeTaxModel`, `USFederalTaxModel`). PayItem doesn't care what kind of tax it is - just calls `calculateTax()`.

PayItems contain tax models (via `std::vector<std::shared_ptr<TaxModel>>`). Not hardcoded like "if UK then calculate income tax".  Different items can have different combinations of taxes. Multiple items can share same tax model instances.

Factories encapsulate country-specific rules, e.g.:

- UKPayItemFactory knows: "salary gets income tax + NI + student loan"
- USPayItemFactory knows: "salary gets federal tax + social security"

Client code just calls factory.createSalary(3000). Adding a new country requires adding a new factory and the necessary tax models, without the need to change PayItem or Payslip.

EffectType separate from tax treatment - EffectType is for accounting (gross/net), TaxModels are for actual tax rules.

### Design Summary
1. Factory creates PayItem with appropriate TaxModels attached
```
   └─> UKPayItemFactory.createSalary(3000)
       └─> PayItem { amount: 3000, taxModels: [IncomeTax, NI, StudentLoan] }
```

2. Payslip receives the PayItem
```
   └─> payslip.addItem(item)
```
3. Payslip computes taxes
```
   └─> For each PayItem:
       └─> For each TaxModel in item.taxModels:
           └─> tax = model.calculateTax(item.amount)
           └─> Accumulate totals
```

4. Payslip displays results
```
   └─> Shows items, taxes, net pay
```

## Technologies
A focus of this project is understanding the features of C++.

The features I would like to leverage as part of this project are:

1. Smart pointers
2. Threads
3. Use of 3rd party libraries
4. Testing in C++
5. Create a Python wrapper