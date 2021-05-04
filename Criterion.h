#pragma once

#include "CriterionType.h"

using namespace std;

template <typename T, typename O>
class Criterion {
public:
	virtual T rate(O object) = 0;

	CriterionType getType();
	void setType(CriterionType type);

private:
	CriterionType type_;
};

template<typename T, typename O>
inline CriterionType Criterion<T, O>::getType()
{
	return type_;
}

template<typename T, typename O>
inline void Criterion<T, O>::setType(CriterionType type)
{
	type_ = type;
}
