#include "BitmapFacade.hpp"

#include <iostream>
using namespace std;

int
main(int argc, char** argv)
{
   BitmapFacade::initGlut(argc, argv);
   auto& c = BitmapFacade::Console::instance();

   c.createWindow(300, 300, "Bitmap Test1");
   c.createWindow(200, 400, "Bitmap Test2");

   c.run();
}
