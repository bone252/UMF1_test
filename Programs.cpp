#include "Programs.h"

bool Programs::Read(string readFile)
{
   ifstream fout(readFile);
   if (!fout.is_open())
      return false;
   fout >> count_of_nodes_x >> count_of_nodes_y;
   fout >> count_fictitious_of_nodes_x >> count_fictitious_of_nodes_y;
   //grid.resize(count_of_nodes_x * count_of_nodes_y);
   //double x_position, y_position;
   vector<double> x_position(count_of_nodes_x), y_position(count_of_nodes_y);
   for (int i = 0; i < count_of_nodes_x; i++)
      fout >> x_position[i];
   for (int i = 0; i < count_of_nodes_y; i++)
      fout >> y_position[i];
   grid.resize(count_of_nodes_y);
   for (int i = 0; i < count_of_nodes_y; i++)
   {
      grid[i].resize(count_of_nodes_x);
      for (int j = 0; j < count_of_nodes_x; j++)
      {
         if (j < count_of_nodes_x - count_fictitious_of_nodes_x && i >= count_fictitious_of_nodes_y) // если узел не фиктивный
            grid[i][j] = node(x_position[j], y_position[i], true);
         else // если узел фиктивный
            grid[i][j] = node(x_position[j], y_position[i], false);
      }
   } 
   fout >> lambda >> gamma;
   f.resize(count_of_nodes_x * count_of_nodes_y);
   for (int i = 0; i < f.size(); i++)
      fout >> f[i];
   fout.close();
   return true;
}

void Programs::Out()
{
   for (int i = 0; i < count_of_nodes_y; i++)
   {
      for (int j = 0; j < count_of_nodes_x; j++)
         cout << grid[i][j].x_position << " " << grid[i][j].y_position << "\t";
      cout << "\n";
   }     
}

void Programs::OutA()
{
   for (int i = 0; i < A.size(); i++)
   {
      cout << i << "\t\t";
      for (int j = 0; j < 5; j++)
         cout << A[i][j] << "\t";
      cout << "\n";
   }
}

void Programs::CreateA()
{
   A.resize(count_of_nodes_x * count_of_nodes_y);
   for (int i = 0; i < A.size(); i++)
      A[i].resize(5);
   b.resize(count_of_nodes_x * count_of_nodes_y);
   for (int i = 0; i < count_fictitious_of_nodes_x; i++)
   {
      A[count_of_nodes_x - count_fictitious_of_nodes_x + i][0] = 0;
      A[count_of_nodes_x - count_fictitious_of_nodes_x + i][1] = 0;
      A[count_of_nodes_x - count_fictitious_of_nodes_x + i][2] = 1;
      A[count_of_nodes_x - count_fictitious_of_nodes_x + i][3] = 0;
      A[count_of_nodes_x - count_fictitious_of_nodes_x + i][4] = 0;
      f[count_of_nodes_x - count_fictitious_of_nodes_x + i] = 0;
   }

   for (int i = 1; i < count_fictitious_of_nodes_x; i++)
   {
      A[(i + 1) * count_of_nodes_x - 1][0] = 0;
      A[(i + 1) * count_of_nodes_x - 1][1] = 0;
      A[(i + 1) * count_of_nodes_x - 1][2] = 1;
      A[(i + 1) * count_of_nodes_x - 1][3] = 0;
      A[(i + 1) * count_of_nodes_x - 1][4] = 0;
      f[(i + 1) * count_of_nodes_x - 1] = 0;
   }

   for (int i = 1; i < count_of_nodes_y - 1; i++)
      for (int j = 1; j < count_of_nodes_x - 1; j++)
      {
         A[i * count_of_nodes_x + j][0] = -lambda * 2 / ((grid[i][j].y_position - grid[i - 1][j].y_position) * ((grid[i + 1][j].y_position - grid[i][j].y_position) + (grid[i][j].y_position - grid[i - 1][j].y_position)));
         A[i * count_of_nodes_x + j][1] = -lambda * 2 / ((grid[i][j].x_position - grid[i][j - 1].x_position) * ((grid[i][j + 1].x_position - grid[i][j].x_position) + (grid[i][j].x_position - grid[i][j - 1].x_position)));
         A[i * count_of_nodes_x + j][2] = gamma + lambda * (2 / ((grid[i][j].x_position - grid[i][j - 1].x_position) * (grid[i][j + 1].x_position - grid[i][j].x_position)) + 2 / ((grid[i][j].y_position - grid[i - 1][j].y_position) * (grid[i + 1][j].y_position - grid[i][j].y_position)));
         A[i * count_of_nodes_x + j][3] = -lambda * 2 / ((grid[i][j + 1].x_position - grid[i][j].x_position) * ((grid[i][j + 1].x_position - grid[i][j].x_position) + (grid[i][j].x_position - grid[i][j - 1].x_position)));
         A[i * count_of_nodes_x + j][4] = -lambda * 2 / ((grid[i + 1][j].y_position - grid[i][j].y_position) * ((grid[i + 1][j].y_position - grid[i][j].y_position) + (grid[i][j].y_position - grid[i - 1][j].y_position)));
      }
}

void Programs::SetS1(string readFile)
{
   ifstream fout(readFile);
   int count_S1;
   fout >> count_S1;
   int x_S1, y_S1;
   for (int i = 0; i < count_S1; i++)
   {
      fout >> x_S1 >> y_S1;
      A[y_S1 * count_of_nodes_x + x_S1][0] = 0;
      A[y_S1 * count_of_nodes_x + x_S1][1] = 0;
      A[y_S1 * count_of_nodes_x + x_S1][2] = 1;
      A[y_S1 * count_of_nodes_x + x_S1][3] = 0;
      A[y_S1 * count_of_nodes_x + x_S1][4] = 0;
      b[y_S1 * count_of_nodes_x + x_S1] = Func_S1(grid[y_S1][x_S1].x_position, grid[y_S1][x_S1].y_position);
   }
}

double Programs::Func_S1(double x, double y)
{
   return x * y;
}