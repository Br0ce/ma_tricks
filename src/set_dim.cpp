/** @file set_dim.cpp
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

#include "../hdr/set_dim.h"


Set_dim::Set_dim(QWidget* parent, std::pair<int, int>& p) :
  QDialog(parent),
  ui_(new Ui::Dialog),
  p_(p)
{
  ui_->setupUi(this);
  setWindowTitle("set Matrix Dimensions");

  ui_->spinBox_row->setMinimum(1);
  ui_->spinBox_row->setMaximum(25);
  ui_->spinBox_row->setValue(p.first);

  ui_->spinBox_col->setMinimum(1);
  ui_->spinBox_col->setMaximum(25);
  ui_->spinBox_col->setValue(p.second);

  connect(ui_->buttonBox_setup_matrix, SIGNAL(accepted()), this,
          SLOT(set_matrix_dim()));
  connect(ui_->buttonBox_setup_matrix, SIGNAL(rejected()), this, SLOT(close()));
}

void Set_dim::set_matrix_dim()
{
  p_.first = ui_->spinBox_row->value();
  p_.second = ui_->spinBox_col->value();
  this->close();
}

Set_dim::~Set_dim()
{
  delete ui_;
}

