#pragma once

#include "Comparator.h"
#include "AllCriteriaTU.h"
#include "TerritorialUnit.h"

class ComparatorTUPopulation : public Comparator
{
public:
    ComparatorTUPopulation(bool compAscending);
    int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) override;
    ~ComparatorTUPopulation();

private:
    CriterionTUPopulation* crit_;

};

inline ComparatorTUPopulation::ComparatorTUPopulation(bool compAscending) : Comparator(compAscending), crit_(new CriterionTUPopulation())
{
}

int ComparatorTUPopulation::compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2)
{
    typedef std::chrono::high_resolution_clock Time;

    auto t0 = Time::now();

    if (crit_->rate(tu1) > crit_->rate(tu2))
    {
        return 1;
    }
    else if (crit_->rate(tu1) < crit_->rate(tu2))
    {
        return -1;
    }
    return 0;
}

inline ComparatorTUPopulation::~ComparatorTUPopulation()
{
    delete crit_;
}
