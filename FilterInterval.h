#pragma once

#include "Filter.h"

template <typename K, typename T, typename V>
class FilterInterval : public Filter<K, T, V>
{
public:
	FilterInterval(Criterion<T, V> criterion, V minValue, V maxValue);
	bool meetsFilter(T* object) override;

private:
	V minValue_;
	V maxValue_;
};

template<typename K, typename T, typename V>
inline FilterInterval<K, T, V>::FilterInterval(Criterion<T, V> criterion, V minValue, V maxValue) : 
	Filter(criterion), minValue_(minValue), maxValue_(maxValue)
{
}

template<typename K, typename T, typename V>
inline bool FilterInterval<K, T, V>::meetsFilter(T* object)
{
	return criterion_->rate(object) >= minValue_ && criterion_->rate(object) <= maxValue_;
}
