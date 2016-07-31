/** @file main_win.cpp
 *
 * @brief MainWindow form gui_wrapper for eigen3.
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
  math_(new Simple_math(this)),
  A_set_(false),
  b_set_(false),
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



/**
 * ***********************************************
 *
 * gui administration
 *
 * ***********************************************
 */


void Main_win::init_gui()
{
  ui_->setupUi(this);

  this->setWindowTitle(tr("Matricks"));

  ui_->display->setReadOnly(true);
  ui_->display->setAlignment(Qt::AlignRight);

  ui_->main_layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  connect(ui_->action_save, SIGNAL(triggered(bool)), this,
          SLOT(save_clicked()));
  connect(ui_->action_load, SIGNAL(triggered(bool)), this, SLOT(load_clicked()));
  connect(ui_->action_beenden, SIGNAL(triggered(bool)), this, SLOT(close()));

  connect(ui_->pb_set_dim, SIGNAL(clicked(bool)), this, SLOT(set_dim_clicked()));
  connect(ui_->pb_equal, SIGNAL(clicked(bool)), this, SLOT(equal_clicked()));
  connect(ui_->pb_plus, SIGNAL(clicked(bool)), this, SLOT(add_clicked()));
  connect(ui_->pb_sub, SIGNAL(clicked(bool)), this, SLOT(sub_clicked()));
  connect(ui_->pb_mul, SIGNAL(clicked(bool)), this, SLOT(mul_clicked()));
  connect(ui_->pb_clear, SIGNAL(clicked(bool)), this, SLOT(clear_clicked()));
  connect(ui_->pb_inv, SIGNAL(clicked(bool)), this, SLOT(inv_clicked()));
  connect(ui_->pb_set_A, SIGNAL(clicked(bool)), this, SLOT(set_A_clicked()));
  connect(ui_->pb_set_b, SIGNAL(clicked(bool)), this, SLOT(set_b_clicked()));
  connect(ui_->pb_solve, SIGNAL(clicked(bool)), this, SLOT(solve_clicked()));
  connect(ui_->pb_trans, SIGNAL(clicked(bool)), this, SLOT(trans_clicked()));
  connect(ui_->pb_set_x, SIGNAL(clicked(bool)), this, SLOT(set_x_clicked()));
  connect(ui_->pb_dot, SIGNAL(clicked(bool)), this, SLOT(dot_clicked()));
  connect(ui_->pb_det, SIGNAL(clicked(bool)), this, SLOT(det_clicked()));

  connect(math_.get(), SIGNAL(publish_result(const Matrix&)), this,
          SLOT(display_result(const Matrix&)));

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


void Main_win::resize_main_win(const Dim d)
{
  int h = h_size_;
  int w = w_size_;

  Field f(this);

  auto fh = f.sizeHint().rheight() + ui_->mat_layout->horizontalSpacing();

  h += (d.first - 1) * fh;

  auto fw = f.sizeHint().rwidth();
  auto vs = ui_->mat_layout->verticalSpacing();
  fw += vs;

  auto width = (d.second * fw) + (2 * vs);

  if(w < width)
    w = width;

  this->setFixedSize(w, h);
}



/**
 * ***********************************************
 *
 * gui-matrix-operations
 *
 * ***********************************************
 */


void Main_win::build_matrix(const Dim d)
{
  for(int i = 0; i < d.first; ++i)
    for(int j = 0; j < d.second; ++j)
      ui_->mat_layout->addWidget(new Field(this), i, j,
                                 Qt::AlignHCenter | Qt::AlignBottom);

  resize_main_win(d);
}


void Main_win::build_matrix(const int rows, const int cols)
{
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < cols; ++j)
      ui_->mat_layout->addWidget(new Field(this), i, j, Qt::AlignHCenter |
                                 Qt::AlignBottom);

  resize_main_win(std::make_pair(rows, cols));
}


void Main_win::remove_matrix()
{
  for(int i = 0; i < mat_dim_.first; ++i)
    for(int j = 0; j < mat_dim_.second; ++j)
      delete ui_->mat_layout->itemAtPosition(i, j)->widget();
}


void Main_win::display_matrix(const Matrix& m)
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


void Main_win::display_matrix(const int rows, const int cols, const
                              std::vector<double>& v)
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


void Main_win::display_matrix(const Vector& v)
{
  for(int i = 0; i < v.rows(); ++i)
  {
    auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i,
                                       0)->widget());
    if(item)
      item->set_text(v(i));
  }
}


void Main_win::read_matrix(Matrix& m)
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


void Main_win::read_matrix(Vector& v)
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



/**
 * ***********************************************
 *
 * gui-display-operations
 *
 * ***********************************************
 */


void Main_win::to_display(const QString s) const
{
  QString tmp = ui_->display->text();
  ui_->display->setText(tmp + s);
}


QString Main_win::next_display_char()
{
  return dis_char_.first.at(dis_char_.second++);
}


