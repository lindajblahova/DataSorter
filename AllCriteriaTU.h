#pragma once

#include <string>
#include "Criterion.h"
#include "structures/heap_monitor.h"

class CriterionTUName : public Criterion<wstring> {
public:
	wstring rate(TerritorialUnit* tu) override;
};
inline wstring CriterionTUName::rate(TerritorialUnit* tu)
{
	return tu->getName();
}

class CriterionTUType : public Criterion<TypeTU> {
public:
	TypeTU rate(TerritorialUnit* tu) override;
};
inline TypeTU CriterionTUType::rate(TerritorialUnit* tu)
{
	return tu->getType();
}
/*
class CriterionTUHasParent : public Criterion<TerritorialUnit*> {
public:
	CriterionTUHasParent(TerritorialUnit* parent);
	TerritorialUnit* rate(TerritorialUnit* tu) override;
	~CriterionTUHasParent();
private:
	TerritorialUnit* parent_;
};
inline TerritorialUnit* CriterionTUHasParent::rate(TerritorialUnit* tu)
{
	if (tu->getType() == State)
	{
		return tu;
	}
	TerritorialUnit* temp = tu->getParent();
	while (temp != nullptr) {
		if (temp == parent_)
		{
			return temp;
		}
		temp = temp->getParent();
	}
	return temp;
}
inline CriterionTUHasParent::~CriterionTUHasParent()
{
	delete parent_;
	parent_ = nullptr;
}
inline CriterionTUHasParent::CriterionTUHasParent(TerritorialUnit* parent) : parent_(parent)
{
}
*/

class CriterionTUPreProductive : public Criterion<int> {
public:
	int rate(TerritorialUnit* tu) override;
};
inline int CriterionTUPreProductive::rate(TerritorialUnit* tu)
{
	return tu->getPreProductive();
}

class CriterionTUProductive : public Criterion<int> {
public:
	int rate(TerritorialUnit* tu) override;
};
inline int CriterionTUProductive::rate(TerritorialUnit* tu)
{
	return tu->getProductive();
}

class CriterionTUPostProductive : public Criterion<int> {
public:
	int rate(TerritorialUnit* tu) override;
};
inline int CriterionTUPostProductive::rate(TerritorialUnit* tu)
{
	return tu->getPostProductive();
}

class CriterionTUPopulation : public Criterion<int> {
public:
	int rate(TerritorialUnit* tu) override;
};
inline int CriterionTUPopulation::rate(TerritorialUnit* tu)
{
	return tu->getPreProductive()+ tu->getProductive()+ tu->getPostProductive();
}

class CriterionTUTotalArea : public Criterion<double> {
public:
	double rate(TerritorialUnit* tu) override;
};
inline double CriterionTUTotalArea::rate(TerritorialUnit* tu)
{
	return tu->getTotalArea();
}

class CriterionTUBuildUpArea : public Criterion<double> {
public:
	double rate(TerritorialUnit* tu) override;
};
inline double CriterionTUBuildUpArea::rate(TerritorialUnit* tu)
{
	return tu->getBuildUpArea();
}

class CriterionTUBuildUpRate : public Criterion<double> {
public:
	double rate(TerritorialUnit* tu) override;
};
inline double CriterionTUBuildUpRate::rate(TerritorialUnit* tu)
{
	double buildUp = tu->getBuildUpArea();
	buildUp += 0.0;
	double total = tu->getTotalArea();
	total += 0.0;
	return 100.0*(double)(tu->getBuildUpArea() /tu->getTotalArea());
}