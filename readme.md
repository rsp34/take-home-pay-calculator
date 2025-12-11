# Take Home Pay Calculator

## Requirements
- A user may predict their payslip, including for multiple jobs, by entering their annual salary and benefits.
- A user may enter their current payslip, including for multiple jobs, and see this scaled to other frequencies.
- We want proportional and marginal taxation view.
- Frequencies of interest are daily, work day, weekly, monthly and annually.
- Looping over the would be interesting.

## Design

### Key Design Decisions
The project is split into 5 components:

1. **PayItem**: Domain model - represents a line item (salary, bonus, pension, etc.)
   - Has an `EffectType` for accounting (TaxableAddition, PreTaxDeduction, etc.)
   - Declares which taxes apply by name
   - Stores computed tax amounts after calculation

2. **Tax**: Stateless calculator - pure function that calculates tax on a given amount
   - Each tax is its own class (UKIncomeTax, UKNationalInsurance, etc.)
   - Pure function: `int64_t calculateTax(int64_t amount) const`

3. **TaxComputationStrategy**: Accumulation logic - defines how to apply a tax across multiple items
   - `CumulativeTaxStrategy`: Accumulates amounts, calculates once, distributes proportionally
   - `FlatTaxStrategy`: Calculates per item independently

4. **TaxRegistry**: Configuration - maps tax names to calculators and strategies
   - Created once per jurisdiction at startup
   - Single source of truth for all available taxes

5. **Payslip**: Orchestration - manages items, triggers calculations, displays results

#### Tax Calculation Flow

**Two types of taxes:**
- **Flat taxes** (Employer NI, pensions): Calculate independently per item
- **Cumulative taxes** (Income Tax, Employee NI): Accumulate across items, then attribute back

**Architecture:**
```
Payslip → TaxRegistry → TaxComputationStrategy → Tax calculator
```

#### Jurisdiction-Specific Components

Each jurisdiction (UK, US, etc.) provides:

1. **Tax Calculators**: Individual classes implementing the `Tax` interface
   - `UKIncomeTax`, `UKNationalInsurance`, `UKEmployerNI`, etc.
   - Each in its own file with the tax formula

2. **Tax Name Constants**: Compile-time constants to eliminate string duplication
   - `UKTaxNames::INCOME_TAX`, `UKTaxNames::EMPLOYEE_NI`, etc.
   - Used by both registry and factory

3. **Registry Setup Function**: Registers all jurisdiction taxes in one place
   - `createUKTaxRegistry()` - lists all UK taxes with their strategies
   - Easy to see all taxes at a glance

4. **PayItem Factory**: Creates items with correct taxes applied
   - `UKPayItemFactory::createSalary()` - knows salary gets income tax + NI
   - Encapsulates jurisdiction-specific rules

**Adding a new jurisdiction:**
- Create tax calculator classes
- Create constants file
- Create registry setup function
- Create factory
- No changes needed to PayItem, Payslip, or core tax infrastructure

### Design Summary

1. **Registry setup (done once at initialization)**
```
   └─> createUKTaxRegistry(taxCode, period)
       ├─> Creates individual tax calculators:
       │   ├─> UKIncomeTax(taxCode, period)
       │   ├─> UKNationalInsurance(period)
       │   └─> UKEmployerNI(period)
       ├─> Creates reusable strategies:
       │   ├─> CumulativeTaxStrategy (shared)
       │   └─> FlatTaxStrategy (shared)
       └─> TaxRegistry
           ├─> UKTaxNames::INCOME_TAX → (UKIncomeTax, CumulativeStrategy)
           └─> UKTaxNames::EMPLOYEE_NI → (UKNationalInsurance, CumulativeStrategy)
```

2. **Factory creates PayItem with tax declarations**
```
   └─> UKPayItemFactory.createSalary(3000)
       └─> PayItem {
             name: "Salary",
             amount: 3000,
             effectType: TaxableAddition,
             taxes: [UKTaxNames::INCOME_TAX, UKTaxNames::EMPLOYEE_NI],
             taxAmounts: {} (empty until computed)
           }
```

3. **Payslip receives the PayItem**
```
   └─> Payslip.addItem(salary)
       └─> payItems vector now contains: [salary, bonus, ...]
```

