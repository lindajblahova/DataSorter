#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include "Reader.h"
#include "../Criteria/AllCriteriaTU.h"
#include "../Criteria/Criterion.h"
#include "../Filters/CompositeFilter.h"
#include "../Filters/Filter.h"
#include "Tasks.h"
#include "../Sorting/Sorter.h"
#include "../Filters/Filtration.h"
#include "../Filters/AllFilters.h"

#include "../Sorting/Comparators/Comparator.h"
#include "../Sorting/Comparators/ComparatorTUName.h"
#include "../Sorting/Comparators/ComparatorTUBuildUpRate.h"
#include "../Sorting/Comparators/ComparatorTUPopulation.h"
#include "../structures/heap_monitor.h"
#include "../structures/table/sorting/heap_sort.h"
#include "../structures/table/unsorted_sequence_table.h"

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

        Sorter<wstring>* sorterName = nullptr;
        Sorter<int>* sorterPopulation = nullptr;
        Sorter<double>* sorterBuildUpRate = nullptr;
        Comparator<wstring>* comparatorName = nullptr;
        Comparator<int>* comparatorPopulation = nullptr;
        Comparator<double>* comparatorBuildUpRate = nullptr;

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
                task->InputName(filters, &criterionName, &filterName, &name, iTask);
                break;

            case 2:
                task->InputPopulation(filters, &critPopulation, &filterPopulation, &populationMin, &populationMax, iTask);
                break;

            case 3:
                task->InputBuildUpRate(filters, &critBuildUpRate, &filterBuildUpRate, &rateMin, &rateMax, iTask);
                break;

            default:
                break;
            }

            filtration->TableFiltration(parentTU, filters, type, newTable, &name);
            task->CoutAllCriteria(newTable);

            break;

        case 2:

            type = Commune;
            criterionType = new CriterionTUType();
            filterType = new FilterTUType(criterionType, type);
            filters->addFilter(filterType);

            filtration->TableFiltration(parentTU, filters, type, newTable, &name);

            task->InputSortType(&bSortOrder);

            sortBy = task->InputSubtask(iTask);
            switch (sortBy)
            {
            case 1:
                comparatorName = new ComparatorTUName(bSortOrder);
                sorterName = new Sorter<wstring>(comparatorName);
                sorterName->sort(newTable);
                break;

            case 2:
                comparatorPopulation = new ComparatorTUPopulation(bSortOrder);
                sorterPopulation = new Sorter<int>(comparatorPopulation);
                sorterPopulation->sort(newTable);
                break;

            case 3:
                comparatorBuildUpRate = new ComparatorTUBuildUpRate(bSortOrder);
                sorterBuildUpRate = new Sorter<double>(comparatorBuildUpRate);
                sorterBuildUpRate->sort(newTable);
                break;

            default:
                break;
            }

           
            task->CoutSortCriteria(newTable, sortBy);
            break;

        case 3:
           
            task->InputType(filters, &criterionType, &filterType, &type);

            parentTU = task->InputParent(filters, stateSlovakia);

            switch (task->InputSubtask(iTask))
            {
            case 1:
                task->InputName(filters, &criterionName, &filterName, &name, iTask);
                break;
            case 2:

                task->InputPopulation(filters, &critPopulation, &filterPopulation, &populationMin, &populationMax, iTask);

                break;
            case 3:
                task->InputBuildUpRate(filters, &critBuildUpRate, &filterBuildUpRate, &rateMin, &rateMax, iTask);
 
                break;
            default:
                break;
            }

            filtration->TableFiltration(parentTU, filters, type, newTable, &name);
            task->CoutAllCriteria(newTable);
            break;

        case 4:

            task->InputType(filters, &criterionType, &filterType, &type);

            parentTU = task->InputParent(filters, stateSlovakia);

            filtration->TableFiltration(parentTU, filters, type, newTable, &name);

            task->InputSortType(&bSortOrder);
            sortBy = task->InputSubtask(iTask);
            switch (sortBy)
            {
            case 1:
                comparatorName = new ComparatorTUName(bSortOrder);
                sorterName = new Sorter<wstring>(comparatorName);
                sorterName->sort(newTable);
                break;

            case 2:
                comparatorPopulation = new ComparatorTUPopulation(bSortOrder);
                sorterPopulation = new Sorter<int>(comparatorPopulation);
                sorterPopulation->sort(newTable);
                break;
            
            case 3:
                comparatorBuildUpRate = new ComparatorTUBuildUpRate(bSortOrder);
                sorterBuildUpRate = new Sorter<double>(comparatorBuildUpRate);
                sorterBuildUpRate->sort(newTable);
                break;

            default:
                break;
            }

            task->CoutSortCriteria(newTable, sortBy);
            break;

        default:
            break;
        }

        delete newTable;
        delete sorterName;
        delete sorterPopulation;
        delete sorterBuildUpRate;

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
    wcout << L"Chcete pokračovať v behu aplikácie? (y/n): ";
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
