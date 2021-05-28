#pragma once

#include "../Criteria/Criterion.h"
#include "../TerritorialUnit/TerritorialUnit.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "../structures/heap_monitor.h"

class FilterBase
{

public:
    FilterBase();
    ~FilterBase();
    virtual bool meetsFilter(TerritorialUnit* obj) = 0;
};

FilterBase::FilterBase()
{
}

inline FilterBase::~FilterBase()
{
}