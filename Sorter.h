#pragma once

#include "structures/table/sorting/heap_sort.h"
#include "structures/table/unsorted_sequence_table.h"
class Sorter
{
public:
    Sorter(Comparator* comparator_);
    void sort(UnsortedSequenceTable<wstring, TerritorialUnit*>* table);
    ~Sorter();

private:
    HeapSort<wstring, TerritorialUnit*>* sorter_;
    Comparator* comparator_;
};

Sorter::Sorter(Comparator* comparator) : sorter_(new  HeapSort<wstring, TerritorialUnit*>()), comparator_(comparator)
{
}

inline void Sorter::sort(UnsortedSequenceTable<wstring, TerritorialUnit*>* table)
{
    sorter_->sort(*table, comparator_);
}

inline Sorter::~Sorter()
{
    delete sorter_;
    delete comparator_;
}
