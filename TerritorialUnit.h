#pragma once

#include <string>
#include "TypeTU.h"
#include "structures/table/sorted_sequence_table.h"

#include "structures/heap_monitor.h"

using namespace std;

class TerritorialUnit 
{
public:
	TerritorialUnit(wstring name, TypeTU type, TerritorialUnit* parent, int preProductive, int productive, int postProductive,  double totalArea, double buildUpArea);
	wstring getName();
	TypeTU getType();
	TerritorialUnit* getParent();
	int getPreProductive();
	int getProductive();
	int getPostProductive();
	double getTotalArea();
	double getBuildUpArea();

	void addChild(TerritorialUnit* tuChild);
	structures::SortedSequenceTable<wstring,TerritorialUnit*>* getChildren();

	void addValues(int preProductive, int productive, int postProductive, double totalArea, double buildUpArea);

	~TerritorialUnit();

private:
	wstring name_;
	TypeTU type_;
	TerritorialUnit* parent_;
	structures::SortedSequenceTable<wstring, TerritorialUnit*>* children_;
	int preProductive_;
	int productive_;
	int postProductive_;
	double totalArea_;
	double buildUpArea_;

};

inline TerritorialUnit::TerritorialUnit(wstring name, TypeTU type, TerritorialUnit* parent, int preProductive, int productive, int postProductive, double totalArea, double buildUpArea)
	: name_(name), type_(type), parent_(parent), preProductive_(preProductive), productive_(productive), postProductive_(postProductive),
	totalArea_(totalArea), buildUpArea_(buildUpArea)
{
	type_ == Commune ? children_ = nullptr : children_ = new structures::SortedSequenceTable<wstring, TerritorialUnit*>();
}

inline wstring TerritorialUnit::getName()
{
	return name_;
}
inline TypeTU TerritorialUnit::getType()
{
	return type_;
}
inline TerritorialUnit* TerritorialUnit::getParent()
{
	return parent_;
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
inline double TerritorialUnit::getTotalArea()
{
	return totalArea_;
}
inline double TerritorialUnit::getBuildUpArea()
{
	return buildUpArea_;
}

inline void TerritorialUnit::addChild(TerritorialUnit* tuChild)
{
	children_->insert(tuChild->getName(),tuChild);
}

inline structures::SortedSequenceTable<wstring, TerritorialUnit*>* TerritorialUnit::getChildren()
{
	return children_;
}

inline void TerritorialUnit::addValues(int preProductive, int productive, int postProductive, double totalArea, double buildUpArea)
{
	preProductive_ += preProductive;
	productive_ += productive;
	postProductive_ += postProductive;
	totalArea_ += totalArea;
	buildUpArea_ += buildUpArea;
}

inline TerritorialUnit::~TerritorialUnit()
{
	if (children_ != nullptr)
	{
		delete children_;
		children_ = nullptr;
	}
	parent_ = nullptr;

}
