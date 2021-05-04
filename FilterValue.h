#pragma once

#include "Filter.h"

template <typename K, typename T, typename V>
class FilterValue : public Filter<K, T, V>
{
public:
	FilterValue(Criterion<T, V> criterion, V value);
	bool meetsFilter(T* object) override;

private:
	V value_;
};

template<typename K, typename T, typename V>
inline FilterValue<K, T, V>::FilterValue(Criterion<T, V> criterion, V value) : Filter(criterion), value_(value)
{
}

template<typename K, typename T, typename V>
inline bool FilterValue<K, T, V>::meetsFilter(T* object)
{
	return criterion_->rate(object) == value_;
}
