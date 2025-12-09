#pragma once
#include <memory>

class TaxRegistry;
class UKTaxCode;

std::shared_ptr<TaxRegistry> createUKTaxRegistry(std::shared_ptr<UKTaxCode> taxCode);