/**
 * @file loading.h
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

#ifndef LOADING_H
#define LOADING_H

#include <QtWidgets>

// Override.
namespace Ui {
class Loading;
}

/**
 * @brief Simply shows a gif loading.
 */
class Loading : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit Loading(QWidget *parent = 0);

    /// Destructor.
    ~Loading();

    /**
     * @brief Singleton ListOrder class get instance.
     *
     * @return The static ListOrder.
     */
    static Loading* getInstance();

    /**
     * @brief Show loading.
     */
    void showLoading();

    /**
     * @brief Hide loading.
     */
    void hideLoading();

protected:
    /// Pointer class for singleton instance.
    static Loading *instance;

private:
    /// The interface design of this class.
    Ui::Loading *ui;

    /// The movie gif.
    QMovie* m_movie;
};

#endif // LOADING_H
