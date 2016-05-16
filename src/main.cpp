/** @file main.cpp
 *
 * @brief Small gui_wrapper for eigen.
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

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include "main_win.h"


void log_to_file(QtMsgType type, const QMessageLogContext& con, const
                 QString& msg)
{
  QString txt;
  QString header = QDateTime::currentDateTime().toString();

  switch(type)
  {
  case QtDebugMsg:
    txt = "Debug: " + header + " " + msg;
    break;

  case QtInfoMsg:
    txt = "Info: " + header + " " + msg;
    break;

  case QtWarningMsg:
    txt = "Warning: " + header + " " + msg;
    break;

  case QtCriticalMsg:
    txt = "Critical: " + header + " " + msg;
    break;

  case QtFatalMsg:
    txt = "Fatal: " + header + " " + msg;
    abort();
  }

  QFile f(QDir::currentPath() + "/log/debug_log.txt");

  if(f.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
  {
    QTextStream ts(&f);
    ts << txt << endl;
  }
}


int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  qInstallMessageHandler(log_to_file);
  Main_win main_win;
  main_win.show();
  return app.exec();
}
