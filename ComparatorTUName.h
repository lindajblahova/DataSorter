#pragma once

#include "Comparator.h"
#include "AllCriteriaTU.h"
#include "TerritorialUnit.h"

class ComparatorTUName : public Comparator
{
public:
    ComparatorTUName(bool compAscending);
    int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) override;

private:
    CriterionTUName crit_;
};

inline ComparatorTUName::ComparatorTUName(bool compAscending) : Comparator(compAscending)
{
}

int ComparatorTUName::compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2)
{
    if (crit_.rate(tu1) > crit_.rate(tu2))
        return 1;
    else if (crit_.rate(tu1) == crit_.rate(tu2))
        return 0;
    else
        return -1;
}