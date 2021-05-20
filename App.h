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
#include "Sorter.h"
#include "Filtration.h"

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
	~App();

private:
   
    int CoutMenu();
    void InputStopApp(wchar_t* stop);

    void deleteAllTU(TerritorialUnit* stateSlovakia);
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
    TerritorialUnit* stateSlovakia = reader->read(*file, *file2);

    wchar_t run = L'y';
    while (run == L'y')
    {
        system("CLS");
        UnsortedSequenceTable<wstring, TerritorialUnit*>* newTable = new UnsortedSequenceTable<wstring, TerritorialUnit*>();
        Tasks* task = new Tasks();

        CompositeFilter* filters = new CompositeFilter();

        Criterion<wstring>* criterionName = nullptr;
        FilterTUName* filterName = nullptr;
        Criterion<int>* critPopulation = nullptr;
        FilterTUPopulation* filterPopulation = nullptr;
        Criterion<double>* critBuildUpRate = nullptr;
        FilterTUBuildUpRate* filterBuildUpRate = nullptr;

        Sorter* sorter = nullptr;
        Comparator* comparator = nullptr;

        Criterion<TypeTU>* criterionType = nullptr;
        FilterValue<TypeTU>* filterType = nullptr;

        Filtration* filtration = new Filtration();

        wstring name = L"";
        TypeTU type;
        int populationMin = -1, populationMax = -1;
        double rateMin = -1.0, rateMax = -1.0;
        int sortBy = 1, iSortOrder;
        bool bSortOrder = true;

        TerritorialUnit* parentTU = stateSlovakia;

        int iTask = CoutMenu();

        switch (iTask)
        {
        case 1:

            type = Commune;
            criterionType = new CriterionTUType();
            filterType = new FilterTUType(criterionType, type);
            filters->addFilter(filterType);
            
            switch (task->InputSubtask(iTask))
            {
            case 1:
                task->Task1AInput(filters, &criterionName, &filterName, &name);
                break;

            case 2:
                task->Task1BInput(filters, &critPopulation, &filterPopulation, &populationMin, &populationMax);
                break;

            case 3:
                task->Task1CInput(filters, &critBuildUpRate, &filterBuildUpRate, &rateMin, &rateMax);
                break;

            default:
                break;
            }

            filtration->FilterAlgorithm(parentTU, filters, type, newTable, &name);
            task->CoutAllCriteria(newTable);

            break;

        case 2:

            type = Commune;
            criterionType = new CriterionTUType();
            filterType = new FilterTUType(criterionType, type);
            filters->addFilter(filterType);

            filtration->FilterAlgorithm(parentTU, filters, type, newTable, &name);

            task->InputSortType(&bSortOrder);

            sortBy = task->InputSubtask(iTask);
            switch (sortBy)
            {
            case 1:
                comparator = new ComparatorTUName(bSortOrder);
                sorter = new Sorter(comparator);
                break;

            case 2:
                comparator = new ComparatorTUPopulation(bSortOrder);
                sorter = new Sorter(comparator);
                break;

            case 3:
                comparator = new ComparatorTUBuildUpRate(bSortOrder);
                sorter = new Sorter(comparator);
                break;

            default:
                break;
            }

            sorter->sort(newTable);
            task->CoutSortCriteria(newTable, sortBy);
            break;

        case 3:
           
            task->Task3InputType(filters, &criterionType, &filterType, &type);

            parentTU = task->Task3InputParent(filters, stateSlovakia);

            switch (task->InputSubtask(iTask))
            {
            case 1:
                task->Task3AInput(filters, &criterionName, &filterName, &name);
                break;
            case 2:

                task->Task3BInput(filters, &critPopulation, &filterPopulation, &populationMin, &populationMax);    

                break;
            case 3:
                task->Task3CInput(filters, &critBuildUpRate, &filterBuildUpRate, &rateMin, &rateMax);
 
                break;
            default:
                break;
            }

            filtration->FilterAlgorithm(parentTU, filters, type, newTable, &name);
            task->CoutAllCriteria(newTable);
            break;

        case 4:

            task->Task3InputType(filters, &criterionType, &filterType, &type);

            parentTU = task->Task3InputParent(filters, stateSlovakia);

            filtration->FilterAlgorithm(parentTU, filters, type, newTable, &name);

            task->InputSortType(&bSortOrder);
            sortBy = task->InputSubtask(iTask);
            switch (sortBy)
            {
            case 1:
                comparator = new ComparatorTUName(bSortOrder);
                sorter = new Sorter(comparator);
                break;

            case 2:
                comparator = new ComparatorTUPopulation(bSortOrder);
                sorter = new Sorter(comparator);
                break;
            
            case 3:
                comparator = new ComparatorTUBuildUpRate(bSortOrder);
                sorter = new Sorter(comparator);
                break;

            default:
                break;
            }

            sorter->sort(newTable);
            task->CoutSortCriteria(newTable, sortBy);
            break;

        default:
            break;
        }

        delete newTable;
        delete sorter;
        delete filtration;

        delete filterName;
        delete filterType;
        delete filterBuildUpRate;
        delete filterPopulation;
        delete filters;
        delete task;

        InputStopApp(&run);

    }

    deleteAllTU(stateSlovakia);
    
    delete reader;
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


inline void App::InputStopApp(wchar_t* run)
{
    wcout << L"Chcete pokračovať v behu aplikácie? (y/n)";
    wcin >> *run;
}

inline void App::deleteAllTU(TerritorialUnit* stateSlovakia)
{
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
}

inline App::~App()
{
}
