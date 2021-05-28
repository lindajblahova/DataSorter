#pragma once
#include <string>
#include "FilterValue.h"
#include "FilterInterval.h"
#include "../Criteria/Criterion.h"
#include "../TerritorialUnit/TypeTU.h"

#include "../structures/heap_monitor.h"

class FilterTUName : public FilterValue<wstring> {
public:
	FilterTUName(Criterion<wstring>* criterion, wstring value);
	~FilterTUName();
};
inline FilterTUName::FilterTUName(Criterion<wstring>* criterion, wstring value) : FilterValue<wstring>::FilterValue(criterion, value)
{
}
inline FilterTUName::~FilterTUName()
{
}

class FilterTUType : public FilterValue<TypeTU> {
public:
	FilterTUType(Criterion<TypeTU>* criterion, TypeTU value);
	~FilterTUType();
};
inline FilterTUType::FilterTUType(Criterion<TypeTU>* criterion, TypeTU value) : FilterValue<TypeTU>::FilterValue(criterion, value)
{
}

inline FilterTUType::~FilterTUType()
{
}

class FilterTUPopulation : public FilterInterval<int> {
public:
	FilterTUPopulation(Criterion<int>* criterion, int min, int max);
	~FilterTUPopulation();
};
inline FilterTUPopulation::FilterTUPopulation(Criterion<int>* criterion, int min, int max) : FilterInterval<int>::FilterInterval(criterion, min, max)
{
}
inline FilterTUPopulation::~FilterTUPopulation()
{
}

class FilterTUBuildUpRate : public FilterInterval<double> {
public:
	FilterTUBuildUpRate(Criterion<double>* criterion, double min, double max);
	~FilterTUBuildUpRate();
};
inline FilterTUBuildUpRate::FilterTUBuildUpRate(Criterion<double>* criterion, double min, double max) : FilterInterval<double>::FilterInterval(criterion, min, max)
{
}
inline FilterTUBuildUpRate::~FilterTUBuildUpRate()
{
}
