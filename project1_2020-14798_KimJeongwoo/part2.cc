#include <deal.II/grid/tria.h>
#include <deal.II/dofs/dof_handler.h>
#include <deal.II/grid/grid_generator.h>
 
#include <deal.II/fe/fe_q.h>
 
#include <deal.II/dofs/dof_tools.h>
 
#include <deal.II/fe/fe_values.h>
#include <deal.II/base/quadrature_lib.h>
 
#include <deal.II/base/function.h>
#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/matrix_tools.h>
 
#include <deal.II/lac/vector.h>
#include <deal.II/lac/full_matrix.h>
#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/dynamic_sparsity_pattern.h>
#include <deal.II/lac/solver_cg.h>
#include <deal.II/lac/precondition.h>
 
#include <deal.II/numerics/data_out.h>
#include <fstream>
#include <iostream>
 
using namespace dealii;
 
template <int dim, int axis>
class MyBoundary : public Function<dim>
{
public:
  virtual double value(const Point<dim> & p,
                       const unsigned int component = 0) const override;
};

template <int dim, int axis>
double MyBoundary<dim, axis>::value(const Point<dim> &p,
                                  const unsigned int /*component*/) const
{
  if (p.operator()(axis) < -0.5) return 1*axis;
  else if (p.operator()(axis) > 0.5) return 1-axis;
  else return p.operator()(axis)*pow(-1,axis)+0.5;
}

 
class Step3
{
public:
  Step3();
 
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
 
 
Step3::Step3()
  : fe(1)
  , dof_handler(triangulation)
{}
 
 
 
void Step3::make_grid()
{
  GridGenerator::hyper_cube(triangulation, -1.5, 1.5);

  // "Some play with several meshes"
  // GridGenerator::hyper_cube_with_cylindrical_hole(triangulation, 0.25, 1.0);
  // const Point<2> center(1, 0);
  // const double   inner_radius = 0.5, outer_radius = 1.0;
  // GridGenerator::hyper_shell(
  //   triangulation, center, inner_radius, outer_radius, 10);

  // triangulation.refine_global(1);

  // for (auto &face : triangulation.active_face_iterators())
  // if ((std::fabs(face->center()(0) - (0.5)) < 1e-12 &&
  //     std::fabs(face->center()(1) - (-1)) < 1e-12)||(std::fabs(face->center()(0) - (1)) < 1e-12 &&
  //     std::fabs(face->center()(1) - (-0.5)) < 1e-12))
  //   face->set_boundary_id(1);

  for (auto &face : triangulation.active_face_iterators()){
    if (std::fabs(face->center()(0) - (1.5)) < 1e-12)
      face->set_boundary_id(1);
    if (std::fabs(face->center()(1) - (-1.5)) < 1e-12)
      face->set_boundary_id(2);
  }
  triangulation.refine_global(6);
 
  std::cout << "Number of active cells: " << triangulation.n_active_cells() 
            << std::endl;
}
 
 
 
 
void Step3::setup_system()
{
  dof_handler.distribute_dofs(fe);
  std::cout << "Number of degrees of freedom: " << dof_handler.n_dofs() << std::endl;
 
  DynamicSparsityPattern dsp(dof_handler.n_dofs());
  DoFTools::make_sparsity_pattern(dof_handler, dsp);
  sparsity_pattern.copy_from(dsp);
 
  system_matrix.reinit(sparsity_pattern);
 
  solution.reinit(dof_handler.n_dofs());
  system_rhs.reinit(dof_handler.n_dofs());
}
 
 
 
void Step3::assemble_system()
{
  QGauss<2> quadrature_formula(fe.degree + 1);
  FEValues<2> fe_values(fe,
                        quadrature_formula,
                        update_values | update_gradients | update_JxW_values);
 
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
        {
          for (const unsigned int i : fe_values.dof_indices())
            for (const unsigned int j : fe_values.dof_indices())
              cell_matrix(i, j) +=
                (fe_values.shape_grad(i, q_index) * // grad phi_i(x_q)
                 fe_values.shape_grad(j, q_index) * // grad phi_j(x_q)
                 fe_values.JxW(q_index));           // dx
 
          for (const unsigned int i : fe_values.dof_indices())
            cell_rhs(i) += (fe_values.shape_value(i, q_index) * // phi_i(x_q)
                            (0) *                                // f(x_q)
                            fe_values.JxW(q_index));            // dx
        }
      cell->get_dof_indices(local_dof_indices);
 
      for (const unsigned int i : fe_values.dof_indices())
        for (const unsigned int j : fe_values.dof_indices())
          system_matrix.add(local_dof_indices[i],
                            local_dof_indices[j],
                            cell_matrix(i, j));
 
      for (const unsigned int i : fe_values.dof_indices())
        system_rhs(local_dof_indices[i]) += cell_rhs(i);
    }
 
 
  std::map<types::global_dof_index, double> boundary_values;
  VectorTools::interpolate_boundary_values(dof_handler,
                                           0,
                                           Functions::ZeroFunction<2>(),
                                           boundary_values);
  VectorTools::interpolate_boundary_values(dof_handler,
                                           1,
                                           MyBoundary<2,1>(),
                                           boundary_values);
  VectorTools::interpolate_boundary_values(dof_handler,
                                           2,
                                           MyBoundary<2,0>(),
                                           boundary_values);
  MatrixTools::apply_boundary_values(boundary_values,
                                     system_matrix,
                                     solution,
                                     system_rhs);
}
 
 
 
void Step3::solve()
{
  SolverControl            solver_control(1000, 1e-6 * system_rhs.l2_norm());
  SolverCG<Vector<double>> solver(solver_control);
  solver.solve(system_matrix, solution, system_rhs, PreconditionIdentity());
}
 
 
 
void Step3::output_results() const
{
  DataOut<2> data_out;
  data_out.attach_dof_handler(dof_handler);
  data_out.add_data_vector(solution, "solution");
  data_out.build_patches();
 
  std::ofstream output("solution.vtk");
  data_out.write_vtk(output);
}
 
 
 
void Step3::run()
{
  make_grid();
  setup_system();
  assemble_system();
  solve();
  output_results();
}
 
 
 
int main()
{
  deallog.depth_console(2);
 
  Step3 laplace_problem;
  laplace_problem.run();
 
  return 0;
}