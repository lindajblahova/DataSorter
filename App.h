#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include "Reader.h"
#include "AllCriteriaTU.h"
#include "Criterion.h"
#include "CompositeFilter.h"
#include "FilterValue.h"
#include "FilterInterval.h"
#include "FilterTable.h"
#include "AllFilters.h"
#include "Tasks.h"

#include "ComparatorTUName.h"
#include "ComparatorTUPopulation.h"
#include "ComparatorTUBuildUpRate.h"
#include "structures/heap_monitor.h"
#include "structures/table/sorting/heap_sort.h"

class App
{
public:
	App();
	void Run();
	int CoutMenu();
	~App();

};

App::App()
{
}

inline void App::Run()
{
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);

    std::wifstream* file = new wifstream(L"data/1 Obce SR.csv");
    std::wifstream* file2 = new wifstream(L"data/2 Územné členenie SR.csv");

    file->imbue(locale("sk_SK.UTF8"));
    file2->imbue(locale("sk_SK.UTF8"));

    Reader* reader = new Reader();

    UnsortedSequenceTable<wstring, TerritorialUnit*>* LLfound = new UnsortedSequenceTable<wstring, TerritorialUnit*>();

    TerritorialUnit* stateSlovakia = reader->read(*file, *file2);

    Tasks* task = new Tasks();

    CompositeFilter* filters_ = new CompositeFilter();

    Criterion<wstring>* criterionName = nullptr;
    FilterTUName* filterName = nullptr;
    Criterion<int>* critPopulation = nullptr;
    FilterTUPopulation* filterPopulation = nullptr;
    Criterion<double>* critBuildUpRate = nullptr;
    FilterTUBuildUpRate* filterBuildUpRate = nullptr;

    HeapSort<wstring, TerritorialUnit*>* sorter_ = new HeapSort<wstring, TerritorialUnit*>();

    Criterion<TypeTU>* criterionType = nullptr;
    FilterValue<TypeTU>* filterType = nullptr;

    wstring name = L"x";
    TypeTU type;
    int populationMin = -1, populationMax = -1;
    double rateMin = -1.0, rateMax = -1.0;
    TerritorialUnit* parentTU = stateSlovakia;
    int sortBy, iSortOrder;
    bool bSortOrder = true;

    int iTask = CoutMenu();

    if (iTask == 2 || iTask == 4)
    {
        wcout << "Zvolte typ triedenia: " << endl;
        wcout << "0 - Triedenie vzostupne" << endl;
        wcout << "1 - Triedenie zostupne" << endl;
        wcin >> iSortOrder;

        iSortOrder == 0 ? bSortOrder = true : bSortOrder = false;
       
    }
    ComparatorTUName compName(bSortOrder);
    ComparatorTUPopulation compPopulation(bSortOrder);
    ComparatorTUBuildUpRate compBulidUpRate(bSortOrder);

	switch (iTask)
	{
	case 1:

        type = Commune;
        criterionType = new CriterionTUType();
        filterType = new FilterTUType(criterionType, type);
        filters_->addFilter(filterType);

        wcout << "Zvolte kritérium pre filtrovanie obcí (1,2,3): " << endl;
        wcout << "1 - 1A - Filtrovanie podla Nazvu" << endl;
        wcout << "2 - 1B - Filtrovanie podla Počtu obyvateľov" << endl;
        wcout << "3 - 1C - Filtrovanie podla Zastavanosti" << endl;
        int taskSubType1;
        wcin >> taskSubType1;

        switch (taskSubType1)
        {
        case 1:
            wcout << "Zadaj nazov (zadaj x pre vynechanie): " << endl;
            getline(wcin, name);
            getline(wcin, name);
            if (name != L"x")
            {
                criterionName = new CriterionTUName();
                filterName = new FilterTUName(criterionName, name);
                filters_->addFilter(filterName);
            }
            break;
        case 2:

            wcout << "Zadaj min pocet obyvatelov:" << endl;
            wcin >> populationMin;
            wcout << "Zadaj max pocet obyvatelov:" << endl;
            wcin >> populationMax;
            if (populationMin != -1 && populationMax != -1 && populationMin <= populationMax)
            {
                critPopulation = new CriterionTUPopulation();
                filterPopulation = new FilterTUPopulation(critPopulation, populationMin, populationMax);
                filters_->addFilter(filterPopulation);
            }
            break;
        case 3:
            wcout << "Zadaj min zastavanosť:" << endl;
            wcin >> rateMin;
            wcout << "Zadaj max zastavanosť:" << endl;
            wcin >> rateMax;
            if (rateMin != -1.0 && rateMax != -1.0 && rateMin <= rateMax)
            {
                critBuildUpRate = new CriterionTUBuildUpRate();
                filterBuildUpRate = new FilterTUBuildUpRate(critBuildUpRate, rateMin, rateMax);
                filters_->addFilter(filterBuildUpRate);
            }
            break;
        default:
            break;
        }

        task->Task3(parentTU, filters_, type, LLfound, name);
        task->CoutAllCriteria(LLfound);

		break;

	case 2:

        type = Commune;
        criterionType = new CriterionTUType();
        filterType = new FilterTUType(criterionType, type);
        filters_->addFilter(filterType);

        wcout << "Zvolte triediace kriterium: " << endl;
        wcout << "1 - 2A - Triedenie obcí podla Nazvu" << endl;
        wcout << "2 - 2B - Triedenie obcí podla Počtu obyvateľov" << endl;
        wcout << "3 - 2C - Triedenie obcí podla Zastavanosti" << endl;
        wcin >> sortBy;

        task->Task3(parentTU, filters_, type, LLfound, name);

        switch (sortBy)
        {
        case 1:
            sorter_->sort(*LLfound, compName);
            break;
        case 2:
            sorter_->sort(*LLfound, compPopulation);
            break;
        case 3:
            sorter_->sort(*LLfound, compBulidUpRate);
            break;
        default:
            break;
        }

        task->CoutSortCriteria(LLfound, sortBy);
		break;

	case 3:
        wcout << "Zvolte doplnujuci filter (1,2,3): " << endl;
        wcout << "1 - 3A - Filtrovanie podla Nazvu" << endl;
        wcout << "2 - 3B - Filtrovanie podla Počtu obyvateľov" << endl;
        wcout << "3 - 3C - Filtrovanie podla Zastavanosti" << endl;
        int taskSubType3;
        wcin >> taskSubType3;

        type = task->Task3InputType();
      
        criterionType = new CriterionTUType();
        filterType = new FilterTUType(criterionType, type);
        filters_->addFilter(filterType);

        parentTU = task->Task3InputParent(filters_, stateSlovakia, type);

        switch (taskSubType3)
        {
        case 1:
            name = task->Task3AInput();
            if (name != L"x")
            {
                criterionName = new CriterionTUName();
                filterName = new FilterTUName(criterionName, name);
                filters_->addFilter(filterName);
            }
            break;
        case 2:

            task->Task3BInput(populationMin, populationMax);
            if (populationMin != -1 && populationMax != -1 && populationMin <= populationMax)
            {
                critPopulation = new CriterionTUPopulation();
                filterPopulation = new FilterTUPopulation(critPopulation, populationMin, populationMax);
                filters_->addFilter(filterPopulation);
            }
            break;
        case 3:
            task->Task3CInput(rateMin, rateMax);
            if (rateMin != -1.0 && rateMax != -1.0 && rateMin <= rateMax)
            {
                critBuildUpRate = new CriterionTUBuildUpRate();
                filterBuildUpRate = new FilterTUBuildUpRate(critBuildUpRate, rateMin, rateMax);
                filters_->addFilter(filterBuildUpRate);
            }
            break;
        default:
            break;
        }

        task->Task3(parentTU, filters_, type, LLfound, name);
        task->CoutAllCriteria(LLfound);

		break;
	case 4:

        type = task->Task3InputType();
        
        criterionType = new CriterionTUType();
        filterType = new FilterTUType(criterionType, type);
        filters_->addFilter(filterType);

        parentTU = task->Task3InputParent(filters_, stateSlovakia, type);

        wcout << "Zvolte triediace kriterium: " << endl;
        wcout << "1 - 4A - Triedenie podla Nazvu" << endl;
        wcout << "2 - 4B - Triedenie podla Počtu obyvateľov" << endl;
        wcout << "3 - 4C - Triedenie podla Zastavanosti" << endl;
        wcin >> sortBy;

        task->Task3(parentTU, filters_, type, LLfound, name);

        switch (sortBy)
        {
        case 1:
            sorter_->sort(*LLfound, compName);
            break;
        case 2:
            sorter_->sort(*LLfound, compPopulation);
            break;
        case 3:
            sorter_->sort(*LLfound, compBulidUpRate);
            break;
        default:
            break;
        }

        task->CoutSortCriteria(LLfound, sortBy);
		break;

	default:
		break;
	}

    delete LLfound;
    delete sorter_;

    for (auto region : *stateSlovakia->getChildren())
    {
        for (auto district : *region->accessData()->getChildren())
        {
            for (auto commune : *district->accessData()->getChildren())
            {
                delete commune->accessData();
            }
            delete district->accessData();
        }
        delete region->accessData();
    }
    delete stateSlovakia;

    delete filterName;
    delete filterType;
    delete filterBuildUpRate;
    delete filterPopulation;
    delete filters_;
    delete reader;
    delete task;
    delete file;
    delete file2;
}

inline int App::CoutMenu()
{
	int task;
	wcout << L"Zadajte číslo úlohy, ktorú chcete vybrať:" << endl;
	wcout << L"1 - Vypísanie informácií o obciach" << endl; 
	wcout << L"2 - Zoradenie obcí" << endl; 
	wcout << L"3 - Vypísanie informácií o územných jednotkách" << endl; 
	wcout << L"4 - Zoradenie územných jednotiek" << endl;

	wcin >> task;
	return task;
}

inline App::~App()
{
}
