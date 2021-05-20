#pragma once

#include "TerritorialUnit.h"
#include "CompositeFilter.h"
#include "structures/table/unsorted_sequence_table.h"
#include <string>
#include <iostream>
class Filtration 
{
public:
	Filtration();
	void FilterAlgorithm(TerritorialUnit* parentTU, CompositeFilter* filters_, TypeTU type, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable, wstring* name);
	~Filtration();

private:
	void FilterInnerRecursion(TerritorialUnit* parentTU, FilterTable<wstring>* filterTable, CompositeFilter* filters_, TypeTU type, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable, wstring* name);
    bool applyFilters(CompositeFilter* filters_, TerritorialUnit* tu, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable);

};

Filtration::Filtration()
{
}

inline Filtration::~Filtration()
{
}

inline void Filtration::FilterAlgorithm(TerritorialUnit* parentTU, CompositeFilter* filters_, TypeTU type, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable, wstring* name)
{
    bool found = false;
    TerritorialUnit* tmp = nullptr;
    FilterTable<wstring>* filterTable = new FilterTable<wstring>(*name);

    applyFilters(filters_, parentTU, newTable);

    if (name != nullptr)
    {
        found = filterTable->filterTable(parentTU->getChildren(), newTable);
    }
    if (!found)
    {
        FilterInnerRecursion(parentTU, filterTable, filters_, type, newTable, name);
    }
    delete filterTable;
}

inline void Filtration::FilterInnerRecursion(TerritorialUnit* parentTU, FilterTable<wstring>* filterTable, CompositeFilter* filters_,
    TypeTU type, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable, wstring* name)
{
    bool found = false;
    for (auto childTU : *parentTU->getChildren())
    {
        if (applyFilters(filters_, childTU->accessData(), newTable) && type != All)        // kontrola filtrov na child                                                                  
        {
            continue;
        }
        if (childTU->accessData()->getChildren() == nullptr)                              // ak mam children (obec ma children nullptr)
        {
            continue;
        }
        if (*name != L"")                                               // bodove hladanie
        {
            found = filterTable->filterTable(childTU->accessData()->getChildren(), newTable);
            if (found)
            {
                break;
            }
        }
        if (*name == L""|| !found)                                     // ak nebol najdeny v bodovom (idem hladat v detoch) alebo nie je bodove hladanie
        {
            FilterInnerRecursion(childTU->accessData(), filterTable, filters_, type, newTable, name);
        }
    }
}

inline bool Filtration::applyFilters(CompositeFilter* filters_, TerritorialUnit* tu, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable)
{
    if (filters_->meetsFilter(tu))
    {
        newTable->insert(tu->getName(), tu);
        return true;
    }
    return false;
}