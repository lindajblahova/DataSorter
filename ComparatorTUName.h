#pragma once

#include "Comparator.h"
#include "AllCriteriaTU.h"
#include "TerritorialUnit.h"
#include "LetterCode.h"

#include <chrono>
#include <iostream>

class ComparatorTUName : public Comparator
{
public:
    ComparatorTUName(bool compAscending);
    int compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2) override;
    ~ComparatorTUName();

private:
    CriterionTUName* crit_;
    LetterCode* lc_;

};

inline ComparatorTUName::ComparatorTUName(bool compAscending) : Comparator(compAscending), lc_(new LetterCode()), crit_(new CriterionTUName())
{
    
}

int ComparatorTUName::compareByCriterion(TerritorialUnit* tu1, TerritorialUnit* tu2)
{

    wstring name1 = crit_->rate(tu1);
    wstring name2 = crit_->rate(tu2);
    int length = 0;
    if (name1.length() <= name2.length())
    {
        length = name1.length();
    }
    else
    {
        length = name2.length();
    }
    for (int i = 0; i < length; i++)
    {
        wstring ch1 = name1.substr(i, 1);
        wstring ch2 = name2.substr(i, 1);
        if (lc_->getIntValue(ch1.c_str()) > lc_->getIntValue(ch2.c_str()))
        {
            return 1;
        } 
        else if (lc_->getIntValue(ch1.c_str()) < lc_->getIntValue(ch2.c_str()))
        {
            return -1;
        }
    }
    if (name1.length() < name2.length())
    {
        return -1;
    }
    else if (name1.length() > name2.length())
    {
        return 1;
    }
    return 0;

 /*
    if (crit_.rate(tu1) > crit_.rate(tu2))
    {
        auto t1 = Time::now();
        fsec_ += t1 - t0;
        return 1;
    }
    else if (crit_.rate(tu1) == crit_.rate(tu2))
    {
        auto t1 = Time::now();
        fsec_ += t1 - t0;
        return 0;
    }
    else
    {
        auto t1 = Time::now();
        fsec_ += t1 - t0;
        return -1;
    }*/
}

inline ComparatorTUName::~ComparatorTUName()
{
    delete lc_;
    delete crit_;
}
