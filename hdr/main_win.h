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

#include "ui_main_view.h"


namespace Ui
{
class Main_win;
}

class Main_win : public QMainWindow
{
  Q_OBJECT
public:
  explicit Main_win(QWidget* parent = 0);
  virtual ~Main_win();
private slots:
private:
  Ui::MainWindow* ui_;
};

#endif // MAIN_WIN_H
