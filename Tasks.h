#pragma once

#include <string>
#include <iostream>
#include "structures/list/linked_list.h"
#include "TerritorialUnit.h"
#include "Criterion.h"
#include "AllCriteriaTU.h"
#include "FilterValue.h"
#include "structures/heap_monitor.h"

using namespace std;
using namespace structures;

class Tasks
{
public:
	void Task3(TerritorialUnit* parentTU, CompositeFilter* filters_, TypeTU type, UnsortedSequenceTable<wstring, TerritorialUnit*>* LLfoundIDK, wstring name);
    TypeTU Task3InputType();
    TerritorialUnit* Task3InputParent(CompositeFilter* filters_, TerritorialUnit* stateSlovakia, TypeTU type);
    wstring Task3AInput();
    void Task3BInput(int populationMin, int populationMax);
    void Task3CInput(double rateMin, double rateMax);

    void CoutAllCriteria(UnsortedSequenceTable<wstring, TerritorialUnit*>* LLfound);
    void CoutSortCriteria(UnsortedSequenceTable<wstring, TerritorialUnit*>* LLfound, int sortCriteriaType);
};

inline void Tasks::Task3(TerritorialUnit* parentTU, CompositeFilter* filters_, TypeTU type, UnsortedSequenceTable<wstring, TerritorialUnit*>* LLfoundIDK, wstring name)
{
    bool found = false;
    TerritorialUnit* tmp = nullptr;

    if (filters_->meetsFilter(parentTU))
    {
        LLfoundIDK->insert(parentTU->getName(), parentTU);
    }
    if (name != L"x")
    {
        tmp = nullptr;
        parentTU->getChildren()->tryFind(name, tmp);
        if (tmp != nullptr)
        {
            LLfoundIDK->insert(tmp->getName(), tmp);
            found = true;
        }
    }
    if (!found)
    {
        for (auto region : *parentTU->getChildren())
        {
            if (filters_->meetsFilter(region->accessData()))
            {
                LLfoundIDK->insert(region->getKey(), region->accessData());
            }
            if (!filters_->meetsFilter(region->accessData()) || type == All)
            {
                if (name != L"x" && region->accessData()->getChildren() != nullptr)
                {
                    tmp = nullptr;
                    region->accessData()->getChildren()->tryFind(name, tmp);
                    if (tmp != nullptr)
                    {
                        LLfoundIDK->insert(tmp->getName(), tmp);
                        break;
                    }
                }
                if (region->accessData()->getChildren() != nullptr)
                {
                    for (auto district : *region->accessData()->getChildren())
                    {
                        if (filters_->meetsFilter(district->accessData()))
                        {
                            LLfoundIDK->insert(district->getKey(), district->accessData());
                        }
                        if (!filters_->meetsFilter(district->accessData()) || type == All)
                        {
                            if (name != L"x" && district->accessData()->getChildren() != nullptr)
                            {
                                tmp = nullptr;
                                district->accessData()->getChildren()->tryFind(name, tmp);
                                if (tmp != nullptr)
                                {
                                    LLfoundIDK->insert(tmp->getName(), tmp);
                                    break;
                                }
                            }
                            if (name == L"x" && district->accessData()->getChildren() != nullptr)
                            {
                                for (auto commune : *district->accessData()->getChildren())
                                {
                                    if (filters_->meetsFilter(commune->accessData()))
                                    {
                                        LLfoundIDK->insert(commune->getKey(), commune->accessData());
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

inline TypeTU Tasks::Task3InputType()
{
    wcout << "Zadaj typ územnej jednotky - 1-obec, 2-okres, 3-kraj, 4-stat (zadaj 0 pre vynechanie): " << endl;
    int typeInt;
    TypeTU type;
    wcin >> typeInt; 
    switch (typeInt)
    {
    case 1:
        type = Commune;
        break;
    case 2:
        type = District;
        break;
    case 3:
        type = Region;
        break;
    case 4:
        type = State;
        break;
    default:
        type = All;
        break;
    }

    return type;
}

inline TerritorialUnit* Tasks::Task3InputParent(CompositeFilter* filters_, TerritorialUnit* stateSlovakia, TypeTU type)
{
    TerritorialUnit* parentTU;
    TerritorialUnit* tmpTU;

    wcout << L"Zadaj príslušnosť (zadaj x pre vynechanie): " << endl;
    wstring parent;
    getline(wcin, parent);
    getline(wcin, parent);

    if (parent == L"x")
    {
        parent = L"Slovensko";
    }

    parentTU = stateSlovakia;
    if (parent != L"Slovensko")
    {
        if (parentTU->getChildren()->tryFind(parent, tmpTU))
        {
            parentTU = tmpTU;
        }
        else
        {
            for (auto region : *parentTU->getChildren())
            {
                if ((region->accessData()->getChildren())->tryFind(parent, tmpTU))
                {
                    parentTU = tmpTU;
                    break;
                }
            }
        }
    }

    /*if (type != State)
    {
        Criterion<TerritorialUnit*>* critParent = new CriterionTUHasParent(parentTU);
        FilterValue<wstring, TerritorialUnit*> * filterParent = new FilterValue<wstring, TerritorialUnit*>(critParent, parentTU);
        filters_->addFilter(filterParent);
    }*/
    return parentTU;
}

inline wstring Tasks::Task3AInput()
{
    wcout << "Zadaj nazov (zadaj x pre vynechanie): " << endl;
    wstring name;
    getline(wcin, name);
    return name;
}

inline void Tasks::Task3BInput(int populationMin, int populationMax)
{
    wcout << "Zadaj min pocet obyvatelov (ak nechceš zadať počet, zadaj x) :" << endl;
    wstring popuationMinString;
    wcin >> popuationMinString;
    if (popuationMinString != L"x")
    {
        populationMin = stoi(popuationMinString);
    }

    wcout << "Zadaj max pocet obyvatelov (ak nechceš zadať počet, zadaj x): " << endl;
    wstring popuationMaxString;
    wcin >> popuationMaxString;
    if (popuationMinString != L"x")
    {
        populationMax = stoi(popuationMaxString);
    }
}

inline void Tasks::Task3CInput(double rateMin, double rateMax)
{
    wcout << "Zadaj min zastavanost (ak nechceš zadať počet, zadaj x) :" << endl;
    wstring rateMinString;
    wcin >> rateMinString;
    if (rateMinString != L"x")
    {
        rateMin = stod(rateMinString);
    }

    wcout << "Zadaj max zastavanost (ak nechceš zadať počet, zadaj x) : " << endl;
    wstring rateMaxString;
    wcin >> rateMaxString;
    if (rateMaxString != L"x")
    {
        rateMax = stod(rateMaxString);
    }
}

inline void Tasks::CoutAllCriteria(UnsortedSequenceTable<wstring, TerritorialUnit*>* LLfound)
{
    CriterionTUName* cName = new CriterionTUName();
    CriterionTUPreProductive* cPreProductive = new CriterionTUPreProductive();
    CriterionTUProductive* cProductive = new CriterionTUProductive();
    CriterionTUPostProductive* cPostProductive = new CriterionTUPostProductive();
    CriterionTUPopulation* cPopulation = new CriterionTUPopulation();
    CriterionTUTotalArea* cTotalArea = new CriterionTUTotalArea();
    CriterionTUBuildUpArea* cBuildUpArea = new CriterionTUBuildUpArea();
    CriterionTUBuildUpRate* cBuildUpRate = new CriterionTUBuildUpRate();

    for (auto item : *LLfound)
    {
        TerritorialUnit* temp = item->accessData()->getParent();
        while (temp != nullptr) {
            wcout << L"Rodič: " << cName->rate(temp) << ", ";
            temp = temp->getParent();
        }
        wcout << endl;

        wcout << L"Územná jednotka: " << cName->rate(item->accessData())
            << L", Preproduktívni: " << cPreProductive->rate(item->accessData())
            << L", Produktívni: " << cProductive->rate(item->accessData())
            << L", Poproduktívni: " << cPostProductive->rate(item->accessData())
            << L", Populacia: " << cPopulation->rate(item->accessData())
            << L", Rozloha: " << cTotalArea->rate(item->accessData())
            << L", Zastavane: " << cBuildUpArea->rate(item->accessData())
            << L", Zastavanosť: " << cBuildUpRate->rate(item->accessData())
            << endl;
    }

    delete cName;
    delete cPreProductive;
    delete cProductive;
    delete cPostProductive;
    delete cPopulation;
    delete cTotalArea;
    delete cBuildUpArea;
    delete cBuildUpRate;
}

inline void Tasks::CoutSortCriteria(UnsortedSequenceTable<wstring, TerritorialUnit*>* LLfound, int sortCriteriaType)
{
    CriterionTUName* cName = new CriterionTUName();
    CriterionTUPopulation* cPopulation = nullptr;
    CriterionTUBuildUpRate* cBuildUpRate = nullptr;
    if (sortCriteriaType == 2)
    {
        cPopulation = new CriterionTUPopulation();
    }
    else if (sortCriteriaType == 3) 
    {
        cBuildUpRate = new CriterionTUBuildUpRate();
    }

    for (auto item : *LLfound)
    {

        wcout << L"Územná jednotka: " << cName->rate(item->accessData());
        if (sortCriteriaType == 1)
        {
            wcout << endl;
        }

        if (sortCriteriaType == 2)
        {
            wcout << L", Populacia: " << cPopulation->rate(item->accessData()) << endl;
        }
        else if (sortCriteriaType == 3)
        {
            wcout << L", Zastavanosť: " << cBuildUpRate->rate(item->accessData()) << endl;
        }

    }

    delete cName;
    delete cPopulation;
    delete cBuildUpRate;
}
