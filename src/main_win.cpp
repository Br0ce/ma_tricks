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
  settings_("ma_trick_user", "ma_trick"), // stored in ~/.config/ma_trick_user/ma_trick.conf
  pending_add_(false),
  pending_mul_(false),
  dis_char_("ABCDEFGHIJKLMN", 0)
{
  settings_.setFallbacksEnabled(false);
  read_settings();
  init_gui();
}

Main_win::~Main_win()
{
  delete ui_;
}

/*************************gui administration*********************/

void Main_win::init_gui()
{
  ui_->setupUi(this);
  ui_->display->setReadOnly(true);
  ui_->display->setAlignment(Qt::AlignRight);

  connect(ui_->action_beenden, SIGNAL(triggered(bool)), this, SLOT(close()));
  connect(ui_->pb_set_dim, SIGNAL(clicked(bool)), this, SLOT(set_dim_clicked()));
  connect(ui_->pb_enter, SIGNAL(clicked(bool)), this, SLOT(equal_clicked()));
  connect(ui_->pb_plus, SIGNAL(clicked(bool)), this, SLOT(add_clicked()));
  connect(ui_->pb_times, SIGNAL(clicked(bool)), this, SLOT(mul_clicked()));

  build_matrix(mat_dim_);
}

void Main_win::read_settings()
{
  mat_dim_.first = settings_.value("activ_mat/dim_row", 5).toInt();
  mat_dim_tmp_.first = mat_dim_.first;

  mat_dim_.second = settings_.value("activ_mat/dim_col", 5).toInt();
  mat_dim_tmp_.second = mat_dim_.second;
}

void Main_win::save_settings()
{
  settings_.beginGroup("activ_mat");
  settings_.setValue("dim_row", mat_dim_.first);
  settings_.setValue("dim_col", mat_dim_.second);
}

void Main_win::closeEvent(QCloseEvent* event)
{
  save_settings();
  QWidget::closeEvent(event);
}

/*****************gui-matrix-operations*****************/


void Main_win::build_matrix(dim d)
{
  for(int i = 0; i < d.first; ++i)
    for(int j = 0; j < d.second; ++j)
      ui_->mat_layout->addWidget(new Field(), i, j);
}

void Main_win::build_matrix(int rows, int cols)
{
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < cols; ++j)
      ui_->mat_layout->addWidget(new Field(), i, j);
}

void Main_win::remove_matrix()
{
  for(int i = 0; i < mat_dim_.first; ++i)
    for(int j = 0; j < mat_dim_.second; ++j)
      delete ui_->mat_layout->itemAtPosition(i, j)->widget();
}

void Main_win::display_matrix(matrix& m)
{
  for(int i = 0; i < m.rows(); ++i)
  {
    for(int j = 0; j < m.cols(); ++j)
    {
      auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i, j)->widget());
      if(item)
        item->set_text(m(i, j));
    }
  }
}

void Main_win::read_matrix(matrix& m)
{
  m.resize(mat_dim_.first, mat_dim_.second);

  for(int i = 0; i < mat_dim_.first; ++i)
  {
    for(int j = 0; j < mat_dim_.second; ++j)
    {
      auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i, j)->widget());
      if(item)
        m(i, j) = item->get_text();
    }
  }
}

/********************gui-display-operations***************/

void Main_win::to_display(QString s)
{
  QString tmp = ui_->display->text();
  ui_->display->setText(tmp + s);
}

QString Main_win::next_dis_char()
{
  return dis_char_.first.at(dis_char_.second++);
}

void Main_win::reset_display()
{
  dis_char_.second = 0;
  ui_->display->clear();
}

/********************math-operations**********************/

void Main_win::sum_matrix()
{
  for(int i = 0; i < mat_dim_.first; ++i)
  {
    for(int j = 0; j < mat_dim_.second; ++j)
    {
      auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i, j)->widget());
      if(item)
        pending_sum_(i, j) = pending_sum_(i, j) + item->get_text();
    }
  }
}

void Main_win::mul_matrix()
{
  matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);
  pending_factors_ *= m;
}

bool Main_win::dim_mismatch()
{
  return ((pending_factors_.rows() != mat_dim_.first) || (pending_factors_.rows() != mat_dim_.second));

}

/***********************slots****************************/

void Main_win::set_dim_clicked()
{
  Set_dim dialog_set_dim(this, mat_dim_tmp_);
  dialog_set_dim.setModal(true);
  dialog_set_dim.exec();

  remove_matrix();
  build_matrix(mat_dim_tmp_);
  mat_dim_ = mat_dim_tmp_;
}

void Main_win::add_clicked()
{
  if(pending_add_)
  {
    sum_matrix();
    remove_matrix();
    build_matrix(mat_dim_);
  }
  else
  {
    read_matrix(pending_sum_);
    remove_matrix();
    build_matrix(mat_dim_);
    pending_add_ = true;
  }
  to_display(next_dis_char() + "+");
}

void Main_win::mul_clicked()
{
  if(pending_mul_)
  {
    if(!dim_mismatch())
    {
      mul_matrix();
      remove_matrix();
      build_matrix(mat_dim_);
      to_display(next_dis_char() + "*");
    }
    else
    {
      remove_matrix();
      build_matrix(pending_factors_.rows(), pending_factors_.cols());
      display_matrix(pending_factors_);
      ui_->display->clear();
      to_display("matrix dimensions to not match: reset to last matrix");
    }
  }
  else
  {
    read_matrix(pending_factors_);
    remove_matrix();
    build_matrix(mat_dim_);
    pending_mul_ = true;
    to_display(next_dis_char() + "*");
  }
}

void Main_win::equal_clicked()
{
  sum_matrix();
  remove_matrix();
  build_matrix(mat_dim_);

  display_matrix(pending_sum_);

  pending_add_ = false;
  to_display(next_dis_char() + "=");
  to_display(next_dis_char());

}