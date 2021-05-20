#pragma once
#include <string>
#include "FilterValue.h"
#include "FilterInterval.h"
#include "structures/heap_monitor.h"

class FilterTUName : public FilterValue<wstring> {
public:
	FilterTUName(Criterion<wstring>* criterion, wstring value);
	bool meetsFilter(TerritorialUnit* object) override;
	~FilterTUName();
};
inline FilterTUName::FilterTUName(Criterion<wstring>* criterion, wstring value) : FilterValue<wstring>::FilterValue(criterion, value)
{
}
inline bool FilterTUName::meetsFilter(TerritorialUnit* object)
{
	return this->value_.compare(criterion_->rate(object)) == 0 ? true : false;
}
inline FilterTUName::~FilterTUName()
{
}

class FilterTUType : public FilterValue<TypeTU> {
public:
	FilterTUType(Criterion<TypeTU>* criterion, TypeTU value);
	bool meetsFilter(TerritorialUnit* object) override;
	~FilterTUType();
};
inline FilterTUType::FilterTUType(Criterion<TypeTU>* criterion, TypeTU value) : FilterValue<TypeTU>::FilterValue(criterion, value)
{
}
bool FilterTUType::meetsFilter(TerritorialUnit* object)
{
	if (this->value_ == All)
	{
		return true;
	}
	else
	{
		return this->value_ == criterion_->rate(object);
	}
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
