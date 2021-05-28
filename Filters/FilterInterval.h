#pragma once

#include "Filter.h"
#include "../structures/heap_monitor.h"

template <typename V>
class FilterInterval : public Filter<V>
{
public:
	FilterInterval(Criterion<V>* criterion, V minValue, V maxValue);
	bool meetsFilter(TerritorialUnit* object) override;
	~FilterInterval();

private:
	V minValue_;
	V maxValue_;
};

template<typename V>
inline FilterInterval<V>::FilterInterval(Criterion<V>* criterion, V minValue, V maxValue) : 
	Filter<V>::Filter(criterion), minValue_(minValue), maxValue_(maxValue)

{
}

template<typename V>
inline bool FilterInterval<V>::meetsFilter(TerritorialUnit* object)
{
	return this->criterion_->rate(object) >= minValue_ && this->criterion_->rate(object) <= maxValue_;
}

template<typename V>
inline FilterInterval<V>::~FilterInterval()
{
}
