/**
 * @file advertisingnews.h
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

#ifndef ADVERTISINGNEWS_H
#define ADVERTISINGNEWS_H

#include <QtWidgets>

// Override.
namespace Ui {
class AdvertisingNews;
}

/**
 * @brief The commercials advertising the tablet.
 */
class AdvertisingNews : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit AdvertisingNews(QWidget *parent = 0);

    /// Destructor.
    ~AdvertisingNews();

Q_SIGNALS:
    /**
     * @brief Emits the signal when the widget is clicked.
     */
    void clicked();

private Q_SLOTS:
    /**
     * @brief Set background image in windown.
     */
    void imageBackgroundRandom();

    /**
     * @brief Cancel and close form.
     */
    void cancel();

protected:
    /**
     * @brief When the user clicks on the screen sends the
     * signal to close the widget.
     *
     * @param event - The mouse events.
     */
    virtual void mousePressEvent(QMouseEvent *event);

    /**
     * @brief When the user clicks on the screen sends the
     * signal to close the widget.
     *
     * @param event - The mouse events.
     */
    virtual void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief Monitor close app events.
     *
     * @param event - Some events.
     */
    virtual void closeEvent(QCloseEvent *event);

    /**
     * @brief Reading the configuration file of the tablet.
     *
     * @param conf - The name config file.
     */
    void readSettings(const QString &conf);

private:
    /// The interface design of this class.
    Ui::AdvertisingNews *ui;

    /// Store time random images.
    unsigned int m_timerandomadsimages;
};

#endif // ADVERTISINGNEWS
