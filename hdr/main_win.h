/** @file main_win.h
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

#ifndef MAIN_WIN_H
#define MAIN_WIN_H

#include <QMainWindow>
#include <QSettings>
#include <QDebug>

#include <exception>
#include <vector>

#include <Eigen/Dense>

#include "field.h"
#include "set_dim.h"

#include "ui_main_view.h"


namespace Ui
{
class Main_win;
}

enum class Op { ADD, SUB, MUL, NONE };

class Main_win : public QMainWindow
{
  Q_OBJECT
public:
  using dim = std::pair<int, int>;
  using matrix = Eigen::MatrixXd;

  explicit Main_win(QWidget* parent = 0);
  virtual ~Main_win();

  void init_gui();
  void read_settings();
  void save_settings();

  void build_matrix(dim d);
  void build_matrix(int rows, int cols);
  void remove_matrix();
  void display_matrix(matrix& m);
  void read_matrix(matrix& m);

  void to_display(QString s);
  QString next_dis_char();
  void reset_display();

  void sum_matrix();
  void mul_matrix();
  bool dim_mismatch();
  void add_control();
  void add();
  void add_pending();
  void mul_control();
  void mul();
  bool mul_pending();
protected:
  void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
private slots:
  void set_dim_clicked();
  void add_clicked();
  void mul_clicked();
  void equal_clicked();
  void clear_clicked();
private:
  Ui::MainWindow* ui_;
  QSettings settings_;

  matrix pending_sum_;
  matrix pending_factors_;

  dim mat_dim_;
  dim mat_dim_tmp_;

  bool pending_add_;
  bool pending_mul_;
  Op pending_op_;
  std::pair<QString, char> dis_char_;
};

#endif // MAIN_WIN_H
