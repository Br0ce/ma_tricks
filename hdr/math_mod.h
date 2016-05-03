/** @file math_mod.h
 *
 * @brief Math-modul for gui-wrapper matricks. Using Eigen to do the work.
 *
 * Copyright (C) 2016 @autor Niklas Beck, beck@informatik.uni-bonn.de
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef MATH_MOD_H
#define MATH_MOD_H

#include "Eigen/Dense"

#include <iostream>
#include <vector>

class Math_mod
{
public:
  explicit Math_mod();
  Eigen::MatrixXd fill_tmp(std::vector<double> v, std::pair<int, int> d);
  std::vector<double> add(std::vector<double> v, std::pair<int, int> d);
  std::vector<double> make_vector(Eigen::MatrixXd& m);
  void fill_b(std::vector<double> v, std::pair<int, int> d);
private:
  Eigen::MatrixXd A_;
  Eigen::MatrixXd pending_sum_;
  Eigen::MatrixXd pending_factors_;
  Eigen::VectorXd b_;

  bool pending_add_;
  bool pending_mul_;
};

#endif // MATH_MOD_H
