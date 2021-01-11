/******************************************************************************
 *
 * Copyright (C) 2020 Michael Lörcher <MichaelLoecher@web.de>
 *
 * This file is part of the YIO-Remote software project.
 *
 * YIO-Remote software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * YIO-Remote software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with YIO-Remote software. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *****************************************************************************/

#include "epgmodel_mediaplayer.h"

ListEPGModel::ListEPGModel(QObject *parent) : QAbstractListModel(parent), m_count(0) {}

int ListEPGModel::count() const { return m_count; }

int ListEPGModel::rowCount(const QModelIndex &p) const {
    Q_UNUSED(p)
    return m_data.size();
}

QVariant ListEPGModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_data.count()) return QVariant();
    const EPGModelItem &item = m_data[index.row()];
    switch (role) {
        case KeyRole:
            return item.itemKey();
        case XCoordinateRole:
            return item.itemXCoordinate();
        case ColumnRole:
            return item.itemColumn();
        case WidthRole:
            return item.itemWidth();
        case HeightRole:
            return item.itemHeight();
        case TypeRole:
            return item.itemType();
    case ColorRole:
        return item.itemColor();
        case TitleRole:
            return item.itemTitle();
        case CommandsRole:
            return item.itemCommands();
    }
    return QVariant();
}

QHash<int, QByteArray> ListEPGModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "item_key";
    roles[XCoordinateRole] = "item_xCoordinate";
    roles[ColumnRole] = "item_column";
    roles[WidthRole] = "item_width";
    roles[HeightRole] = "item_height";
    roles[TypeRole] = "item_type";
    roles[ColorRole] = "item_color";
    roles[TitleRole] = "item_title";
    roles[CommandsRole] = "item_commands";
    return roles;
}

void ListEPGModel::append(const EPGModelItem &o) {
    int i = m_data.size();
    beginInsertRows(QModelIndex(), i, i);
    m_data.append(o);

    // Emit changed signals
    emit countChanged(count());

    endInsertRows();
}

void ListEPGModel::setCount(int count) {
    if (m_count == count) return;

    m_count = count;
    emit countChanged(m_count);
}

void BrowseEPGModel::addEPGItem(const QString &key, const int &xCoordinate,
                                            const int &column, const int &width, const int& height, const QString &type,
                          const QString &color, const QString &title, const QVariant &commands) {
    ListEPGModel *model = static_cast<ListEPGModel *>(m_model);
    EPGModelItem  item = EPGModelItem(key, xCoordinate, column, width, height, type, color, title, commands);
    model->append(item);
    emit modelChanged();
}
