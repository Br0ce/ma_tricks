/** @file math_module.h
 *
 * @brief Class to perform all the math for matricks
 *
 * Copyright (C) 2016 @author Niklas Beck, beck@informatik.uni-bonn.de
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

#ifndef MATH_MODULE_H
#define MATH_MODULE_H

#include "stdexcept"

#include "helper.h"


struct Math_error : std::runtime_error
{

  Math_error() : runtime_error("Math_error") {}

  explicit Math_error(const std::string msg) :
    runtime_error("Math_error " + msg)
  {}

};

class Math_module
{
public:

  virtual ~Math_module() = default;

  virtual bool add(matrix& m) = 0;
  virtual bool sub(matrix& m) = 0;
  virtual bool mul(matrix& m) = 0;
  virtual bool inv(matrix& m) = 0;
  virtual bool trans(matrix& m) = 0;
  virtual bool equal(matrix& m) = 0;
  virtual bool solve(matrix& A, matrix& b) = 0;
  virtual bool polyfit(matrix& x, matrix& b) = 0;
  virtual matrix& get_res() = 0;

};

#endif // MATH_MODULE_H
