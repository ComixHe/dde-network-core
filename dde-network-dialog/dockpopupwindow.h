/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *
 * Maintainer: sbw <sbw@sbw.so>
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

#ifndef DOCKPOPUPWINDOW_H
#define DOCKPOPUPWINDOW_H

#include <darrowrectangle.h>

namespace Dtk {
    namespace Gui {
        class DRegionMonitor;
        class DWindowManagerHelper;
    } // namespace Gui
} // namespace Dtk

DWIDGET_USE_NAMESPACE

class DockPopupWindow : public Dtk::Widget::DArrowRectangle
{
    Q_OBJECT

public:
    explicit DockPopupWindow(QWidget *parent = 0);
    ~DockPopupWindow();

    bool model() const;

    void setContent(QWidget *content);
    void setBackground(const QImage &image);
    void closeDialog();

public slots:
    void show(const QPoint &pos, const bool model = false);
    void show(const int x, const int y);
    void onGlobMouseRelease(const QPoint &mousePos, const int flag);

signals:
    void accept() const;
    // 在把专业版的仓库降级到debian的stable时, dock出现了一个奇怪的问题:
    // 在plugins/tray/system-trays/systemtrayitem.cpp中的showPopupWindow函数中
    // 无法连接到上面这个信号: "accept", qt给出一个运行时警告提示找不到信号
    // 目前的解决方案就是在下面增加了这个信号
    void unusedSignal();
    void hideSignal();

protected:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    void enterEvent(QEvent *e);
    bool eventFilter(QObject *o, QEvent *e);
    void paintEvent(QPaintEvent *event);

private slots:
    void compositeChanged();
    void ensureRaised();

private:
    bool m_model;
    QPoint m_lastPoint;

    Dtk::Gui::DRegionMonitor *m_regionInter;
    Dtk::Gui::DWindowManagerHelper *m_wmHelper;

    QImage *m_bgImage;
    QImage *m_srcImage;
};

#endif // DOCKPOPUPWINDOW_H
