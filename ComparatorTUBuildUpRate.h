#pragma once

#include "Comparator.h"
#include "AllCriteriaTU.h"
#include "TerritorialUnit.h"

class ComparatorTUBuildUpRate : public Comparator
{
public:
    ComparatorTUBuildUpRate(bool compAscending);
    int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) override;

private:
    CriterionTUBuildUpRate crit_;
};

inline ComparatorTUBuildUpRate::ComparatorTUBuildUpRate(bool compAscending) : Comparator(compAscending)
{
}

int ComparatorTUBuildUpRate::compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2)
{
    if (crit_.rate(tu1) > crit_.rate(tu2))
        return 1;
    else if (crit_.rate(tu1) == crit_.rate(tu2))
        return 0;
    else
        return -1;
}