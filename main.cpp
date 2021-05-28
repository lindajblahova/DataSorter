
#include <stdlib.h>
#include "Other/App.h"

using namespace structures;
using namespace std;
int main()
{
    initHeapMonitor();

    App* app = new App();
    app->Run();
    delete app;

    return 0;
}