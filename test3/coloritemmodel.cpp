/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     zhangsheng <zhangsheng@uniontech.com>
 *
 * Maintainer: zhangsheng <zhangsheng@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "coloritemmodel.h"

ColorItemModel::ColorItemModel(QObject *parent):
    QAbstractItemModel(parent)
{

}

void ColorItemModel::appendColor(const QString &text)
{
    QColor color(text);
    if (color.isValid()) {
        beginResetModel();
        m_colors.append(color);
        endResetModel();
    }
}

void ColorItemModel::removeColor(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    beginResetModel();
    m_colors.removeAt(index.row());
    endResetModel();
}

QModelIndex ColorItemModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if (row < 0 || column < 0)
        return QModelIndex();
    return createIndex(row, column);
}

QModelIndex ColorItemModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

int ColorItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_colors.size();
}

int ColorItemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant ColorItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    switch (role) {
    case Qt::DisplayRole:
        return m_colors.at(row).name();
    case Qt::BackgroundRole:
        return m_colors.at(row);
    }
    return QVariant();
}

