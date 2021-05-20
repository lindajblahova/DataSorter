#pragma once

#include "Filter.h"
#include "TerritorialUnit.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/list/linked_list.h"
#include "structures/heap_monitor.h"

using namespace structures;

template <typename K>
class FilterTable
{
public:
	FilterTable(K value);
	bool filterTable(SortedSequenceTable<K, TerritorialUnit*>* table, UnsortedSequenceTable<wstring, TerritorialUnit*>* newList);

private:
	K key_;
};

template<typename K>
inline FilterTable<K>::FilterTable(K key) : key_(key)
{
}

template<typename K>
inline bool FilterTable<K>::filterTable(SortedSequenceTable<K, TerritorialUnit*>* table, UnsortedSequenceTable<wstring, TerritorialUnit*>* newList)
{
	TerritorialUnit* tmp = nullptr;
	table->tryFind(key_, tmp);
	if (tmp != nullptr)
	{
		newList->insert(tmp->getName(), tmp);
		return true;
	}
	return false;
}
