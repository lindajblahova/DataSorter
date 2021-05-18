#pragma once

#include "Comparator.h"
#include "AllCriteriaTU.h"
#include "TerritorialUnit.h"

class ComparatorTUPopulation : public Comparator
{
public:
    ComparatorTUPopulation(bool compAscending);
    int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) override;

private:
    CriterionTUPopulation crit_;
};

inline ComparatorTUPopulation::ComparatorTUPopulation(bool compAscending) : Comparator(compAscending)
{
}

int ComparatorTUPopulation::compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2)
{
    if (crit_.rate(tu1) > crit_.rate(tu2))
        return 1;
    else if (crit_.rate(tu1) == crit_.rate(tu2))
        return 0;
    else
        return -1;
}