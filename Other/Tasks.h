#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include "../structures/list/linked_list.h"
#include "../TerritorialUnit/TerritorialUnit.h"
#include "../Criteria/Criterion.h"
#include "../Criteria/Criterion.h"
#include "../Filters/AllFilters.h"
#include "../Filters/FilterTable.h"
#include "../structures/heap_monitor.h"

using namespace std;
using namespace structures;

class Tasks
{
public:

    void InputSortType(bool* bSortOrder);

    int InputSubtask(int iTask);

    void InputName(CompositeFilter* filters_, Criterion<wstring>** criterionName, FilterTUName** filterName, wstring* name, int task);
    void InputPopulation(CompositeFilter* filters_, Criterion<int>** critPopulation, FilterTUPopulation** filterPopulation, int* populationMin, int* populationMax, int task);
    void InputBuildUpRate(CompositeFilter* filters_, Criterion<double>** critBuildUpRate, FilterTUBuildUpRate** filterBuildUpRate, double* rateMin, double* rateMax, int task);

    void InputType(CompositeFilter* filters_, Criterion<TypeTU>** criterionType, FilterValue<TypeTU>** filterType, TypeTU* type);
    TerritorialUnit* InputParent(CompositeFilter* filters_, TerritorialUnit* stateSlovakia);

    void CoutAllCriteria(UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable);
    void CoutSortCriteria(UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable, int sortCriteriaType);

private:
    inline void changeColor(int desiredColor);

    void createNameFilter(CompositeFilter* filters_, Criterion<wstring>** criterionName, FilterTUName** filterName, wstring* name);
    void createTypeFilter(CompositeFilter* filters_, Criterion<TypeTU>** criterionType, FilterValue<TypeTU>** filterType, TypeTU* type);
    void createPopulationFilter(CompositeFilter* filters_, Criterion<int>** critPopulation, FilterTUPopulation** filterPopulation, int* populationMin, int* populationMax);
    void createBuildUpRateFilter(CompositeFilter* filters_, Criterion<double>** critBuildUpRate, FilterTUBuildUpRate** filterBuildUpRate, double* rateMin, double* rateMax);
  
};

inline void Tasks::InputSortType(bool* bSortOrder)
{
    int iSortOrder;
    wcout << L"Zvoľte typ triedenia: " << endl;
    wcout << L"0 - Triedenie vzostupne" << endl;
    wcout << L"1 - Triedenie zostupne" << endl;
    wcin >> iSortOrder;

    iSortOrder == 0 ? *bSortOrder = true : *bSortOrder = false;
}

inline void Tasks::InputType(CompositeFilter* filters_, Criterion<TypeTU>** criterionType, FilterValue<TypeTU>** filterType, TypeTU* type)
{
    wcout << L"Zadaj typ územnej jednotky - 1-obec, 2-okres, 3-kraj, 4-stat (zadaj x pre vynechanie): " << endl;
    int iType;
    wstring chType;
    wcin >> chType;
    chType != L"x" ? iType = stoi(chType) : iType = 0;
    switch (iType)
    {
    case 1:
        *type = Commune;
        break;
    case 2:
        *type = District;
        break;
    case 3:
        *type = Region;
        break;
    case 4:
        *type = State;
        break;
    default:
        *type = All;
    }

    createTypeFilter(filters_, criterionType, filterType, type);
}

inline TerritorialUnit* Tasks::InputParent(CompositeFilter* filters_, TerritorialUnit* stateSlovakia)
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

