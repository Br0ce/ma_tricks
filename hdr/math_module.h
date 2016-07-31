/** @file math_module.h
 *
 * @brief Interface to perform all the math for matricks
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

#include <stdexcept>

#include <QObject>

#include "helper.h"


/**
 * @brief error handling - derived form std::runtime_error
 *
 */
struct Math_error : std::runtime_error
{

  Math_error() : runtime_error("Math_error") {}

  explicit Math_error(const std::string& msg) :
    runtime_error("Math_error " + msg) {}

};

/**
 * @brief Interface to the mathlogic -derived from QObject
 *
 */
class Math_module : public QObject
{

  Q_OBJECT

public:

  explicit Math_module(QObject* parent = 0) : QObject(parent) {}
  virtual ~Math_module() = default;


  /**
   * @brief Publish what is expected from a add-button
   * in the context of a calculator using
   * publish_result(const matrix&)
   *
   * throws Math_error()
   *
   * @param m const matrix&
   * @return void
   */
  virtual void add(const Matrix& m) = 0;


  /**
   * @brief Publish what is expected from a sub-button
   * in the context of a calculator using
   * publish_result(const matrix&)
   *
   * throws Math_error()
   *
   * @param m const matrix&
   * @return void
   */
  virtual void sub(const Matrix& m) = 0;


  /**
   * @brief Publish what is expected from a mul-button
   * in the context of a calculator using
   * publish_result(const matrix&)
   *
   * throws Math_error()
   *
   * @param m const matrix&
   * @return void
   */
  virtual void mul(const Matrix& m) = 0;


  /**
    * @brief Publish what is expected from a equal-button
    * in the context of a calculator using
    * publish_result(const matrix&)
    *
    * throws Math_error()
    *
    * @param m const matrix&
    * @return void
    */
  virtual void equal(const Matrix& m) = 0;


  /**
   * @brief Publish the invert of matrix m using
   * publish_result(const matrix&)
   *
   * @param m const matrix&
   * @return void
   */
  virtual void inv(const Matrix& m) = 0;


  /**
   * @brief Publish the dotproduct < x, y > using
   * publish_result(const matrix&)
   *
   * throws Math_error() if x or y not vector
   *
   * @param x const matrix& - has do be a vector!
   * @param y const matrix& - has do be a vector!
   * @return void
   */
  virtual void dot(const Matrix& x, const Matrix& y) = 0;


  /**
   * @brief Publish the determinant of matrix m using
   * publish_result(const matrix&)
   *
   * @param m const matrix&
   * @return void
   */
  virtual void det(const Matrix& m) = 0;


  /**
   * @brief Publish the transpose of matrix m using
   * publish_result(const matrix&)
   *
   * @param m const matrix&
   * @return void
   */
  virtual void trans(const Matrix& m) = 0;


  /**
   * @brief Publish vector x == least-square solution to Ax=b
   *
   * throws Math_error()
   *
   * @param A const matrix&
   * @param b const matrix& - has to be a vector
   * @return void
   */
  virtual void solve(const Matrix& A, const Matrix& b) = 0;


  /**
   * @brief Clears out all tmp-matrices
   *
   * @return void
   */
  virtual void clear() = 0;

signals:

  void publish_result(const Matrix& m);

};

#endif // MATH_MODULE_H
