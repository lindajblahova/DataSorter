#pragma once

#include "../Filters/Filter.h"
#include "../Filters/FilterBase.h"
#include "../TerritorialUnit/TerritorialUnit.h"
#include "../structures/heap_monitor.h"
#include "../structures/list/linked_list.h"

class CompositeFilter
{
public:
	CompositeFilter();
	void addFilter(FilterBase* filter);
	bool meetsFilter(TerritorialUnit* object);
	~CompositeFilter();
private:
	structures::List<FilterBase*>* filters_;
};

inline CompositeFilter::CompositeFilter()
{
	filters_ = new structures::LinkedList<FilterBase*>();
}

inline void CompositeFilter::addFilter(FilterBase* filter)
{
	filters_->add(filter);
}

inline bool CompositeFilter::meetsFilter(TerritorialUnit* object)
{
	if (filters_->isEmpty())
	{
		return true;
	}
	for (auto f : *filters_)
	{
		if (!f->meetsFilter(object))
		{
			return false;
		}
	}
	return true;
}

inline CompositeFilter::~CompositeFilter()
{
	delete filters_;
	filters_ = nullptr;
}
