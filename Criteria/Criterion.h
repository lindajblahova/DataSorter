#pragma once

#include "../TerritorialUnit/TerritorialUnit.h"
#include "../structures/heap_monitor.h"

using namespace std;

template <typename T>
class Criterion {
public:
	virtual T rate(TerritorialUnit* object) = 0;
};

