#pragma once

#include "Comparator.h"
#include "../../Criteria/AllCriteriaTU.h"
#include "../../TerritorialUnit/TerritorialUnit.h"
#include "../../structures/heap_monitor.h"


class ComparatorTUBuildUpRate : public Comparator<double>
{
public:
    ComparatorTUBuildUpRate(bool compAscending);
    int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) override;
    ~ComparatorTUBuildUpRate();
};

inline ComparatorTUBuildUpRate::ComparatorTUBuildUpRate(bool compAscending) : Comparator(compAscending, new CriterionTUBuildUpRate())
{
}

int ComparatorTUBuildUpRate::compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2)
{
    if (this->criterion_->rate(tu1) > this->criterion_->rate(tu2))
    {
        return 1;
    }
    /*else if (this->criterion_->rate(tu1) > this->criterion_->rate(tu2))
    {
        return -1;
    }*/
    return 0;
       
}

inline ComparatorTUBuildUpRate::~ComparatorTUBuildUpRate()
{
}
