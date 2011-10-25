/***
 * @file aug_lagrangian_test.h
 *
 * Define a test function for the augmented Lagrangian method.
 */

#ifndef __AUG_LAGRANGIAN_TEST_FUNCTCLINS_H
#define __AUG_LAGRANGIAN_TEST_FUNCTCLINS_H

#include <mlpack/core/io/cli.hpp>
#include <mlpack/core/io/log.h>
#include <armadillo>

namespace mlpack {
namespace optimization {

/***
 * This function is taken from "Practical Mathematical Optimization" (Snyman),
 * section 5.3.8 ("Application of the Augmented Lagrangian Method").  It has
 * only one constraint.
 *
 * The minimum that satisfies the constraint is x = [1, 4], with an objective
 * value of 70.
 */
class AugLagrangianTestFunction {
 public:
  AugLagrangianTestFunction();
  AugLagrangianTestFunction(const arma::mat& initial_point);

  double Evaluate(const arma::mat& coordinates);
  void Gradient(const arma::mat& coordinates, arma::mat& gradient);

  int NumConstraints() const { return 1; }

  double EvaluateConstraint(int index, const arma::mat& coordinates);
  void GradientConstraint(int index,
                          const arma::mat& coordinates,
                          arma::mat& gradient);

  const arma::mat& GetInitialPoint() { return initial_point_; }

 private:
  arma::mat initial_point_;
};

/***
 * This function is taken from M. Gockenbach's lectures on general nonlinear
 * programs, found at:
 * http://www.math.mtu.edu/~msgocken/ma5630spring2003/lectures/nlp/nlp.pdf
 *
 * The program we are using is example 2.5 from this document.
 * I have arbitrarily decided that this will be called the Gockenbach function.
 *
 * The minimum that satisfies the two constraints is given as
 *   x = [0.12288, -1.1078, 0.015100], with an objective value of about 29.634.
 */
class GockenbachFunction {
 public:
  GockenbachFunction();
  GockenbachFunction(const arma::mat& initial_point);

  double Evaluate(const arma::mat& coordinates);
  void Gradient(const arma::mat& coordinates, arma::mat& gradient);

  int NumConstraints() const { return 2; };

  double EvaluateConstraint(int index, const arma::mat& coordinates);
  void GradientConstraint(int index,
                          const arma::mat& coordinates,
                          arma::mat& gradient);

  const arma::mat& GetInitialPoint() { return initial_point_; }

 private:
  arma::mat initial_point_;
};

}; // namespace optimization
}; // namespace mlpack

/***
 * This function is the Lovasz-Theta semidefinite program, as implemented in the
 * following paper:
 *
 * S. Burer, R. Monteiro
 * "A nonlinear programming algorithm for solving semidefinite programs via
 * low-rank factorization."
 * Journal of Mathematical Programming, 2004
 *
 * Given a simple, undirected graph G = (V, E), the Lovasz-Theta SDP is defined
 * by:
 *
 * min_X{Tr(-(e e^T)^T X) : Tr(X) = 1, X_ij = 0 for all (i, j) in E, X >= 0}
 *
 * where e is the vector of all ones and X has dimension |V| x |V|.
 *
 * In the Monteiro-Burer formulation, we take X = R * R^T, where R is the
 * coordinates given to the Evaluate(), Gradient(), EvaluateConstraint(), and
 * GradientConstraint() functions.
 */
class LovaszThetaSDP {
 public:
  LovaszThetaSDP();

  /***
   * Initialize the Lovasz-Theta SDP with the given set of edges.  The edge
   * matrix should consist of rows of two dimensions, where dimension 0 is the
   * first vertex of the edge and dimension 1 is the second edge (or vice versa,
   * as it doesn't make a difference).
   *
   * @param edges Matrix of edges.
   */
  LovaszThetaSDP(const arma::mat& edges);

  double Evaluate(const arma::mat& coordinates);
  void Gradient(const arma::mat& coordinates, arma::mat& gradient);

  int NumConstraints();

  double EvaluateConstraint(int index, const arma::mat& coordinates);
  void GradientConstraint(int index,
                          const arma::mat& coordinates,
                          arma::mat& gradient);

  const arma::mat& GetInitialPoint();

 private:
  arma::mat edges_;
  int vertices_;

  arma::mat initial_point_;
};

#endif
