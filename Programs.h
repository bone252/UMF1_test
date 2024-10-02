#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct node
{
   node (double x_position, double y_position, bool main): x_position(x_position), y_position(y_position), main(main) {};
   node(): x_position(0), y_position(0) {};
   double x_position;
   double y_position;
   bool main;
};

class Programs
{
private:
   int count_of_nodes_x;
   int count_of_nodes_y;
   int count_fictitious_of_nodes_x;
   int count_fictitious_of_nodes_y;
   double lambda, gamma;
   vector<double> f, b;
   vector<vector<node>> grid;
   vector<vector<double>> A;

public:
   bool Read(string readFile);
   void Out();
   void OutA();
   void CreateA();
   void SetS1(string readFile);
   double Func_S1(double x, double y);
   
};