#pragma once

#include <string>
#include "TypeTU.h"

using namespace std;

class TerritorialUnit 
{
public:
	string getName();
	TypeTU getType();
	bool hasParent();
	int getPreProductive();
	int getProductive();
	int getPostProductive();
	int getPopulation();
	double getTotalArea();
	double getBuildUpArea();

private:
	string name_;
	TypeTU type_;
	bool hasParent_;
	int preProductive_;
	int productive_;
	int postProductive_;
	int population_;
	double totalArea_;
	double buildUpArea_;

};

inline string TerritorialUnit::getName()
{
	return name_;
}
inline TypeTU TerritorialUnit::getType()
{
	return type_;
}
inline bool TerritorialUnit::hasParent()
{
	return hasParent_;
}
inline int TerritorialUnit::getPreProductive()
{
	return preProductive_;
}
inline int TerritorialUnit::getProductive()
{
	return productive_;
}
inline int TerritorialUnit::getPostProductive()
{
	return postProductive_;
}
inline int TerritorialUnit::getPopulation()
{
	return population_;
}
inline double TerritorialUnit::getTotalArea()
{
	return totalArea_;
}
inline double TerritorialUnit::getBuildUpArea()
{
	return buildUpArea_;
}