#pragma once

#include "Comparator.h"
#include "../../Criteria/AllCriteriaTU.h"
#include "../../TerritorialUnit/TerritorialUnit.h"
#include "../../structures/heap_monitor.h"


#include <iostream>
#include <string>

class ComparatorTUName : public Comparator<wstring>
{
public:
    ComparatorTUName(bool compAscending);
    int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) override;
    ~ComparatorTUName();

};

inline ComparatorTUName::ComparatorTUName(bool compAscending) : Comparator(compAscending, new CriterionTUName()) {
    
}

int ComparatorTUName::compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2)
{
    if (this->criterion_->rate(tu1) > this->criterion_->rate(tu2))
    {
        return 1;
    }
    return 0;
}

inline ComparatorTUName::~ComparatorTUName()
{
}
