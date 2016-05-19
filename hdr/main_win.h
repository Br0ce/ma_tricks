/** @file main_win.h
 *
 * @brief MainWindow is a gui for matricks - gui-wrapper for eigen3.
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
#include <QFileDialog>
#include <QFile>
#include <QString>
// #include <QDebug>

#include <vector>
#include <fstream>
#include <istream>
#include <iostream>
#include <memory>

#include <Eigen/Dense>
// #include <Eigen/QR>

#include "field.h"
#include "set_dim.h"
#include "helper.h"
#include "math_module.h"
#include "simple_math.h"

#include "ui_main_view.h"


namespace Ui
{
class Main_win;
}


/**
 * @brief MainWindow for gui-wrapper to eigen3 : Matricks
 *
 */
class Main_win : public QMainWindow
{

  Q_OBJECT

public:

  explicit Main_win(QWidget* parent = 0);
  virtual ~Main_win();

  void init_gui();
  void read_settings();
  void save_settings();

  void build_matrix(const dim d);
  void build_matrix(const int rows, const int cols);
  void remove_matrix();
  void display_matrix(const matrix& m);
  void display_matrix(const vector& v);//TODO delete
  void display_matrix(const int rows, const int cols, const std::vector<double>&
                      v);
  void read_matrix(matrix& m);
  void read_matrix(vector& v);

  void to_display(const QString s) const;
  QString next_display_char();
  void reset_display();

  void resize_main_win(const dim d);

protected:

  void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;

private slots:

  void set_A_clicked();
  void set_b_clicked();
  void set_x_clicked();
  void set_dim_clicked();
  void mul_clicked();
  void add_clicked();
  void sub_clicked();
  void clear_clicked();
  void trans_clicked();
  void inv_clicked();
  void dot_clicked();

  void solve_clicked();
  void det_clicked();
  void equal_clicked();


  void save_clicked();
  void load_clicked();
  void display_result(const matrix& m);

private:

  Ui::MainWindow* ui_;
  QSettings settings_;

  /**
   * minimum height-size of MainWindow for the buttonsection
   */
  static constexpr int h_size_ = 400;

  /**
   * minimum width-size of MainWindow for the buttonsection
   */
  static constexpr int w_size_ = 275;

  std::unique_ptr<Math_module> math_;

  matrix A_;
  matrix b_;
  matrix x_;

  dim mat_dim_;  // dimensions of the displayed matrix
  dim mat_dim_tmp_;

  bool A_set_;
  bool b_set_;
  bool x_set_;

  std::pair<const QString, char> dis_char_;
};

#endif // MAIN_WIN_H
