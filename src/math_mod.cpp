/** @file math_mod.cpp
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

#include "math_mod.h"

Math_mod::Math_mod() :
  pending_add_(false),
  pending_mul_(false)
{ }

Eigen::MatrixXd Math_mod::fill_tmp(std::vector< double > v, std::pair<int, int> d)
{
  A_.resize(d.first, d.second);
  int k = 0;
  for(int i = 0; i < d.first; ++i)
    for(int j = 0; j < d.second; ++j)
      A_(i, j) = v.at(k++);

  return A_;
}

std::vector<double> Math_mod::add(std::vector< double > v, std::pair<int, int> d)
{
  if(!pending_mul_)
  {
    if(!pending_add_)
    {
      pending_sum_ = fill_tmp(v, d);
    }
    else
    {
      pending_sum_ += fill_tmp(v, d);
    }
  }
  return make_vector(pending_sum_);
}

std::vector< double > Math_mod::make_vector(Eigen::MatrixXd& m)
{
  std::vector<double> tmp;

  for(int i = 0; i < m.rows(); ++i)
    for(int j = 0; j < m.cols(); ++j)
      tmp.push_back(m(i, j));

  return tmp;
}
