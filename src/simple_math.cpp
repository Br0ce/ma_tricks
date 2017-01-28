/** @file simple_math.cpp
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

#include "../hdr/simple_math.h"


Simple_math::Simple_math(QObject* parent) :
  Math_module(parent),
  status_(3, false) {}


bool Simple_math::calc(const Matrix& m, Operation o)
{

  switch(o)
  {
  case Operation::ADD:

    if(dim_match_add(m))
      sum_stack_ += m;
    else
      throw Math_error("dimensions do not match");
    break;


  case Operation::SUB:

    if(dim_match_add(m))
      sum_stack_ -= m;
    else throw Math_error("dimensions do not match");
    break;


  case Operation::MUL:

    if(dim_match_mul(m))
      mul_stack_ *= m;
    else
      throw Math_error("dimensions do not match");
    break;


  default:
    return false;
  }

  return true;
}


void Simple_math::add(const Matrix& m)
{
  tmp_matrix_ = m;

  if(open_mul()) // point befor line
  {
    calc(tmp_matrix_, Operation::MUL);
    tmp_matrix_ = mul_stack_;

    set_open_mul(false);
  }

  if(open_add()) // pending addition ?
  {
    calc(tmp_matrix_, Operation::ADD);

    emit publish_result(sum_stack_);
  }
  else
  {
    sum_stack_ = m;
    zero_matrix_.resize(sum_stack_.rows(), sum_stack_.cols());
    zero_matrix_.setZero();

    emit publish_result(zero_matrix_);
  }

  set_open_add(true);
}


void Simple_math::sub(const Matrix& m)
{
  //TODO dont use same code as add
  tmp_matrix_ = m;

  if(open_mul())
  {
    calc(tmp_matrix_, Operation::MUL);
    tmp_matrix_ = mul_stack_;

    set_open_mul(false);
  }

  if(open_sub())
  {
    calc(tmp_matrix_, Operation::SUB);

    emit publish_result(sum_stack_);
  }
  else
  {
    sum_stack_ = m;
    zero_matrix_.resize(sum_stack_.rows(), sum_stack_.cols());
    zero_matrix_.setZero();

    emit publish_result(zero_matrix_);
  }

  set_open_sub(true);
}


void Simple_math::mul(const Matrix& m)
{
  tmp_matrix_ = m;

  if(open_mul())
  {
    calc(tmp_matrix_, Operation::MUL);

    emit publish_result(mul_stack_);
  }
  else
  {
    mul_stack_ = tmp_matrix_;
    zero_matrix_.resize(mul_stack_.rows(), mul_stack_.cols());
    zero_matrix_.setZero();

    emit publish_result(zero_matrix_);
  }

  set_open_mul(true);
}


void Simple_math::equal(const Matrix& m)
{
  tmp_matrix_ = m;

  if(open_mul())
  {
    calc(tmp_matrix_, Operation::MUL);
    tmp_matrix_ = mul_stack_;
    mul_stack_.setZero();

    set_open_mul(false);
  }

  if(open_add() || open_sub())
  {
    if(open_add())
    {
      calc(tmp_matrix_, Operation::ADD);
      tmp_matrix_ = sum_stack_;

      set_open_add(false);
    }

    if(open_sub())
    {
      calc(tmp_matrix_, Operation::SUB);
      tmp_matrix_ = sum_stack_;

      set_open_sub(false);
    }
  }
  else
    sum_stack_ = tmp_matrix_;

  emit publish_result(sum_stack_);
}


void Simple_math::clear()
{
  sum_stack_.setZero();
  mul_stack_.setZero();
  tmp_matrix_.setZero();
}

void Simple_math::inv(const Matrix& m)
{
  tmp_matrix_ = m.inverse();

  emit publish_result(tmp_matrix_);
}

void Simple_math::det(const Matrix& m)
{
  tmp_matrix_.resize(1, 1);
  tmp_matrix_(0, 0) = m.determinant();

  emit publish_result(tmp_matrix_);
}


void Simple_math::trans(const Matrix& m)
{
  tmp_matrix_ = m.transpose();

  emit publish_result(tmp_matrix_);
}

void Simple_math::dot(const Matrix& x, const Matrix& y)
{
  if((x.cols() == 1) && y.cols() == 1)
  {
    Vector b = y;

    tmp_matrix_ = x.adjoint() * b;
  }
  else
    throw Math_error("x and b have to be vectors");

  emit publish_result(tmp_matrix_);
}


void Simple_math::solve(const Matrix& A, const Matrix& b)
{
  if(!(A.rows() == b.rows()))
    throw Math_error("dimensions do not match");

  if(b.cols() != 1)
    throw Math_error("b has to be vector");

  tmp_matrix_ = A.colPivHouseholderQr().solve(b);

  emit publish_result(tmp_matrix_);
}


bool Simple_math::dim_match_add(const Matrix& m) const
{
  return (sum_stack_.rows() == m.rows()) && (sum_stack_.cols() == m.cols());
}


bool Simple_math::dim_match_mul(const Matrix& m) const
{
  return (mul_stack_.cols() == m.rows());
}


bool Simple_math::open_add() const { return status_.at(0); }


void Simple_math::set_open_add(const bool b) { status_.at(0) = b; }


bool Simple_math::open_sub() const { return status_.at(1); }


void Simple_math::set_open_sub(const bool b) { status_.at(1) = b; }


bool Simple_math::open_mul() const { return status_.at(2); }


void Simple_math::set_open_mul(const bool b) { status_.at(2) = b; }
