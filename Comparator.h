#pragma once

#include "TerritorialUnit.h"

class Comparator
{
public:
    Comparator(bool compAscending);
    virtual int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) = 0;
    virtual int compareTU(TerritorialUnit* tu1, TerritorialUnit* tu2);
    virtual ~Comparator();

private:
    bool compAscending_;
};

inline Comparator::Comparator(bool compAscending) : compAscending_(compAscending)
{
}

int Comparator::compareTU(TerritorialUnit* tu1, TerritorialUnit* tu2)
{
    return (compAscending_ ? compareByCriterion(tu1, tu2) : compareByCriterion(tu2, tu1));
}

inline Comparator::~Comparator()
{
}
