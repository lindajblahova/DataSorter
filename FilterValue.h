#pragma once

#include "Filter.h"
#include "structures/heap_monitor.h"

template <typename V>
class FilterValue : public Filter<V>
{
public:
	FilterValue(Criterion<V>* criterion, V value);
	bool meetsFilter(TerritorialUnit* object) override;
	//void filterTable(structures::SortedSequenceTable<K, TerritorialUnit*>* table, structures::LinkedList<TerritorialUnit*>* newList) override;
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

/*template<typename K, typename V>
inline void FilterValue<K, V>::filterTable(structures::SortedSequenceTable<K, TerritorialUnit*>* table, structures::LinkedList<TerritorialUnit*>* newList)
{
	TerritorialUnit* tmp = nullptr;
	table->tryFind(, tmp);
	if (tmp != nullptr)
	{
		newList->add(tmp);
	}
}*/