/**
 * @file menuwidget.h
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

#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QButtonGroup>

/**
 * The designer interfaces.
 */
namespace Ui {
// Override.
class MenuWidget;
}

// Override.
class MenuFoods;
class MenuDrinks;
class MenuWine;

/**
 * @brief The MenuWidget class.
 */
class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     * @param idorder - The number id order.
     */
    explicit MenuWidget(QWidget *parent = 0, int idorder = 1);

    /// Destructor.
    virtual ~MenuWidget();

    /**
     * @brief Set background image in windown.
     *
     * @param img - Image path.
     * @param pix - Image pixmap.
     */
    void setBackgroundImage(const QString &img, const QPixmap &pix);

    /**
     * @brief Set number id order..
     *
     * @param idorder - This order id.
     */
    void setIdOrder(int idorder = 1);

    /**
     * @brief Print number id current order.
     *
     * @return The number id order.
     */
    int printIdCurrentOrder();

    /**
     * @brief Menu which will show first. The objectName,
     * must equal the objectName class.
     *
     * @param objectName - The name of the object that will be shown.
     */
    void setShowMenu(const QString objectName);

    /**
     * @brief Disable or enable objects form.
     * @param disable - True disable objects, false enable.
     */
    void disableObjects(bool disable = false);

private Q_SLOTS:
    /**
     * @brief Used to advance a widget.
     */
    void changeNextPage();

    /**
     * @brief Used to return a widget when it comes to
     * the value -1 closes the window.
     */
    void changeBackPage();

    /**
     * @brief Show My Order.
     */
    void showMyOrder();

    /**
     * @brief Active the objects in widget wheen close
     * form send signal.
     */
    void closeForms();

    /**
     * @brief Closes the this form (send signal).
     */
    void closeAllForms();

    /**
     * @brief Show message after request order (send signal).
     */
    void showMessageAfterRequestOrder();

protected:
    /// The Menu Foods class.
    MenuFoods *m_menufoods;

    /// The Menu Drinks class.
    MenuDrinks *m_menudrinks;

    /// The Menu Wine class.
    MenuWine *m_menuwine;

private:
    /// The interface design of this class.
    Ui::MenuWidget *ui;

    /// The pointer pages widgets.
    QStackedWidget *m_pageswidget;

    /// The order number.
    int m_idorder;
};

#endif // MENUWIDGET_H
