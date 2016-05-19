/** @file helper.h
 *
 * @brief all helpers for matricks
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

#ifndef HELPER_H
#define HELPER_H

#include <QDebug>

#include <utility>

#include <Eigen/Dense>



#define __LOG__FUNC \
qDebug() << Q_FUNC_INFO;

#define __LOG(msg) \
qDebug() << Q_FUNC_INFO << "in Line" << __LINE__ << ":" << msg;


enum class Operation { ADD, SUB, MUL, EQUAL, INV, TRANS };

using dim = std::pair<int, int>;
using matrix = Eigen::MatrixXd;
using vector = Eigen::VectorXd;


#endif // HELPER_H
