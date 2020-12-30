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
#include "mainwindow.h"

#include <QDebug>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "colorlistview.h"
#include "coloritemmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    initializeUi();
    handleEvents();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initializeUi()
{
    resize(400, 600);

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;

    m_comb = new QComboBox;
    m_comb->addItems({"red", "green", "blue", "cyan", "yellow", "purple", "white", "black"});
    m_appendBtn = new QPushButton("append");
    m_removeBtn = new QPushButton("remove");
    m_removeBtn->setEnabled(false);
    hlayout->addWidget(m_comb);
    hlayout->addWidget(m_appendBtn);
    hlayout->addWidget(m_removeBtn);

    m_view = new ColorListView;
    m_model = new ColorItemModel;
    m_view->setModel(m_model);

    layout->addLayout(hlayout);
    layout->addWidget(m_view);
    setLayout(layout);
}

void MainWindow::handleEvents()
{
    connect(m_appendBtn, &QPushButton::clicked, this, &MainWindow::append);
    connect(m_removeBtn, &QPushButton::clicked, this, &MainWindow::remove);

    connect(m_view, &ColorListView::clicked, this, [this]() {
        m_removeBtn->setEnabled(true);
    });
}

void MainWindow::append()
{
    QString &&colorText = m_comb->currentText();
    qDebug() << "append color" << colorText;
    m_model->appendColor(colorText);
}

void MainWindow::remove()
{
    auto index = m_view->currentIndex();
    m_removeBtn->setEnabled(false);
    m_model->removeColor(index);
}
