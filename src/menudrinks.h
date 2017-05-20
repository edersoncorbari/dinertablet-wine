/**
 * @file menudrinks.h
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

#ifndef MENUDRINKS_H
#define MENUDRINKS_H

#include <QtWidgets>

// Override.
namespace Ui {
class MenuDrinks;
}

// Override.
class XmlRpcClient;

/**
 * @brief This is the main menus of drinks.
 */
class MenuDrinks : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     * @param idorder - The number id order.
     */
    explicit MenuDrinks(QWidget *parent = 0, int idorder = 1);

    /// Destructor.
    ~MenuDrinks();

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
     * @brief Disable or enable objects form.
     * @param disable - True disable objects, false enable.
     */
    void disableObjects(bool disable = false);

private Q_SLOTS:
    /**
     * @brief Calls the slot method when an error occurs
     * in the RPC Server.
     */
    void xmlRpcError();

    /**
     * @brief Call method to get the categories
     * RPC Server.
     */
    void xmlRpcCallCategory();

    /**
     * @brief Call method to get the drinks
     * RPC Server.
     */
    void xmlRpcCallDrinks();

    /**
     * @brief Slot called by class Loader when the image was
     * downloaded.
     */
    void finishedDownload();

    /**
     * @brief Change the image of the label randomly.
     */
    void imageFrameRandom();

    /**
     * @brief Called by the group buttons menu to get the (id)
     * number of the button that was clicked.
     *
     * @param buttonid - Button id.
     */
    void buttonMenuWasClicked(int buttonid = 0);

    /**
     * @brief Called by the group buttons list to get the (id)
     * number of the button that was clicked.
     *
     * @param buttonid - Button id.
     */
    void buttonListAddWasClicked(int buttonid = 0);

    /**
     * @brief Called by the group buttons list to get the (id)
     * number of the button that was clicked. Shows the detail
     * of the food.
     *
     * @param buttonid - Button id.
     */
    void buttonListDetailWasClicked(int buttonid = 0);

    /**
     * @brief Called when the user clicks on the list.
     *
     * @param item - Item clicked.
     */
    void itemClicked(QListWidgetItem *item);

    /**
     * @brief Slot called by QListWidget when the widget is changed.
     *
     * @param current - The widget current.
     * @param previous - The widget next.
     */
    void currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    /**
     * @brief Active the objects in widget wheen close
     * form send signal.
     */
    void closeForms();

protected:
    /**
     * @brief Show My Order.
     */
    void showMyOrder();

    /**
     * @brief Show Details Food.
     */
    void showDetails();

    /**
     * @brief Reading the configuration file of the tablet.
     *
     * @param conf - The name config file.
     */
    void readSettings(const QString &conf);

private:
    /// The interface design of this class.
    Ui::MenuDrinks *ui;

    /// The XML Rpc Client.
    XmlRpcClient* m_xmlrpc;

    /// Store values Server RPC (categories).
    QList<QVariant> m_categories;

    /// Store list of dynamically created buttons.
    QList<QPushButton*> m_buttonlist;

    /// Group buttons menu.
    QButtonGroup* m_groupbuttonmenu;

    /// Group buttons list add.
    QButtonGroup* m_groupbuttonadd;

    /// Group buttons list detail.
    QButtonGroup* m_groupbuttondetail;

    /// Store id drink selected in listwidget.
    int m_iddrink;

    /// The order number.
    int m_idorder;

    /// Store time random images.
    unsigned int m_timerandomadsimages;

};

#endif // MENUDRINKS_H
