/******************************************************************************
 *
 * Copyright (C) 2018-2019 Marton Borzak <hello@martonborzak.com>
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

#include "tvchannelmodel_mediaplayer.h"

ListtvchannelModel::ListtvchannelModel(QObject *parent) : QAbstractListModel(parent), m_count(0) {}

int ListtvchannelModel::count() const { return m_count; }

int ListtvchannelModel::rowCount(const QModelIndex &p) const {
    Q_UNUSED(p)
    return m_data.size();
}

QVariant ListtvchannelModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_data.count()) return QVariant();
    const tvchannelModelItem &item = m_data[index.row()];
    switch (role) {
        case KeyRole:
            return item.item_key();
        case TimeRole:
            return item.item_time();
        case TitleRole:
            return item.item_title();
        case SubTitleRole:
            return item.item_subtitle();
        case TypeRole:
            return item.item_type();
        case ImageUrlRole:
            return item.item_imageUrl();
        case CommandsRole:
            return item.item_commands();
    }
    return QVariant();
}

QHash<int, QByteArray> ListtvchannelModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "item_key";
    roles[TimeRole] = "item_time";
    roles[TitleRole] = "item_title";
    roles[SubTitleRole] = "item_subtitle";
    roles[TypeRole] = "item_type";
    roles[ImageUrlRole] = "item_image";
    roles[CommandsRole] = "item_commands";
    return roles;
}

void ListtvchannelModel::append(const tvchannelModelItem &o) {
    int i = m_data.size();
    beginInsertRows(QModelIndex(), i, i);
    m_data.append(o);

    // Emit changed signals
    emit countChanged(count());

    endInsertRows();
}

void ListtvchannelModel::setCount(int count) {
    if (m_count == count) return;

    m_count = count;
    emit countChanged(m_count);
}

void BrowsetvchannelModel::addtvchannelItem(const QString &key, const QString &time, const QString &title, const QString &subtitle, const QString &type,
                          const QString &imageUrl, const QVariant &commands) {
    ListtvchannelModel *model = static_cast<ListtvchannelModel *>(m_model);
    tvchannelModelItem  item = tvchannelModelItem(key, time, title, subtitle, type, imageUrl, commands);
    model->append(item);
    emit modelChanged();
}
