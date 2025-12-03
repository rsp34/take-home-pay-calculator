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
2. Tax: Tax tracking - represents a tax due on a specific line item
3. Factory: Construction logic - knows which taxes apply to which items
4. Payslip: Orchestration - manages items, triggers calculations, displays results

Tax is an abstract interface where each jurisdiction implements its own concrete taxes (e.g., `UKIncomeTax`, `USFederalTax`). PayItem doesn't care what kind of tax it is - just calls `calculateTax()`.

PayItems contain taxes (via `std::vector<std::unique_ptr<Tax>>`). Not hardcoded like "if UK then calculate income tax".  Different items can have different combinations of taxes. Each pay item owns its taxes.

`Tax`es, `PayItems`, `Payslips`,  and  can be accumulated and split using the add and divide operators. The accumulation works over all levels as follows:

- Tax + Tax = combined tax calculation
- PayItem + PayItem = combined items with accumulated taxes  
- Payslip + Payslip = combined payslips (would contain equivalent information to a tax return)

A  year's worth of payslips may be elegantly summarised, 

```
annual_income = jan + feb + mar + ... + dec
```

or, split into daily payslips.

```
daily_income = annual_income*Period::Annual/Period::Daily
```

Factories encapsulate country-specific rules, e.g.:

- UKPayItemFactory knows: "salary gets income tax + NI + student loan"
- USPayItemFactory knows: "salary gets federal tax + social security"

Client code just calls factory.createSalary(3000). Adding a new country requires adding a new factory and the necessary tax models, without the need to change PayItem or Payslip.

EffectType separate from tax treatment - EffectType is for accounting (gross/net), TaxModels are for actual tax rules.

### Design Summary
1. Factory creates PayItem with appropriate Taxes attached
```
   └─> UKPayItemFactory.createSalary(3000)
       └─> PayItem { amount: 3000, taxes: [IncomeTax, NI, StudentLoan] }
```

2. Payslip receives the PayItem
```
   └─> payslip.addItem(item)
```

3. Payslip computes taxes
```
   └─> For each PayItem:
       └─> For each tax in item.taxes:
           └─> taxDue = tax.calculate(item.amount)
           └─> Accumulate totals
```

4. Payslip displays results
```
   └─> Shows items, taxes, net pay
```

## Project Structure
Jurisdiction-specific code is stored in seperate folders e.g. there is a `uk` folder.

## Technologies
A focus of this project is understanding the features of C++.

The features I would like to leverage as part of this project are:

1. Smart pointers
2. Threads - might be difficult.
3. Use of 3rd party libraries
4. Testing in C++
5. Create a Python wrapper
6. Implement a REST api

## Ideas
- A "what-if" feature to compare old tax years to the present.
- Time bounds for each rule as taxes are relevant in a given year.
- "Company value" could also be interesting. How much is my employer paying for the benefit of employing me - main addition would be employer N.I.

# ToDo
I've attempted to estimate times here...
- [ ] Switch from frequency to period (10 minutes)
- [ ] Re-implement the Tax classes (2 hours)
- [ ] Re-implement the PayItem class to reference new tax class (0.5 hours)
- [ ] Switch to pennies and use ratio (1 hour)
- [ ] Each class should have it's own separate file  (accounted above)
- [ ] Break out headers (accounted above)
- [ ] Remove all the magic numbers (accounted above)
- [ ] Break out one-liners (accounted above)
- [ ] Overload operators to enable summation and division (3 hours)
- [ ] Improve the main function so it does something (2 hours)
- [ ] Switch the main function to a CLI interface (3 hours)
- [ ] Implement testing
- [ ] Add some CI/CD to releases