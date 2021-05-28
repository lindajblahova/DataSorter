#pragma once

#include "Filter.h"
#include "../TerritorialUnit/TerritorialUnit.h"
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/list/linked_list.h"
#include "../structures/heap_monitor.h"

using namespace structures;

class FilterTable
{
public:
	FilterTable(wstring value);
	bool filterTable(SortedSequenceTable<wstring, TerritorialUnit*>* table, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable);

private:
	wstring key_;
};

inline FilterTable::FilterTable(wstring key) : key_(key)
{
}

inline bool FilterTable::filterTable(SortedSequenceTable<wstring, TerritorialUnit*>* table, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable)
{
	TerritorialUnit* tmp = nullptr;
	table->tryFind(key_, tmp);
	if (tmp != nullptr)
	{
		newTable->insert(tmp->getName(), tmp);
		return true;
	}
	return false;
}
