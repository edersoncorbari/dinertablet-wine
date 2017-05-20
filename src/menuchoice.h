/**
 * @file menuchoice.h
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

#ifndef MENUCHOICE_H
#define MENUCHOICE_H

#include <QWidget>

// Override.
namespace Ui {
class MenuChoice;
}

// Override.
class MainWidget;

/**
 * @brief Where is made ​​the choice of food, drink, wine, etc...
 */
class MenuChoice : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     * @param idorder - The number id order.
     */
    explicit MenuChoice(QWidget *parent = 0, int idorder = 1);

    /// Destructor.
    ~MenuChoice();

private Q_SLOTS:
    /**
     * @brief Show the menu containing the food dishes.
     */
    void showMenuDishesFoods();

    /**
     * @brief Show the menu containing the drinks.
     */
    void showMenuDrinks();

    /**
     * @brief Show the menu containing the food desserts.
     */
    void showMenuDesserts();

    /**
     * @brief Show the menu containing the food wines.
     */
    void showMenuWines();

    /**
     * @brief Cancel and close form.
     */
    void cancel();

protected:
    /**
     * @brief Show order in MainWidget.
     */
    void showMainOrder();

    /**
     * @brief Reading the configuration file of the tablet.
     *
     * @param conf - The name config file.
     */
    void readSettings(const QString &conf);

private:
    /// The interface design of this class.
    Ui::MenuChoice *ui;

    /// The pointer @class MainWidget.
    MainWidget *m_mainwidget;

    /// The order number.
    int m_idorder;
};

#endif // MENUFOODS_H
