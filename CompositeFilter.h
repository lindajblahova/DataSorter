#pragma once

#include "Filter.h"
#include "structures/list/linked_list.h"

template <typename K, typename T, typename V>
class CompositeFilter
{
public:
	void addFilter(Filter<K, T, V>* filter);
	bool meetsFilter(T* object) override;
private:
	structures::LinkedList<Filter<K, T, V>> filters_;
};

template<typename K, typename T, typename V>
inline void CompositeFilter<K, T, V>::addFilter(Filter<K, T, V>* filter)
{
	filters_->add(filter);
}

template<typename K, typename T, typename V>
inline bool CompositeFilter<K, T, V>::meetsFilter(T* object)
{
	for (auto filter : filters_)
	{
		if (!filter.meetsFilter(object))
		{
			return false;
		}
	}
	return true;
}
