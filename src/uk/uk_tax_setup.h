#pragma once
#include <memory>
#include "uk_tax_code.h"
#include "../tax/tax_registry.h"

std::shared_ptr<TaxRegistry> createUKTaxRegistry(std::shared_ptr<UKTaxCode> taxCode, int period);