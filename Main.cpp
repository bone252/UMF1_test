#include "Programs.h"
#include <locale>

void main()
{
   setlocale(LC_ALL, "");
   Programs slau;
   if (slau.Read("grid.txt"))
   {
      slau.Out();
      slau.CreateA();
      slau.SetS1("S1.txt");
      slau.OutA();
   }
   else
      cout << "Îøèáêà";
   //test Github Actions v2
   int testv2 = 1;
}