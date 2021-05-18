#pragma once

#include "Criterion.h"
#include "FilterBase.h"
#include "structures/heap_monitor.h"

template <typename V>
class Filter : public FilterBase
{

public:
	Filter(Criterion<V>* criterion);
	virtual bool meetsFilter(TerritorialUnit* object) = 0;
	~Filter();

protected:
	 Criterion<V>* criterion_;
};

template<typename V>
inline Filter<V>::Filter(Criterion<V>* criterion) : FilterBase::FilterBase()
{
	criterion_ = criterion;
}

template<typename V>
inline Filter< V>::~Filter()
{
	delete criterion_;
	criterion_ = nullptr;
}