void Main_win::reset_display()
{
  dis_char_.second = 0;
  ui_->display->clear();
}



/**
 * ***********************************************
 *
 * slots
 *
 * ***********************************************
 */


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
  {
    reset_display();
    to_display("b is vector: set col-dim to 1");
  }

  b_set_ = true;
}


void Main_win::set_x_clicked()
{
  if(mat_dim_.second == 1)
    read_matrix(x_);
  else
  {
    reset_display();
    to_display("x is vector: set col-dim to 1");
  }

  x_set_ = true;
}


void Main_win::set_dim_clicked()
{
  Set_dim dialog_set_dim(this, mat_dim_tmp_);
  dialog_set_dim.setModal(true);

  dialog_set_dim.show();
  dialog_set_dim.exec();

  remove_matrix();
  build_matrix(mat_dim_tmp_);
  mat_dim_ = mat_dim_tmp_;
}


void Main_win::mul_clicked()
{
  Matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);

  try
  {
    math_->mul(m);

    to_display(next_display_char() + " * ");
  }
  catch(std::exception& e)
  {
    to_display(e.what());
  }
}


void Main_win::add_clicked()
{
  Matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);

  try
  {
    math_->add(m);

    to_display(next_display_char() + " + ");
  }
  catch(std::exception& e)
  {
    to_display(e.what());
  }
}


void Main_win::sub_clicked()
{
  Matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);

  try
  {
    math_->sub(m);

    to_display(next_display_char() + " - ");
  }
  catch(std::exception& e)
  {
    to_display(e.what());
  }
}


void Main_win::clear_clicked()
{
  math_->clear();

  remove_matrix();
  build_matrix(mat_dim_);
  reset_display();
}


void Main_win::trans_clicked()
{
  Matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);

  math_->trans(m);

  to_display("(");
  to_display(dis_char_.first.at(dis_char_.second));
  to_display(")trans");
}


void Main_win::inv_clicked()
{
  Matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);

  math_->inv(m);

  to_display("(");
  to_display(dis_char_.first.at(dis_char_.second));
  to_display(")inv");
}


void Main_win::dot_clicked()
{
  try
  {
    if(x_set_ && b_set_)
    {
      math_->dot(x_, b_);

      reset_display();
      to_display("< x , b > = a");
    }
    else
    {
      reset_display();
      to_display("first set x and b");
    }
  }
  catch(std::exception& e)
  {
    reset_display();
    to_display(e.what());
  }
}


void Main_win::solve_clicked()
{
  try
  {
    if(A_set_ && b_set_)
    {
      math_->solve(A_, b_);

      reset_display();
      to_display("x = least-squares solution");
    }
    else
    {
      reset_display();
      to_display("first set A and b");
    }
  }
  catch(std::exception& e)
  {
    reset_display();
    to_display(e.what());
  }
}


void Main_win::det_clicked()
{
  try
  {
    Matrix m(mat_dim_.first, mat_dim_.second);
    read_matrix(m);

    math_->det(m);

    to_display("(");
    to_display(dis_char_.first.at(dis_char_.second));
    to_display(")det");
  }
  catch(std::exception& e)
  {
    reset_display();
    to_display(e.what());
  }
}


void Main_win::equal_clicked()
{
  Matrix m(mat_dim_.first, mat_dim_.second);
  read_matrix(m);

  try
  {
    math_->equal(m);

    to_display(next_display_char() + " = ");
    to_display(next_display_char());
  }
  catch(std::exception& e)
  {
    to_display(e.what());
  }
}


void Main_win::save_clicked()
{
  try
  {
    QFileDialog fd;
    fd.setDefaultSuffix(".mat"); // not working under linux?!

    QString q_form = fd.getSaveFileName(this, tr("Save Matrix"));

    std::ofstream target(q_form.toStdString(), std::ios::trunc);

    if(target.fail()) throw std::ios_base::failure("cannot save matrix");

    for(int i = 0; i < mat_dim_.first; ++i)
    {
      for(int j = 0; j < mat_dim_.second; ++j)
      {
        auto item = qobject_cast< Field* >(ui_->mat_layout->itemAtPosition(i,
                                           j)->widget());
        if(item)
          target << item->get_text() << " ";
      }
      target << "\n";
    }

    target.close();
  }
  catch(std::exception& e)
  {
    to_display(e.what());
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

      mat_dim_.first = row;
      mat_dim_.second = col;

      mat_dim_tmp_.first = row;
      mat_dim_tmp_.second = col;

      display_matrix(row, col, v);
    }
    else throw std::ios_base::failure("cannot open file");
  }
  catch(std::exception& e)
  {
    e.what();
    to_display(e.what());
  }
}


void Main_win::display_result(const Matrix& m)
{
  remove_matrix();
  build_matrix(m.rows(), m.cols());

  mat_dim_.first = m.rows();
  mat_dim_.second = m.cols();

  mat_dim_tmp_.first = m.rows();
  mat_dim_tmp_.second = m.cols();

  display_matrix(m);
}
