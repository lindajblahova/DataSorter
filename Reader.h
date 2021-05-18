#pragma once

#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"
#include "structures/list/linked_list.h"
#include "TerritorialUnit.h"
#include <string>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include "structures/heap_monitor.h"

using namespace std;
using namespace structures;
class Reader
{
public:
	static TerritorialUnit* read(wifstream& dataCommune, wifstream& dataParent);

	Reader();
	~Reader();

};

TerritorialUnit* Reader::read(wifstream& dataCommune, wifstream& dataParent)
{
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);

	TerritorialUnit* stateTU = new TerritorialUnit(L"Slovensko", State, nullptr, 0, 0, 0, 0.0, 0.0);
	TerritorialUnit* regionTU;
	TerritorialUnit* districtTU;
	TerritorialUnit* communeTU;

	if (dataCommune.is_open() && dataParent.is_open())
	{
		wstring line;
		getline(dataCommune, line);
		getline(dataParent, line);

		wstring name;
		TypeTU type;
		unsigned int preProd, prod, postProd;
		double totalArea, bulidUpArea;
		wstring commune, district, region;

		while (dataCommune.good() && dataParent.good())
		{

			std::getline(dataCommune, line, L';');
			name = line;
			std::getline(dataCommune, line, L';');
			preProd = stoi(line);
			std::getline(dataCommune, line, L';');
			prod = stoi(line);
			std::getline(dataCommune, line, L';');
			postProd = stoi(line);
			std::getline(dataCommune, line, L';');
			totalArea = stod(line);
			std::getline(dataCommune, line, L'\n');
			bulidUpArea = stod(line);

			std::getline(dataParent, line, L';');
			commune = line;
			std::getline(dataParent, line, L';');
			district = line;
			std::getline(dataParent, line, L'\n');
			region = line;

			stateTU->addValues(preProd, prod, postProd, totalArea, bulidUpArea);
			if (stateTU->getChildren()->tryFind(region, regionTU))
			{
				regionTU->addValues(preProd, prod, postProd, totalArea, bulidUpArea);
			}
			else
			{
				regionTU = new TerritorialUnit(region, Region, stateTU, preProd, prod, postProd, totalArea, bulidUpArea);
				stateTU->addChild(regionTU);
			}

			try
			{
				TerritorialUnit* districtTU = stateTU->getChildren()->operator[](region)->getChildren()->operator[](district);
				districtTU->addValues(preProd, prod, postProd, totalArea, bulidUpArea);
				
				communeTU = new TerritorialUnit(name, Commune, districtTU, preProd, prod, postProd, totalArea, bulidUpArea);
				districtTU->addChild(communeTU);
			}
			catch (logic_error)
			{
				districtTU = new TerritorialUnit(district, District, regionTU, preProd, prod, postProd, totalArea, bulidUpArea);
				regionTU->addChild(districtTU);

				communeTU = new TerritorialUnit(name, Commune, districtTU, preProd, prod, postProd, totalArea, bulidUpArea);
				districtTU->addChild(communeTU);
			}
		}
	}
	dataCommune.close();
	dataParent.close();
	
	return stateTU;

}

inline Reader::Reader()
{
}

inline Reader::~Reader()
{

}