#pragma once

#include "Comparator.h"
#include "../../Criteria/AllCriteriaTU.h"
#include "../../TerritorialUnit/TerritorialUnit.h"
#include "../../structures/heap_monitor.h"


class ComparatorTUPopulation : public Comparator<int>
{
public:
    ComparatorTUPopulation(bool compAscending);
    int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) override;
    ~ComparatorTUPopulation();

};

inline ComparatorTUPopulation::ComparatorTUPopulation(bool compAscending) : Comparator(compAscending, new CriterionTUPopulation())
{
}

int ComparatorTUPopulation::compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2)
{
    //typedef std::chrono::high_resolution_clock Time;
    //auto t0 = Time::now();

    if (this->criterion_->rate(tu1) > this->criterion_->rate(tu2))
    {
        return 1;
    }
    return 0;
}

inline ComparatorTUPopulation::~ComparatorTUPopulation()
{
}
