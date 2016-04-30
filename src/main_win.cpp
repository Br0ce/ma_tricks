/** @file main_win.cpp
 *
 * @brief MainWindow form small gui_wrapper for eigen.
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

#include "main_win.h"

Main_win::Main_win(QWidget* parent) :
  QMainWindow(parent),
  ui_(new Ui::MainWindow),
  settings_("ma_trick_user", "ma_trick") // stored in ~/.config/ma_trick_user/ma_trick.conf
{
  settings_.setFallbacksEnabled(false);
  read_settings();
  init_gui();
}

Main_win::~Main_win()
{
  delete ui_;
}

void Main_win::init_gui()
{
  ui_->setupUi(this);
  ui_->display->setReadOnly(true);
  ui_->display->setAlignment(Qt::AlignRight);

  connect(ui_->action_beenden, SIGNAL(triggered(bool)), this, SLOT(close()));
  build_matrix(matrix_dim_.first, matrix_dim_.first);
}

void Main_win::read_settings()
{
  A_dim_.first = settings_.value("matrix_A/dim_row", 5).toInt();
  A_dim_.second = settings_.value("matrix_A/dim_col", 5).toInt();

  C_dim_.first = settings_.value("matrix_C/dim_row", 5).toInt();
  C_dim_.second = settings_.value("matrix_C/dim_col", 5).toInt();

  b_dim_ = settings_.value("vector_b/dim", 5).toInt();

  matrix_dim_.first = settings_.value("activ_mat/dim_row", 5).toInt();
  matrix_dim_.second = settings_.value("activ_mat/dim_col", 5).toInt();
}

void Main_win::save_settings()
{
  settings_.beginGroup("matirx_A");
  settings_.setValue("dim_row", A_dim_.first);
  settings_.setValue("dim_col", A_dim_.second);
  settings_.endGroup();

  settings_.beginGroup("matrix_C");
  settings_.setValue("dim_row", C_dim_.first);
  settings_.setValue("dim_col", C_dim_.second);
  settings_.endGroup();

  settings_.setValue("vector_b/dim", b_dim_);

  settings_.beginGroup("activ_mat");
  settings_.setValue("dim_row", matrix_dim_.first);
  settings_.setValue("dim_col", matrix_dim_.second);
}

void Main_win::closeEvent(QCloseEvent* event)
{
  save_settings();
  QWidget::closeEvent(event);
}

void Main_win::build_matrix(int row, int col)
{
  for(int i = 0; i < row; ++i)
    for(int j = 0; j < col; ++j)
      ui_->mat_layout->addWidget(new Field(), j, i);
}
