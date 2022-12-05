/*
*Project for Understanding of Computier Science 2
*Made by Jeongil Seo
*on 4, December, 2022
*/
//Header for Triangulation
#include <deal.II/grid/tria.h>
//Header for Gridgenerating and Refine
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/manifold_lib.h>
//Header for Degree of Freedom Handler
#include <deal.II/dofs/dof_handler.h>
#include <deal.II/dofs/dof_tools.h>
//Header for Finite Element
#include <deal.II/fe/fe_q.h>
#include <deal.II/fe/fe_values.h>
//Header for Quadrature
#include <deal.II/base/quadrature_lib.h>
//Header for User Function
#include <deal.II/base/function.h>
//Header for Vector and Matrix Handling
#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/matrix_tools.h>
#include <deal.II/lac/vector.h>
#include <deal.II/lac/full_matrix.h>
#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/dynamic_sparsity_pattern.h>
//Header for Solving and Precondition
#include <deal.II/lac/solver_cg.h>
#include <deal.II/lac/precondition.h>

//Header for Ouput
#include <deal.II/numerics/data_out.h>
#include <deal.II/grid/grid_out.h>
#include <fstream>
#include <iostream>
#include <deal.II/base/logstream.h>

using namespace dealii;

//Declare Template
class Poisson_equation_solve
{
public:
  Poisson_equation_solve();
  void run();

private:
  void make_grid();
  void setup_system();
  void assemble_system();
  void solve();
  void output_results() const;

  Triangulation<2> triangulation;
  FE_Q<2>          fe;
  DoFHandler<2>    dof_handler;

  SparsityPattern      sparsity_pattern;
  SparseMatrix<double> system_matrix;

  Vector<double> solution;
  Vector<double> system_rhs;
};
/*
class RightHandSide : public Function<2>
{
public:
  virtual double value(const Point<2> & p,
                       const unsigned int component = 0) const override;
};
*/
class BoundaryValues : public Function<2>
{
public:
  virtual double value(const Point<2> & p,
                       const unsigned int component = 0) const override;
};
/*
Defining RHS Function and Boundary Value
double RightHandSide::value(const Point<2> &p,
                                 const unsigned int component) const
{
  double return_value = 0.0;
  for (unsigned int i = 0; i < 2; ++i)
    return_value += 4.0 * std::pow(p(i), 4.0);

  return return_value;
}
*/
double BoundaryValues::value(const Point<2> &p,
                                  const unsigned int /*component*/) const
{
  Point<2> center1(0.5, 0.5);
  Point<2> center2(-0.5, -0.5);

  double distance1=p.distance(center1);
  double distance2=p.distance(center2);

  if(std::fabs(distance1-0.25)<0.1)
    return 30.;
  else if(std::fabs(distance2-0.25)<0.1)
    return -1.;
  else
    return 0.;
}


Poisson_equation_solve::Poisson_equation_solve()
  : fe(1)
  , dof_handler(triangulation)
{}

void Poisson_equation_solve::make_grid()
{
  Triangulation<2> tria1;
  Triangulation<2> tria2;
  GridGenerator::subdivided_hyper_cube(tria1, 2, 0, 1);
  GridGenerator::hyper_cube_with_cylindrical_hole(tria2, 0.25, 0.5, 0);
  GridTools::shift(Point<2>(0.5,0.5), tria2);
  GridTools::shift(Point<2>(0,-1), tria1);
  GridGenerator::merge_triangulations(tria1, tria2, triangulation);
  GridTools::shift(Point<2>(-1,1), tria1);
  GridGenerator::merge_triangulations(tria1, triangulation, triangulation);
  GridTools::shift(Point<2>(-1,-1), tria2);
  GridGenerator::merge_triangulations(tria2, triangulation, triangulation);
  triangulation.refine_global(3);

  std::ofstream out("grid-1.svg");
  GridOut       grid_out;
  grid_out.write_svg(triangulation, out);
  std::cout << "Grid written to grid-1.svg" << std::endl;

  std::cout << "   Number of active cells: " << triangulation.n_active_cells()
            << std::endl
            << "   Total number of cells: " << triangulation.n_cells()
            << std::endl;
}

