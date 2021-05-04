#pragma once

#include "Criterion.h"
#include "TerritorialUnit.h"

template <typename T>
class CriterionTU : public Criterion<T, TerritorialUnit>
{
public:
	virtual T rate(TerritorialUnit* tu) = 0;
}; 