/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     gongheng <gongheng@uniontech.com>
 *
 * Maintainer: zhengyouge <zhengyouge@uniontech.com>
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
#include "bookmarkeventreceiver.h"
#include "controller/bookmarkmanager.h"

#include <dfm-framework/dpf.h>

#include <QDebug>

DPBOOKMARK_USE_NAMESPACE

BookMarkEventReceiver *BookMarkEventReceiver::instance()
{
    static BookMarkEventReceiver instance;
    return &instance;
}

void BookMarkEventReceiver::handleRenameFile(quint64 windowId, const QList<QUrl> &urls, bool result, const QString &errorMsg)
{
    Q_UNUSED(windowId)
    Q_UNUSED(errorMsg)
    if (urls.size() == 2 && result)
        BookMarkManager::instance()->fileRenamed(urls.at(0), urls.at(1));
}

void BookMarkEventReceiver::handleAddSchemeOfBookMarkDisabled(const QString &scheme)
{
    BookMarkManager::instance()->addSchemeOfBookMarkDisabled(scheme);
}

void BookMarkEventReceiver::handleSidebarOrderChanged(quint64 winId, const QString &group)
{
    if (group != "Bookmark")
        return;
    auto items = dpfSlotChannel->push("dfmplugin_sidebar", "slot_GetGroupItems", winId, group);
    BookMarkManager::instance()->sortItemsByOrder(items.value<QList<QUrl>>());
}

BookMarkEventReceiver::BookMarkEventReceiver(QObject *parent)
    : QObject(parent) {}