void Poisson_equation_solve::setup_system()
{
  dof_handler.distribute_dofs(fe);
 
  std::cout << "   Number of degrees of freedom: " << dof_handler.n_dofs()
            << std::endl;
 
  DynamicSparsityPattern dsp(dof_handler.n_dofs());
  DoFTools::make_sparsity_pattern(dof_handler, dsp);
  sparsity_pattern.copy_from(dsp);
 
  system_matrix.reinit(sparsity_pattern);
 
  solution.reinit(dof_handler.n_dofs());
  system_rhs.reinit(dof_handler.n_dofs());
}

void Poisson_equation_solve::assemble_system()
{
  QGauss<2> quadrature_formula(fe.degree + 1);

  //RightHandSide right_hand_side;

  FEValues<2> fe_values(fe,
                          quadrature_formula,
                          update_values | update_gradients |
                            update_quadrature_points | update_JxW_values);

  const unsigned int dofs_per_cell = fe.n_dofs_per_cell();

  FullMatrix<double> cell_matrix(dofs_per_cell, dofs_per_cell);
  Vector<double>     cell_rhs(dofs_per_cell);

  std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);

  for (const auto &cell : dof_handler.active_cell_iterators())
    {
      fe_values.reinit(cell);
      cell_matrix = 0;
      cell_rhs    = 0;

      for (const unsigned int q_index : fe_values.quadrature_point_indices())
        for (const unsigned int i : fe_values.dof_indices())
          {
            for (const unsigned int j : fe_values.dof_indices())
              cell_matrix(i, j) +=
                (fe_values.shape_grad(i, q_index) * // grad phi_i(x_q)
                 fe_values.shape_grad(j, q_index) * // grad phi_j(x_q)
                 fe_values.JxW(q_index));           // dx

            //const auto &x_q = fe_values.quadrature_point(q_index);
            cell_rhs(i) += (fe_values.shape_value(i, q_index) * // phi_i(x_q)
                            0. *        // f(x_q)
                            fe_values.JxW(q_index));            // dx
          }

      cell->get_dof_indices(local_dof_indices);
      for (const unsigned int i : fe_values.dof_indices())
        {
          for (const unsigned int j : fe_values.dof_indices())
            system_matrix.add(local_dof_indices[i],
                              local_dof_indices[j],
                              cell_matrix(i, j));

          system_rhs(local_dof_indices[i]) += cell_rhs(i);
        }
    }

  std::map<types::global_dof_index, double> boundary_values;

  VectorTools::interpolate_boundary_values(dof_handler,
                                           0,
                                           BoundaryValues(),
                                           boundary_values);

  MatrixTools::apply_boundary_values(boundary_values,
                                     system_matrix,
                                     solution,
                                     system_rhs);
}

void Poisson_equation_solve::solve()
{
  SolverControl            solver_control(1000, 1e-12);
  SolverCG<Vector<double>> solver(solver_control);
  solver.solve(system_matrix, solution, system_rhs, PreconditionIdentity());

  std::cout << "   " << solver_control.last_step()
            << " CG iterations needed to obtain convergence." << std::endl;
}

void Poisson_equation_solve::output_results() const
{
  DataOut<2> data_out;

  data_out.attach_dof_handler(dof_handler);
  data_out.add_data_vector(solution, "solution");

  data_out.build_patches();

  std::ofstream output("solution-2d.vtk");
  data_out.write_vtk(output);
}

void Poisson_equation_solve::run()
{
  std::cout << "Solving problem in 2 space dimensions."
            << std::endl;

  make_grid();
  setup_system();
  assemble_system();
  solve();
  output_results();
}

int main()
{
  {
    Poisson_equation_solve laplace_problem_2d;
    laplace_problem_2d.run();
  }

  return 0;
}
