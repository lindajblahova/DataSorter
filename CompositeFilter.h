#pragma once

#include "Filter.h"
#include "TerritorialUnit.h"
#include "structures/heap_monitor.h"
#include "structures/list/linked_list.h"

class CompositeFilter
{
public:
	CompositeFilter();
	void addFilter(FilterBase* filter);
	bool meetsFilter(TerritorialUnit* object);
	int getSize();
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
	for (auto f : *filters_)
	{
		if (!f->meetsFilter(object))
		{
			return false;
		}
	}
	return true;
}

inline int CompositeFilter::getSize()
{
	return filters_->size();
}

inline CompositeFilter::~CompositeFilter()
{
	delete filters_;
	filters_ = nullptr;
}
