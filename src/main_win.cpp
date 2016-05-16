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
  settings_("ma_trick_user",
            "ma_trick"), // stored in ~/.config/ma_trick_user/ma_trick.conf
  pending_add_(false),
  pending_minus_(false),
  pending_mul_(false),
  A_set_(false),
  b_set_(false),
  status_(5, false),
  dis_char_("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0)
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

  connect(ui_->action_save, SIGNAL(triggered(bool)), this, SLOT(save_clicked()));
  connect(ui_->action_load, SIGNAL(triggered(bool)), this, SLOT(load_clicked()));
  connect(ui_->action_beenden, SIGNAL(triggered(bool)), this, SLOT(close()));
  connect(ui_->pb_set_dim, SIGNAL(clicked(bool)), this, SLOT(set_dim_clicked()));
  connect(ui_->pb_equal, SIGNAL(clicked(bool)), this, SLOT(equal_clicked()));
  connect(ui_->pb_plus, SIGNAL(clicked(bool)), this, SLOT(add_clicked()));
  connect(ui_->pb_minus, SIGNAL(clicked(bool)), this, SLOT(minus_clicked()));
  connect(ui_->pb_mul, SIGNAL(clicked(bool)), this, SLOT(mul_clicked()));
  connect(ui_->pb_clear, SIGNAL(clicked(bool)), this, SLOT(clear_clicked()));
  connect(ui_->pb_inv, SIGNAL(clicked(bool)), this, SLOT(inv_clicked()));
  connect(ui_->pb_set_A, SIGNAL(clicked(bool)), this, SLOT(set_A_clicked()));
  connect(ui_->pb_set_b, SIGNAL(clicked(bool)), this, SLOT(set_b_clicked()));
  connect(ui_->pb_solve, SIGNAL(clicked(bool)), this, SLOT(solve_clicked()));

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
      auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i,
                                         j)->widget());
      if(item)
        item->set_text(m(i, j));
    }
  }
}

void Main_win::display_matrix(int rows, int cols, std::vector< double > v)
{
  int k = 0;
  for(int i = 0; i < rows; ++i)
  {
    for(int j = 0; j < cols; ++j)
    {
      auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i,
                                         j)->widget());
      if(item)
        item->set_text(v.at(k++));
    }
  }
}

void Main_win::display_matrix(vector& v)
{
  for(int i = 0; i < v.rows(); ++i)
  {
    auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i,
                                       0)->widget());
    if(item)
      item->set_text(v(i));
  }
}


void Main_win::read_matrix(matrix& m)
{
  m.resize(mat_dim_.first, mat_dim_.second);

  for(int i = 0; i < mat_dim_.first; ++i)
  {
    for(int j = 0; j < mat_dim_.second; ++j)
    {
      auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i,
                                         j)->widget());
      if(item)
        m(i, j) = item->get_text();
    }
  }
}

void Main_win::read_matrix(vector& v)
{
  v.resize(mat_dim_.first);

  for(int i = 0; i < mat_dim_.first; ++i)
  {
    auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i,
                                       0)->widget());
    if(item)
      v(i) = item->get_text();
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

void Main_win::math_control(Status st)
{
  switch(st)
  {
  case Status::ADD :
    if(pending_mul_)
      mul_control();

    add_control();
    break;
  case Status::SUB :
    if(pending_mul_)
      mul_control();

    minus_control();
    break;
  case Status::MUL :
    mul_control();
    break;
  case Status::EQUAL :
    if(pending_mul_)
    {
      mul_matrix();
      remove_matrix();
      build_matrix(pending_factors_.rows(), pending_factors_.cols());

      display_matrix(pending_factors_);

      pending_mul_ = false;
    }

    if(pending_add_)
    {
      sum_matrix();
      remove_matrix();
      build_matrix(mat_dim_);

      display_matrix(pending_sum_);

      pending_add_ = false;
    }

    if(pending_minus_)
    {
      diff_matrix();
      remove_matrix();
      build_matrix(mat_dim_);

      display_matrix(pending_diff_);

      pending_minus_ = false;
    }
    break;
  }
}

void Main_win::sum_matrix()
{
  matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);
  pending_sum_ += m;
}

void Main_win::diff_matrix()
{
  matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);
  pending_diff_ -= m;
}

void Main_win::mul_matrix()
{
  matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);
  pending_factors_ *= m;
}

bool Main_win::dim_mismatch()
{
  return ((pending_factors_.rows() != mat_dim_.first) ||
          (pending_factors_.rows() != mat_dim_.second));
}

bool Main_win::solve_match()
{
  return (A_.cols() == b_.rows());
}

void Main_win::add_control()
{
  if(pending_add_)
  {
    add_pending();
  }
  else
  {
    add();
    pending_add_ = true;
  }
}

