/** @file set_dim.h
 *
 * @brief QDialog to set dimensions of displayed matrix
 *
 * Copyright (C) 2016  @autor Niklas Beck, beck@informatik.uni-bonn.de
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

#ifndef SET_DIM_H
#define SET_DIM_H

#include <QMainWindow>

#include "ui_set_dim.h"

class Set_dim : public QDialog
{
  Q_OBJECT
public:
  explicit Set_dim(QWidget* parent, std::pair<int, int>& p);
  virtual ~Set_dim();
private slots:
  void set_matrix_dim();
private:
  Ui::Dialog* ui_;
  std::pair<int, int>& p_;
};

#endif // SET_DIM_H
