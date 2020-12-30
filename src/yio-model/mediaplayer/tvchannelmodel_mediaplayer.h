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

#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QVariant>
#include <QtDebug>

class tvchannelModelItem {
 public:
    tvchannelModelItem(const QString& key, const QString& time, const QString& title,
                       const QString& subtitle, const QString& type,
              const QString& imageUrl, const QVariant& commands)
        : m_key(key), m_time(time), m_title(title), m_subtitle(subtitle),
          m_type(type), m_imageUrl(imageUrl), m_commands(commands) {}

    QString  item_key() const { return m_key; }
    QString  item_time() const { return m_time; }
    QString  item_title() const { return m_title; }
    QString  item_subtitle() const { return m_subtitle; }
    QString  item_type() const { return m_type; }
    QString  item_imageUrl() const { return m_imageUrl; }
    QVariant item_commands() const { return m_commands; }

 private:
    QString  m_key;
    QString  m_time;
    QString  m_title;
    QString  m_subtitle;
    QString  m_type;
    QString  m_imageUrl;
    QVariant m_commands;
};

class ListtvchannelModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

 public:
    enum SearchRoles { KeyRole = Qt::UserRole + 1, TimeRole, TitleRole, SubTitleRole,
                       TypeRole, ImageUrlRole, CommandsRole };

    explicit ListtvchannelModel(QObject* parent = nullptr);
    ~ListtvchannelModel() {}

    int                    count() const;
    int                    rowCount(const QModelIndex& p = QModelIndex()) const;
    QVariant               data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    void append(const tvchannelModelItem& o);

 public slots:  // NOLINT open issue: https://github.com/cpplint/cpplint/pull/99
    void setCount(int count);

 signals:
    void countChanged(int count);

 private:
    int              m_count;
    QList<tvchannelModelItem> m_data;
};

class BrowsetvchannelModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString subtitle READ subtitle NOTIFY subtitleChanged)
    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    Q_PROPERTY(QString imageUrl READ imageUrl NOTIFY imageUrlChanged)
    Q_PROPERTY(QObject* model READ model NOTIFY modelChanged)
    Q_PROPERTY(QStringList commands READ commands NOTIFY commandsChanged)

 public:
    BrowsetvchannelModel(QObject* parent = nullptr, const QString& id = "", const QString& time = "",
                         const QString& title = "", const QString& subtitle = "", const QString& type = "",
                         const QString& imageUrl = "", const QStringList& commands = {})
        : m_id(id), m_time(time), m_title(title), m_subtitle(subtitle), m_type(type),
          m_imageUrl(imageUrl), m_commands(commands) {
        Q_UNUSED(parent)
    }
    ~BrowsetvchannelModel() {}

    QString     id() { return m_id; }
    QString     time() { return m_time; }
    QString     title() { return m_title; }
    QString     subtitle() { return m_subtitle; }
    QString     type() { return m_type; }
    QString     imageUrl() { return m_imageUrl; }
    QObject*    model() { return m_model; }
    QStringList commands() { return m_commands; }

    void addtvchannelItem(const QString& key, const QString& time, const QString& title, const QString& subtitle,
                          const QString& type, const QString& imageUrl, const QVariant& commands);

 signals:
    void idChanged();
    void titleChanged();
    void subtitleChanged();
    void typeChanged();
    void imageUrlChanged();
    void modelChanged();
    void commandsChanged();

 private:
    QString     m_id;
    QString     m_time;
    QString     m_title;
    QString     m_subtitle;
    QString     m_type;
    QString     m_imageUrl;
    QObject*    m_model = new ListtvchannelModel();
    QStringList m_commands;
};
