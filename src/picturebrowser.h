/**
 * @file picturebrowser.h
 *
 * Definitions for an diner-tablet.
 *
 * MOBILE-APP - Project DinerTablet.
 *
 * Copyright (c) 2014 BlueSalute Company Ltda.
 *
 * @author Ederson Moura - <ederson.moura@bluesalute.com.br>
 *
 * $Id: Exp$
 */

#ifndef PICTUREBROWSER_H
#define PICTUREBROWSER_H

#include "thirdpartycodes/pictureflow.h"

#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <QString>
#include <QStringList>

/**
 * @brief Used to cover the flow of images.
 */
class PictureBrowser: public PictureFlow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    PictureBrowser(QWidget* parent = 0);

    /// Destructor.
    ~PictureBrowser();

    /**
     * @brief Looking for the photos/images in a directory.
     *
     * @param path - Full path directory photos.
     * @return Return the imagens found in directory.
     */
    QStringList findImages(const QString &path = QString());

};

#endif // PICTUREBROWSER_H
