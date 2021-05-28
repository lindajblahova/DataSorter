#pragma once

#include "../TerritorialUnit/TerritorialUnit.h"
#include "CompositeFilter.h"
#include "FilterTable.h"
#include "../structures/table/unsorted_sequence_table.h"
#include <string>
#include <iostream>
class Filtration 
{
public:
	Filtration();
	void TableFiltration(TerritorialUnit* parentTU, CompositeFilter* filters_, TypeTU type, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable, wstring* name);
	~Filtration();

private:
	void FilterAlgorithm(TerritorialUnit* parentTU, FilterTable* filterTable, CompositeFilter* filters_, TypeTU type,
        UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable, wstring* name, bool alreadyFiltered = false);
    bool applyFilters(CompositeFilter* filters_, TerritorialUnit* tu, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable);

};

Filtration::Filtration()
{
}

inline Filtration::~Filtration()
{
}

inline void Filtration::TableFiltration(TerritorialUnit* parentTU, CompositeFilter* filters_, TypeTU type, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable, wstring* name)
{
    FilterTable* filterTable = new FilterTable(*name);
    applyFilters(filters_, parentTU, newTable);
    FilterAlgorithm(parentTU, filterTable, filters_, type, newTable, name);
    delete filterTable;
}

inline void Filtration::FilterAlgorithm(TerritorialUnit* parentTU, FilterTable* filterTable, CompositeFilter* filters_,
    TypeTU type, UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable, wstring* name, bool alreadyFiltered)
{

    if (!name->empty() && (parentTU->getType() == type + 1) && !alreadyFiltered) // ak je to bodove hladanie a potomkovia su hladaneho typu alebo all a ešte som ich 
    {                                                                                           // neprehladala tryFindom
        if (filterTable->filterTable(parentTU->getChildren(), newTable))                        // prehladam ich tryfindom a ak som nasla skoncim
        {
            return;
        }
    }
    for (auto childTU : *parentTU->getChildren())                                               // ak som nenasla tak ich prejdem foreachom 
    {
        if ((applyFilters(filters_, childTU->accessData(), newTable) && type != All) || (childTU->accessData()->getChildren() == nullptr)) // ak child splna filtre a je zadany                                                                 
        {                                                                                                                   // konkretny typ alebo ak child uz nema potomkov
            continue;                                                                                                       // tak len pokracujem v cykle
        }

        if (!name->empty() && ((childTU->accessData()->getType() == type + 1) ||
            (childTU->accessData()->getType() == District && type == All)))    // ak je to bodove hladanie a potomkovia su hladaneho typu alebo all
        {
            if (filterTable->filterTable(childTU->accessData()->getChildren(), newTable))       // skusim ich prehladat tryFindom a ak som nasla tak breaknem
            {
                break;
            }
            alreadyFiltered = true;                                                             // nastavím si flag, ze uz som potomkov prehladala trfindom aby v rekurzii
        }                                                                                       // neboli prehladani este raz
        if ((name->empty() && childTU->accessData()->getType() != type) || (!name->empty() && childTU->accessData()->getType() != District))  // ak to nie je bodove hladanie a 
                                                                                                //este nie  som na type kt. hladam, alebo ak je* ale type nie je okres
                                                                                                // *(ak nebol najdeny v bodovom (idem hladat v detoch))
        {
            FilterAlgorithm(childTU->accessData(), filterTable, filters_, type, newTable, name, alreadyFiltered); // rekurzia
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