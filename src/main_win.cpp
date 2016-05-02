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
  connect(ui_->pb_set_dim, SIGNAL(clicked(bool)), this, SLOT(set_dim()));
  connect(ui_->pb_set_A, SIGNAL(clicked(bool)), this, SLOT(set_A()));

  build_matrix(mat_dim_);
}

void Main_win::read_settings()
{
  A_dim_.first = settings_.value("matrix_A/dim_row", 5).toInt();
  A_dim_.second = settings_.value("matrix_A/dim_col", 5).toInt();

  C_dim_.first = settings_.value("matrix_C/dim_row", 5).toInt();
  C_dim_.second = settings_.value("matrix_C/dim_col", 5).toInt();

  b_dim_ = settings_.value("vector_b/dim", 5).toInt();

  mat_dim_.first = settings_.value("activ_mat/dim_row", 5).toInt();
  mat_dim_tmp_.first = mat_dim_.first;

  mat_dim_.second = settings_.value("activ_mat/dim_col", 5).toInt();
  mat_dim_tmp_.second = mat_dim_.second;
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
  settings_.setValue("dim_row", mat_dim_.first);
  settings_.setValue("dim_col", mat_dim_.second);
}

void Main_win::closeEvent(QCloseEvent* event)
{
  save_settings();
  QWidget::closeEvent(event);
}

void Main_win::build_matrix(std::pair<int, int> dim)
{
  for(int i = 0; i < dim.first; ++i)
    for(int j = 0; j < dim.second; ++j)
      ui_->mat_layout->addWidget(new Field(), i, j);
}

void Main_win::remove_matrix()
{
  for(int i = 0; i < mat_dim_.first; ++i)
    for(int j = 0; j < mat_dim_.second; ++j)
      delete ui_->mat_layout->itemAtPosition(i, j)->widget();
}

void Main_win::set_dim()
{
  Set_dim dialog_set_dim(this, mat_dim_tmp_);
  dialog_set_dim.setModal(true);
  dialog_set_dim.exec();

  remove_matrix();
  build_matrix(mat_dim_tmp_);
  mat_dim_ = mat_dim_tmp_;
}

void Main_win::set_A()
{
  math.fill_A(read_matrix(), mat_dim_);
}

std::vector< double > Main_win::read_matrix()
{
  std::vector<double> tmp;

  for(int i = 0; i < mat_dim_.first; ++i)
    for(int j = 0; j < mat_dim_.second; ++j)
    {
      auto item = dynamic_cast<Field*>(ui_->mat_layout->itemAtPosition(i, j)->widget());
      tmp.push_back(item->get_text());
    }

  return tmp;
}

