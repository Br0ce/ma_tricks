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
  init_gui();
}

Main_win::~Main_win()
{
  delete ui_;
}

void Main_win::init_gui()
{
  ui_->setupUi(this);

  connect(ui_->action_beenden, SIGNAL(triggered(bool)), this, SLOT(close()));
}
