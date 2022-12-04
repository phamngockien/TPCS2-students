
#include <deal.II/grid/tria.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_out.h>
 
#include <iostream>
#include <fstream>
#include <cmath>
 
using namespace dealii;
 
 
void first_grid()
{
  Triangulation<2> triangulation;
 
  GridGenerator::hyper_cube(triangulation);
  triangulation.refine_global(1);

  for (unsigned int step = 0; step<10; ++step){
    for (auto &cell : triangulation.active_cell_iterators())
    {
      unsigned int score = 0;
      for (const auto v : cell->vertex_indices()){

        if (cell->vertex(v)[0] == cell->vertex(v)[1]){
          score += 1;
          }
        
        if (score == 2){
          cell->set_refine_flag();
        }
      }
    }
    triangulation.execute_coarsening_and_refinement();
  }
 
  std::ofstream out("fractal.svg");
  GridOut       grid_out;
  grid_out.write_svg(triangulation, out);
  std::cout << "Grid written to fractal.svg" << std::endl;
}
 
void second_grid(unsigned int n)
{
  Triangulation<2> triangulation;
 
  GridGenerator::hyper_cube(triangulation, -2, 2);
  triangulation.refine_global(2);

  for (unsigned int step = 0; step < n ; ++step){
    for (auto &cell : triangulation.active_cell_iterators())
      {
        unsigned int score = 0;
        for (const auto v : cell->vertex_indices()){

          double x = cell->vertex(v)[0];
          double y = cell->vertex(v)[1];

          double x1 = pow(x,2) - pow(y,2) +x;
          double y1 = 2*x*y + y;

          for (unsigned int num=0; num <n ; ++num){
            x1 = pow(x1,2) - pow(y1,2) +x;
            y1 = 2*x1*y1 +y;

            if ((pow(x1,2) + pow(y1,2)) >= 4){
              break;
            }

            if (num == n-1) score +=1;
          }
        }
        if (score >= 3){
            cell->set_refine_flag();
          }
      }
    triangulation.execute_coarsening_and_refinement();
  }

  std::ofstream out("Mandelbrot_set1.svg");
  GridOut       grid_out;
  grid_out.write_svg(triangulation, out);
  std::cout << "Grid written to Mandelbrot_set.svg" << std::endl;
}

int main()
{
  first_grid();
  second_grid(6);
}