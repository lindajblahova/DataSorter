#pragma once

#include "Criterion.h"
#include "Table.h"

template <typename K, typename T, typename V>
class Filter 
{
public:
	Filter(Criterion<V, T> criterion);
	virtual bool meetsFilter(T* object) = 0;
	void filterTable(Table<K, T> table, Table<K, T> newTable);

protected:
	 Criterion<V, T> criterion_;
};

template<typename K, typename T, typename V>
inline Filter<K, T, V>::Filter(Criterion<V, T> criterion)
{
	criterion_ = criterion;
}
