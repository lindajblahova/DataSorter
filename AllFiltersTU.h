#pragma once

#include "FilterValue.h"
#include "FilterInterval.h"
#include "TerritorialUnit.h"
#include <string>

class FilterTUName : public FilterValue<string, TerritorialUnit, string> {
};

class FilterTUType : public FilterValue<TypeTU, TerritorialUnit, TypeTU> {
};

class FilterTUHasParent : public FilterValue<bool, TerritorialUnit, bool> { // TODO toto bude nejako inac asi na stringy ?
};

class FilterTUPopulation : public FilterInterval<int, TerritorialUnit, int> {
};

class FilterTUBuildUpRate : public FilterInterval<double, TerritorialUnit, double> {
};