4. **Payslip computes taxes**
```
   └─> Payslip.computeTaxes()
       └─> For each tax name (INCOME_TAX, EMPLOYEE_NI):
           ├─> TaxRegistry.getTaxRegistration(INCOME_TAX)
           │   └─> Returns: (UKIncomeTax calculator, CumulativeStrategy)
           ├─> CumulativeStrategy.computeTax(payItems, INCOME_TAX, UKIncomeTax)
           │   ├─> Accumulate: £3000 + £1000 = £4000
           │   ├─> Calculate: UKIncomeTax.calculateTax(£4000) = £590
           │   └─> Distribute: salary 75% (£442.50), bonus 25% (£147.50)
           └─> Store results back in PayItems:
               ├─> salary.taxAmounts[INCOME_TAX] = £442.50
               └─> bonus.taxAmounts[INCOME_TAX] = £147.50
```

5. **Display results**
```
   └─> For each PayItem:
       ├─> salary.getTaxAmount(INCOME_TAX) → £442.50
       ├─> salary.getTaxAmount(EMPLOYEE_NI) → £240.00
       └─> Total tax = £682.50, Net pay = £2317.50
```

#### Operator Overloading

Taxes, PayItems, and Payslips can be accumulated and split using operators:

- Tax + Tax = combined tax calculation
- PayItem + PayItem = combined items with accumulated taxes
- Payslip + Payslip = combined payslips (would contain equivalent information to a tax return)

A year's worth of payslips may be elegantly summarised:

```cpp
annual_income = jan + feb + mar + ... + dec
```

or split into daily payslips:

```cpp
daily_income = annual_income*Period::Annual/Period::Daily
```

## Project Structure
```
src/
├─ tax/                              # Core tax infrastructure (jurisdiction-agnostic)
│  ├─ tax.h                         # Tax interface
│  ├─ tax_computation_strategy.h    # Strategy interface
│  ├─ cumulative_tax_strategy.h/cpp # Cumulative logic
│  ├─ flat_tax_strategy.h/cpp       # Flat logic
│  └─ tax_registry.h/cpp            # Registry
├─ pay/                              # Pay domain models (jurisdiction-agnostic)
│  ├─ pay_item.h                    # PayItem with EffectType
│  └─ payslip.h/cpp                 # Payslip orchestrator
└─ uk/                               # UK-specific implementation
   ├─ uk_tax_names.h                # Tax name constants
   ├─ uk_income_tax.h/cpp           # Income Tax calculator
   ├─ uk_national_insurance.h/cpp   # NI calculator
   ├─ uk_employer_ni.h/cpp          # Employer NI calculator
   ├─ uk_tax_setup.h/cpp            # Registry setup (all UK taxes)
   └─ uk_pay_item_factory.h         # UK item factory
```

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
- [x] Switch from frequency to period
- [x] Switch to pennies and use int64_t
- [x] Each class in separate file with headers
- [x] Implement Strategy + Registry pattern for tax computation
  - [x] Create TaxComputationStrategy interface
  - [x] Implement CumulativeTaxStrategy and FlatTaxStrategy
  - [x] Create TaxRegistry
  - [x] Create UK tax name constants
  - [x] Update PayItem with applicableTaxes and taxAmounts
  - [x] Rewrite Payslip.computeTaxes() to use registry
  - [x] Add a Payslip.print?
  - [x] Clarify nomenclature around compute and calculate as its confusing
  - [x] Create UK tax setup with registration
- [x] Complete UKIncomeTax and UKNationalInsurance implementations
- [ ] Create currency types so that we are using the right currencies
- [ ] Overload the "<<" operator for pennies for printing PayItem
- [ ] Update payItems and tax to use a currency
- [ ] Create own alternative to ratio to avoid template usage
- [ ] Fix includes
- [ ] Remove string_view
- [ ] TaxRegistration could be overkill as C++ developers prefer to avoid small class declaration?
- [ ] Assess usage of structs vs classes vs functions vs namespace
- [ ] Include the PayItem knowledge in the tax registry?
- [ ] Overload operators for summation and division
- [ ] Implement a CLI interface for the main function
- [ ] Build out tests
- [ ] Add CI/CD and first release
- [ ] Build out UK tax rules
- [ ] Add a Python wrapper

## References
https://uk-income.zainp.com/
https://www.thesalarycalculator.co.uk/