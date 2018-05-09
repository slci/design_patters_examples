#ifndef BITMAPFACADE_HPP
#define BITMAPFACADE_HPP

#include "BitmapTest.hpp"

#include <memory>
#include <vector>

using namespace std;

namespace BitmapFacade {

static void
initGlut(int argc, char** argv)
{
   glutInit(&argc, argv);
}

class Console
{
 public:
   static Console&
   instance()
   {
      static Console* console{nullptr};
      if (!console)
      {
         console = new Console();
      }
      return *console;
   }

   void
   createWindow(int width, int height, char const* name)
   {
      glutInitWindowSize(width, height);
      windows.push_back(glutCreateWindow(name));

      glutReshapeFunc(bitmap_test::Reshape);
      glutKeyboardFunc(bitmap_test::Key);
      glutDisplayFunc(bitmap_test::Draw);
   }

   void
   run()
   {
      glutMainLoop();
   }

 private:
   vector< int > windows;

   Console()
   {
      glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
      bitmap_test::Init();
   }
};

} // namespace BitmapFacade

#endif // BITMAPFACADE_HPP