void Main_win::add()
{
  read_matrix(pending_sum_);
  remove_matrix();
  build_matrix(mat_dim_);
}

void Main_win::add_pending()
{
  sum_matrix();
  remove_matrix();
  build_matrix(mat_dim_);
}

void Main_win::minus_control()
{
  if(pending_minus_)
  {
    minus_pending();
  }
  else
  {
    minus();
    pending_minus_ = true;
  }
}

void Main_win::minus()
{
  // mul -1
  read_matrix(pending_diff_);
  remove_matrix();
  build_matrix(mat_dim_);
}

void Main_win::minus_pending()
{
  diff_matrix();
  remove_matrix();
  build_matrix(mat_dim_);
}

void Main_win::mul_control()
{
  if(pending_mul_)
  {
    if(!mul_pending())
    {
      reset_display();
      to_display("matrix dimensions to not match: reset to last matrix");
    }
  }
  else
  {
    mul();
    pending_mul_ = true;
  }
}

void Main_win::mul()
{
  read_matrix(pending_factors_);
  remove_matrix();
  build_matrix(mat_dim_);
}

bool Main_win::mul_pending()
{
  if(!dim_mismatch())
  {
    mul_matrix();
    remove_matrix();
    build_matrix(mat_dim_);
    return true;
  }
  else
  {
    remove_matrix();
    build_matrix(pending_factors_.rows(), pending_factors_.cols());
    display_matrix(pending_factors_);
    return false;
  }
}

void Main_win::inv_matrix()
{
  matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);
  matrix n = m.inverse();

  remove_matrix();
  build_matrix(mat_dim_);
  display_matrix(n);
}

/*
Status Main_win::next_op()
{
  if(pending_mul_)
    return Status::MUL;
  else if(pending_minus_)
    return Status::MINUS;
  else if(pending_add_)
    return Status::ADD;
}
*/
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
  math_control(Status::ADD);
  to_display(next_dis_char() + " + ");
}

void Main_win::minus_clicked()
{
  math_control(Status::SUB);
  to_display(next_dis_char() + " - ");
}


void Main_win::mul_clicked()
{
  math_control(Status::MUL);
  to_display(next_dis_char() + " * ");
}

void Main_win::equal_clicked()
{
  math_control(Status::EQUAL);
  to_display(next_dis_char() + " = ");
  to_display(next_dis_char());
}

void Main_win::clear_clicked()
{
  remove_matrix();
  build_matrix(mat_dim_);
  reset_display();
}

void Main_win::inv_clicked()
{
  inv_matrix();
}

void Main_win::set_A_clicked()
{
  A_.resize(mat_dim_.first, mat_dim_.second);
  read_matrix(A_);
  A_set_ = true;
}

void Main_win::set_b_clicked()
{
  if(mat_dim_.second == 1)
    read_matrix(b_);
  else
    to_display("b is vector: set col-dim to 1");

  b_set_ = true;
}

void Main_win::save_clicked()
{
  try
  {
    QFileDialog fd;
    fd.setDefaultSuffix("mat"); // not working in linux?!

    QString q_form = fd.getSaveFileName(this, tr("Save Matrix"));

    std::ofstream target(q_form.toStdString(), std::ios::trunc);

    for(int i = 0; i < mat_dim_.first; ++i)
    {
      for(int j = 0; j < mat_dim_.second; ++j)
      {
        auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i,
                                           j)->widget());
        if(item)
        {
          target << item->get_text();
          target << " ";
        }
      }
      target << "\n";
    }

    target.close();
  }
  catch(...)
  {
    to_display("could not save matrix");
  }
}

void Main_win::load_clicked()
{
  try
  {
    QString q_form = QFileDialog::getOpenFileName(this, tr("Load Matrix"));

    std::ifstream f;
    f.open(q_form.toStdString(), std::ios_base::in);

    if(f.is_open())
    {
      int row = 0;
      int col = 0;
      char c = 0;
      bool flag = true;

      while(f.get(c))
      {
        if(flag && (c == ' '))
          col++;
        if(c == '\n')
        {
          row++;
          flag = false;
        }
      }

      f.clear();
      f.seekg(0, f.beg);

      std::istream_iterator<double> ii{f};
      std::istream_iterator<double> eos{};
      std::vector<double> v{ii, eos};

      f.close();

      remove_matrix();
      build_matrix(row, col);
      display_matrix(row, col, v);
    }
  }
  catch(std::exception& e)
  {
    e.what();
    to_display("cannot load matrix");
  }
}

void Main_win::solve_clicked()
{
  if((A_set_ && b_set_) && solve_match())
  {
    vector res = A_.householderQr().solve(b_);
    remove_matrix();
    build_matrix(res.rows(), 1);
    display_matrix(res);
  }
  else
  {
    to_display("first set A and b");
  }
}
