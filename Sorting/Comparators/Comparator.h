#pragma once

#include "../../TerritorialUnit/TerritorialUnit.h"
#include "../../Criteria/Criterion.h"
#include "../../structures/heap_monitor.h"


template <typename V>
class Comparator
{
public:
    Comparator(bool compAscending, Criterion<V>* criterion);
    virtual int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) = 0;
    int compareTU(TerritorialUnit* tu1, TerritorialUnit* tu2);
    virtual ~Comparator();

protected:
    Criterion<V>* criterion_;

private:
    bool compAscending_;
   
};

template <typename V>
inline Comparator<V>::Comparator(bool compAscending, Criterion<V>* criterion) : compAscending_(compAscending), criterion_(criterion)
{
}

template <typename V>
int Comparator<V>::compareTU(TerritorialUnit* tu1, TerritorialUnit* tu2)
{
    return (compAscending_ ? compareByCriterion(tu1, tu2) : compareByCriterion(tu2, tu1));
}
template <typename V>
inline Comparator<V>::~Comparator()
{
    delete criterion_;
}
