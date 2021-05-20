#pragma once

#include "Comparator.h"
#include "AllCriteriaTU.h"
#include "TerritorialUnit.h"

class ComparatorTUBuildUpRate : public Comparator
{
public:
    ComparatorTUBuildUpRate(bool compAscending);
    int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) override;
    ~ComparatorTUBuildUpRate();

private:
    CriterionTUBuildUpRate* crit_;
};

inline ComparatorTUBuildUpRate::ComparatorTUBuildUpRate(bool compAscending) : Comparator(compAscending), crit_(new CriterionTUBuildUpRate())
{
}

int ComparatorTUBuildUpRate::compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2)
{
    if (crit_->rate(tu1) > crit_->rate(tu2))
    {
        return 1;
    }
    else if (crit_->rate(tu1) > crit_->rate(tu2))
    {
        return -1;
    }
    return 0;
       
}

inline ComparatorTUBuildUpRate::~ComparatorTUBuildUpRate()
{
    delete crit_;
}
