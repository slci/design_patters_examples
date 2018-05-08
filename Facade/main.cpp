#include "BitmapTest.hpp"

int
main(int argc, char** argv)
{
   // This code needs Facade!
   GLenum type;

   glutInit(&argc, argv);
   bitmap_test::Args(argc, argv);

   type = (bitmap_test::rgb) ? GLUT_RGB : GLUT_INDEX;
   type |= (bitmap_test::doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
   glutInitDisplayMode(type);
   glutInitWindowSize(300, 300);
   glutCreateWindow("Bitmap Test");

   bitmap_test::Init();

   glutReshapeFunc(bitmap_test::Reshape);
   glutKeyboardFunc(bitmap_test::Key);
   glutDisplayFunc(bitmap_test::Draw);


   glutMainLoop();
}
