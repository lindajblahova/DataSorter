#pragma once

#include "../structures/table/sorting/heap_sort.h"
#include "../structures/table/unsorted_sequence_table.h"
template <typename V>
class Sorter
{
public:
    Sorter(Comparator<V>* comparator);
    void sort(UnsortedSequenceTable<wstring, TerritorialUnit*>* table);
    ~Sorter();

private:
    HeapSort<wstring, TerritorialUnit*, V>* sorter_;
    Comparator<V>* comparator_;
};
template <typename V>
Sorter<V>::Sorter(Comparator<V>* comparator) : sorter_(new  HeapSort<wstring, TerritorialUnit*, V>()), comparator_(comparator)
{
}

template <typename V>
inline void Sorter<V>::sort(UnsortedSequenceTable<wstring, TerritorialUnit*>* table)
{
    sorter_->sort(*table, comparator_);
}
template <typename V>
inline Sorter<V>::~Sorter()
{
    delete sorter_;
    delete comparator_;
}
