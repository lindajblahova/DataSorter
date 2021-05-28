#pragma once

#include "../Filters/Filter.h"
#include "../structures/heap_monitor.h"

template <typename V>
class FilterValue : public Filter<V>
{
public:
	FilterValue(Criterion<V>* criterion, V value);
	bool meetsFilter(TerritorialUnit* object) override;
	~FilterValue();

protected:
	V value_;
};

template<typename V>
inline FilterValue<V>::FilterValue(Criterion<V>* criterion, V value) : Filter<V>::Filter(criterion), value_(value)
{
}

template<typename V>
inline bool FilterValue<V>::meetsFilter(TerritorialUnit* object)
{
	return this->criterion_->rate(object) == value_;
}

template<typename V>
inline FilterValue<V>::~FilterValue()
{
}