#pragma once

#include "CriterionTU.h"
#include <string>

class CriterionTUName : public CriterionTU<string> {
public:
	string rate(TerritorialUnit* tu) override;
};
inline string CriterionTUName::rate(TerritorialUnit* tu)
{
	return tu->getName();
}

class CriterionTUType : public CriterionTU<TypeTU> {
public:
	TypeTU rate(TerritorialUnit* tu) override;
};
inline TypeTU CriterionTUType::rate(TerritorialUnit* tu)
{
	return tu->getType();
}

class CriterionTUHasParent : public CriterionTU<bool> {
public:
	bool rate(TerritorialUnit* tu) override;
};
inline bool CriterionTUHasParent::rate(TerritorialUnit* tu)
{
	return tu->hasParent();
}


class CriterionTUPreProductive : public CriterionTU<int> {
public:
	int rate(TerritorialUnit* tu) override;
};
inline int CriterionTUPreProductive::rate(TerritorialUnit* tu)
{
	return tu->getPreProductive();
}

class CriterionTUProductive : public CriterionTU<int> {
public:
	int rate(TerritorialUnit* tu) override;
};
inline int CriterionTUProductive::rate(TerritorialUnit* tu)
{
	return tu->getProductive();
}

class CriterionTUPostProductive : public CriterionTU<int> {
public:
	int rate(TerritorialUnit* tu) override;
};
inline int CriterionTUPostProductive::rate(TerritorialUnit* tu)
{
	return tu->getPostProductive();
}

class CriterionTUPopulation : public CriterionTU<int> {
public:
	int rate(TerritorialUnit* tu) override;
};
inline int CriterionTUPopulation::rate(TerritorialUnit* tu)
{
	return tu->getPopulation();
}

class CriterionTUTotalArea : public CriterionTU<double> {
public:
	double rate(TerritorialUnit* tu) override;
};
inline double CriterionTUTotalArea::rate(TerritorialUnit* tu)
{
	return tu->getTotalArea();
}

class CriterionTUBuildUpArea : public CriterionTU<double> {
public:
	double rate(TerritorialUnit* tu) override;
};
inline double CriterionTUBuildUpArea::rate(TerritorialUnit* tu)
{
	return tu->getBuildUpArea();
}

class CriterionTUBuildUpRate : public CriterionTU<double> {
public:
	double rate(TerritorialUnit* tu) override;
};
inline double CriterionTUBuildUpRate::rate(TerritorialUnit* tu)
{
	return 100*(tu->getBuildUpArea()/ tu->getTotalArea());
}