inline int Tasks::InputSubtask(int iTask)
{
    if (iTask == 1)
    {
        wcout << L"Zvoľte kritérium pre filtrovanie obcí (1,2,3): " << endl;
    }
    else if (iTask == 3)
    {
        wcout << L"Zvoľte kritérium pre filtrovanie územných jednotiek (1,2,3): " << endl;
    }

    switch (iTask)
    {
    case 1: case 3:
        wcout << L"1 - 1A - Filtrovanie podľa Názvu" << endl;
        wcout << L"2 - 1B - Filtrovanie podľa Počtu obyvateľov" << endl;
        wcout << L"3 - 1C - Filtrovanie podľa Zastavanosti" << endl;
        break;
    case 2: 
        wcout << L"Zvoľte triediace kritérium: " << endl;
        wcout << L"1 - 2A - Triedenie obcí podla Názvu" << endl;
        wcout << L"2 - 2B - Triedenie obcí podla Počtu obyvateľov" << endl;
        wcout << L"3 - 2C - Triedenie obcí podla Zastavanosti" << endl;
        break;
    case 4:
        wcout << L"Zvoľte triediace kritérium: " << endl;
        wcout << L"1 - 2A - Triedenie územných jednotiek podla Názvu" << endl;
        wcout << L"2 - 2B - Triedenie územných jednotiek podla Počtu obyvateľov" << endl;
        wcout << L"3 - 2C - Triedenie územných jednotiek podla Zastavanosti" << endl;
        break;
    default:
        break;
    }
   
    int taskSubType;
    wcin >> taskSubType;
    return taskSubType;
}

inline void Tasks::InputName(CompositeFilter* filters_, Criterion<wstring>** criterionName, FilterTUName** filterName, wstring* name, int task)
{
    if (task == 1)
    {
        wcout << L"Zadajte názov: " << endl;
    }
    else
    {
        wcout << L"Zadajte názov (zadajte x pre vynechanie): " << endl;
    }
  
    getline(wcin, *name);
    getline(wcin, *name);
    createNameFilter(filters_, criterionName, filterName, name);
}

inline void Tasks::InputPopulation(CompositeFilter* filters_, Criterion<int>** critPopulation, FilterTUPopulation** filterPopulation, int* populationMin, int* populationMax, int task)
{
   task == 1 ? wcout << L"Zadajte minimálny počet obyvateľov:" << endl : wcout << L"Zadajte minimálny počet obyvateľov (zadajte x pre vynechanie) :" << endl;

   wstring popuationMinString;
   wcin >> popuationMinString;
   if (popuationMinString != L"x")
   {
       *populationMin = stoi(popuationMinString);
   }

   task == 1 ? wcout << L"Zadajte maximálny počet obyvateľov: " << endl : wcout << L"Zadajte maximálny počet obyvateľov (zadajte x pre vynechanie): " << endl;
    wstring popuationMaxString;
    wcin >> popuationMaxString;
    if (popuationMinString != L"x")
    {
        *populationMax = stoi(popuationMaxString);
    }
    createPopulationFilter(filters_, critPopulation, filterPopulation, populationMin, populationMax);
}

inline void Tasks::InputBuildUpRate(CompositeFilter* filters_, Criterion<double>** critBuildUpRate, FilterTUBuildUpRate** filterBuildUpRate, double* rateMin, double* rateMax, int task)
{
    task == 1 ? wcout << L"Zadajte minimálnu zastavanosť:" << endl : wcout << L"Zadajte minimálnu zastavanosť (zadajte x pre vynechanie) :" << endl;

    wstring rateMinString;
    wcin >> rateMinString;
    if (rateMinString != L"x")
    {
        *rateMin = stod(rateMinString);
    }

    task == 1 ? wcout << L"Zadajte maximálnu zastavanosť:" << endl : wcout << L"Zadajte maximálnu zastavanosť (zadajte x pre vynechanie) : " << endl;
    wstring rateMaxString;
    wcin >> rateMaxString;
    if (rateMaxString != L"x")
    {
        *rateMax = stod(rateMaxString);
    }
    createBuildUpRateFilter(filters_, critBuildUpRate, filterBuildUpRate, rateMin, rateMax);
}

inline void Tasks::createNameFilter(CompositeFilter* filters_, Criterion<wstring>** criterionName, FilterTUName** filterName, wstring* name)
{
    if (*name != L"x")
    {
        *criterionName = new CriterionTUName();
        *filterName = new FilterTUName(*criterionName, *name);
        filters_->addFilter(*filterName);
    }
    else
    {
        *name = L"";
    }
}

inline void Tasks::createTypeFilter(CompositeFilter* filters_, Criterion<TypeTU>** criterionType, FilterValue<TypeTU>** filterType, TypeTU* type)
{
    if (*type != All)
    {
        *criterionType = new CriterionTUType();
        *filterType = new FilterTUType(*criterionType, *type);
        filters_->addFilter(*filterType);
    }
}

