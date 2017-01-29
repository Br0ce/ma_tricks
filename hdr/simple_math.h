/** @file simple_math.h
 *
 * @brief Concret Math_module to do the calculation for Matricks
 * heavily inspird by an example of the qt-documentation
 *
 * Copyright (C) 2016  @author Niklas Beck, beck@informatik.uni-bonn.de
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

#ifndef SIMPLE_MATH_H
#define SIMPLE_MATH_H


#include "math_module.h"
#include "helper.h"


/**
 * @brief Concret class to do the math for matricks - derived from QObject
 *
 */
class Simple_math : public Math_module
{
public:

  explicit Simple_math(QObject* parent = 0);
  virtual ~Simple_math() = default;


  /**
   * @brief Performs the Operation o on m
   *
   * throws Math_error()
   *
   * @param m const matrix& - right Operant of Operation o
   * @param o Operation - Operation to perform
   * @return bool
   */
  bool calc(const Matrix& m, Operation o);



  /***************************************
   *
   * Implementation off Math_module
   *
   ***************************************
   */

  void add(const Matrix& m) override;
  void sub(const Matrix& m) override;
  void mul(const Matrix& m) override;
  void div(const Matrix& m) override;
  void equal(const Matrix& m) override;
  void clear() override;

  void trans(const Matrix& m) override;
  void inv(const Matrix& m) override;
  void dot(const Matrix& x, const Matrix& y) override;
  void det(const Matrix& m) override;
  void solve(const Matrix& A, const Matrix& b) override;



  /***************************************
   *
   * helper-functions
   *
   ***************************************
   */


  /**
   * @brief Checks if dimensions of m fit to sum_stack_
   * to perform a add-operation
   *
   * @param m const matrix&
   * @return bool
   */
  bool dim_match_add(const Matrix& m) const;


  /**
   * @brief Checks if dimensions of m fit to mul_stack_
   * to perform a matrix-multiplication
   *
   * @param m const matrix&
   * @return bool
   */
  bool dim_match_mul(const Matrix& m) const;


  /**
   * @brief Checks if the is a pending add operation
   *
   * @return bool
   */
  bool open_add() const;


  /**
   * @brief Set a pending add operation
   *
   * @param b bool
   * @return void
   */
  void set_open_add(const bool b);


  /**
   * @brief Checks if the is a pending sub operation
   *
   * @return bool
   */
  bool open_sub() const;


  /**
   * @brief Set a pending sub operation
   *
   * @param b bool
   * @return void
   */
  void set_open_sub(const bool b);


  /**
   * @brief Checks if the is a pending mul operation
   *
   * @return bool
   */
  bool open_mul() const;


  /**
  * @brief Set a pending mul operation
  *
  * @param b bool
  * @return void
  */
  void set_open_mul(const bool b);

private:

  Matrix sum_stack_;   // holds the actual sum
  Matrix mul_stack_;   // holds the actual factor
  Matrix tmp_matrix_;  // used to store tmp-results
  Matrix zero_matrix_;

  std::vector<bool> status_; //at: 0=open_add, 1=open_sub, 2=open_mul

};

#endif // SIMPLE_MATH_H
