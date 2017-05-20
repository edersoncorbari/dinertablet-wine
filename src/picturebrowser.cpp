/**
 * @file picturebrowser.cpp
 *
 * Implementations for an diner-tablet.
 *
 * MOBILE-APP - Project DinerTablet.
 *
 * Copyright (c) 2014 BlueSalute Company Ltda.
 *
 * @author Ederson Moura - <ederson.moura@bluesalute.com.br>
 *
 * $Id: Exp$
 */

#include "picturebrowser.h"

#include <QTime>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>

PictureBrowser::PictureBrowser(QWidget *parent) : PictureFlow(parent)
{
    // Delete widget affter close.
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    // Set windown name.
    this->setWindowTitle(QObject::tr("Photos"));
}

PictureBrowser::~PictureBrowser()
{
}

QStringList PictureBrowser::findImages(const QString &path)
{
    QStringList files;

    QDir dir = QDir::current();
    if(!path.isEmpty()) {
        dir = QDir(path);
    }

    dir.setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        files.append(dir.absoluteFilePath(fileInfo.fileName()));
    }

    return files;
}