inline void Tasks::createPopulationFilter(CompositeFilter* filters_, Criterion<int>** critPopulation, FilterTUPopulation** filterPopulation, int* populationMin, int* populationMax)
{
    if (*populationMin != -1 && *populationMax != -1 && *populationMin <= *populationMax)
    {
        *critPopulation = new CriterionTUPopulation();
        *filterPopulation = new FilterTUPopulation(*critPopulation, *populationMin, *populationMax);
        filters_->addFilter(*filterPopulation);
    }
}

inline void Tasks::createBuildUpRateFilter(CompositeFilter* filters_, Criterion<double>** critBuildUpRate, FilterTUBuildUpRate** filterBuildUpRate, double* rateMin, double* rateMax)
{
    if (*rateMin != -1.0 && *rateMax != -1.0 && *rateMin <= *rateMax)
    {
        *critBuildUpRate = new CriterionTUBuildUpRate();
        *filterBuildUpRate = new FilterTUBuildUpRate(*critBuildUpRate, *rateMin, *rateMax);
        filters_->addFilter(*filterBuildUpRate);
    }
}

inline void Tasks::CoutAllCriteria(UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable)
{
    CriterionTUName* cName = new CriterionTUName();
    CriterionTUPreProductive* cPreProductive = new CriterionTUPreProductive();
    CriterionTUProductive* cProductive = new CriterionTUProductive();
    CriterionTUPostProductive* cPostProductive = new CriterionTUPostProductive();
    CriterionTUPopulation* cPopulation = new CriterionTUPopulation();
    CriterionTUTotalArea* cTotalArea = new CriterionTUTotalArea();
    CriterionTUBuildUpArea* cBuildUpArea = new CriterionTUBuildUpArea();
    CriterionTUBuildUpRate* cBuildUpRate = new CriterionTUBuildUpRate();

    for (auto item : *newTable)
    {
        changeColor(11);
        wcout << endl << L" | Rodičia: ";
        TerritorialUnit* temp = item->accessData()->getParent();
        while (temp != nullptr) {
            wcout << cName->rate(temp);
            temp = temp->getParent();
            if (temp != nullptr)
            {
                wcout << " + ";
            }
        }
        wcout << " |" << endl;

        changeColor(14);
        wcout << L" | Územná jednotka: " << cName->rate(item->accessData());
        changeColor(6);
        wcout << L" | Preproduktívni: " << cPreProductive->rate(item->accessData());
        changeColor(4);
        wcout << L" | Produktívni: " << cProductive->rate(item->accessData());
        changeColor(2);
        wcout << L" | Poproduktívni: " << cPostProductive->rate(item->accessData());
        changeColor(3);
        wcout << L" | Populácia: " << cPopulation->rate(item->accessData());
        changeColor(8);
        wprintf(L" | Rozloha: %.2f km²", (cTotalArea->rate(item->accessData()) / 1000.0));
        changeColor(15);
       wprintf(L" | Zastavané: %.2f km²", (cBuildUpArea->rate(item->accessData())/1000.0));
       changeColor(10);
       wprintf(L" | Zastavanosť: %.2f", cBuildUpRate->rate(item->accessData()));
       wcout << " % |" << endl ;
    }
    changeColor(7);
    delete cName;
    delete cPreProductive;
    delete cProductive;
    delete cPostProductive;
    delete cPopulation;
    delete cTotalArea;
    delete cBuildUpArea;
    delete cBuildUpRate;
}


inline void Tasks::CoutSortCriteria(UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable, int sortCriteriaType)
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

    for (auto item : *newTable)
    {
        changeColor(14);
        wcout << L" | Územná jednotka: " << cName->rate(item->accessData());
        if (sortCriteriaType == 1)
        {
            wcout << endl;
        }

        if (sortCriteriaType == 2)
        {
            changeColor(3);
            wcout << L" | Populacia: " << cPopulation->rate(item->accessData()) << " |"  << endl;
        }
        else if (sortCriteriaType == 3)
        {
            changeColor(10);
            wprintf(L" | Zastavanosť: %.2f", cBuildUpRate->rate(item->accessData()));
            wcout << " % |" << endl;
        }

    }

    delete cName;
    delete cPopulation;
    delete cBuildUpRate;
    changeColor(7);
}

inline void Tasks::changeColor(int desiredColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}
