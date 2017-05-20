/**
 * @file listorder.h
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

#ifndef LISTORDER_H
#define LISTORDER_H

#include <QtWidgets>

// Override.
namespace Ui {
class ListOrder;
}

// Override.
class XmlRpcClient;

/**
 * @brief Contains list of order that the customer
 * is doing.
 */
class ListOrder : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit ListOrder(QWidget *parent = 0);

    /// Destructor.
    ~ListOrder();

    /**
     * @brief Singleton ListOrder class get instance.
     *
     * @return The static ListOrder.
     */
    static ListOrder* getInstance();

    /**
     * @brief Check is order is empty.
     * @return The item orders.
     */
    int checkOrderIsEmpty();

    /**
     * @brief Start and show List Foods.
     * @param id - The id food.
     */
    void startListFoods(int id = 0);

    /**
     * @brief Start and show List Drinks.
     * @param id - The id drink.
     */
    void startListDrinks(int id = 0);

    /**
     * @brief Start and show List Wine.
     * @param id - The id wine.
     */
    void startListWine(int id = 0);

    /**
     * @brief Show all list orders.
     */
    void showAll();

private Q_SLOTS:
    /**
     * @brief Calls the slot method when an error occurs
     * in the RPC Server.
     */
    void xmlRpcError();

    /**
     * @brief Call method to get the dishes
     * RPC Server.
     */
    void xmlRpcCallDishes();

    /**
     * @brief Call method to get the drinks
     * RPC Server.
     */
    void xmlRpcCallDrinks();

    /**
     * @brief Call method to get the wine
     * RPC Server.
     */
    void xmlRpcCallWines();

    /**
     * @brief Add more foods.
     */
    void addMore();

    /**
     * @brief Shows the message to request, if the button is
     * clicked ok calls the orderRequestNow.
     */
    void orderRequest();

    /**
     * @brief Makes the request and the request is printing
     * order.
     */
    void orderRequestNow();

    /**
     * @brief Called by the group buttons list (foods) to get the (id)
     * number of the button that was clicked. Changes in the unit
     * qspinbox dish always adding "1" when it.
     *
     * @param buttonid - Button id.
     */
    void buttonListFoodsAddWasClicked(int buttonid = 0);

    /**
     * @brief Called by the group buttons list (foods) to get the (id)
     * number of the button that was clicked. Changes in the unit
     * qspinbox dish for less. When it reaches the value of zero "0"
     * deletes the list item.
     *
     * @param buttonid - Button id.
     */
    void buttonListFoodsRemoveWasClicked(int buttonid = 0);

    /**
     * @brief Called by the group buttons list (drinks) to get the (id)
     * number of the button that was clicked. Changes in the unit
     * qspinbox dish always adding "1" when it.
     *
     * @param buttonid - Button id.
     */
    void buttonListDrinksAddWasClicked(int buttonid = 0);

    /**
     * @brief Called by the group buttons list (drinks) to get the (id)
     * number of the button that was clicked. Changes in the unit
     * qspinbox dish for less. When it reaches the value of zero "0"
     * deletes the list item.
     *
     * @param buttonid - Button id.
     */
    void buttonListDrinksRemoveWasClicked(int buttonid = 0);

    /**
     * @brief Called by the group buttons list (wines) to get the (id)
     * number of the button that was clicked. Changes in the unit
     * qspinbox dish always adding "1" when it.
     *
     * @param buttonid - Button id.
     */
    void buttonListWinesAddWasClicked(int buttonid = 0);

    /**
     * @brief Called by the group buttons list (wines) to get the (id)
     * number of the button that was clicked. Changes in the unit
     * qspinbox dish for less. When it reaches the value of zero "0"
     * deletes the list item.
     *
     * @param buttonid - Button id.
     */
    void buttonListWinesRemoveWasClicked(int buttonid = 0);

    /**
     * @brief Called when the user clicks on the list food.
     *
     * @param item - Item clicked.
     */
    void itemClickedFoods(QListWidgetItem *item);

    /**
     * @brief Slot called by QListWidgetFoods when the widget
     * is changed.
     *
     * @param current - The widget current.
     * @param previous - The widget next.
     */
    void currentItemChangedFoods(QListWidgetItem *current, QListWidgetItem *previous);

    /**
     * @brief Called when the user clicks on the list drinks.
     *
     * @param item - Item clicked.
     */
    void itemClickedDrinks(QListWidgetItem *item);

    /**
     * @brief Slot called by QListWidgetDrinks when the widget
     * is changed.
     *
     * @param current - The widget current.
     * @param previous - The widget next.
     */
    void currentItemChangedDrinks(QListWidgetItem *current, QListWidgetItem *previous);

    /**
     * @brief Called when the user clicks on the list wines.
     *
     * @param item - Item clicked.
     */
    void itemClickedWines(QListWidgetItem *item);

    /**
     * @brief Slot called by QListWidgetWine when the widget
     * is changed.
     *
     * @param current - The widget current.
     * @param previous - The widget next.
     */
    void currentItemChangedWines(QListWidgetItem *current, QListWidgetItem *previous);

    /**
     * @brief Show list widget foods.
     */
    void showListWidgetFoods();

    /**
     * @brief Show list widget drinks.
     */
    void showListWidgetDrinks();

    /**
     * @brief Show list widget wine.
     */
    void showListWidgetWine();

Q_SIGNALS:
    /**
     * @brief Sends a signal when the method addMore() is
     * clicked.
     */
    void addMoreClicked();

    /**
     * @brief Sends the signal after it prints the order.
     */
    void afterRequestOrder();

protected:
    /**
     * @brief Save all data in file.
     */
    void saveData();

    /**
     * @brief Monitor close app events.
     *
     * @param event - Some events.
     */
    virtual void closeEvent(QCloseEvent *event);

    /**
     * @brief Set background image in windown.
     *
     * @param img - Image path.
     * @param pix - Image pixmap.
     */
    void setBackgroundImage(const QString &img, const QPixmap &pix);

    /// Pointer class for singleton instance.
    static ListOrder *instance;

private:
    /// The interface design of this class.
    Ui::ListOrder *ui;

    /// The XML Rpc Client.
    XmlRpcClient* m_xmlrpc;

    /**
     * Contains the variables and related objects (Foods).
     */
    struct foods {
        QList<QVariant> datalocal; //!<  Store in list foods the local values.
        QList<QVariant> id; //!< Store in list the number id foods.
        QMap<int, int> mapspins; //!< Store in map the values spinbox.
        QList<QSpinBox*> spinlist; //!< Store spinboxs.
        QString filename; //!< Store name save data filename.
        QString filenameids; //!< Store name save data ids.
        QString filenamespin; //!< Store name save data spinbox.
        QButtonGroup* groupbuttonremove; //!< Group buttons list remove.
        QButtonGroup* groupbuttonadd; //!< Group buttons list add.
    };

    /// Object foods.
    foods m_foods;

    /**
     * Contains the variables and related objects (Drinks).
     */
    struct drinks {
        QList<QVariant> datalocal; //!<  Store in list drinks the local values.
        QList<QVariant> id; //!< Store in list the number id foods.
        QMap<int, int> mapspins; //!< Store in map the values spinbox.
        QList<QSpinBox*> spinlist; //!< Store spinboxs.
        QString filename; //!< Store name save data filename.
        QString filenameids; //!< Store name save data ids.
        QString filenamespin; //!< Store name save data spinbox.
        QButtonGroup* groupbuttonremove; //!< Group buttons list remove.
        QButtonGroup* groupbuttonadd; //!< Group buttons list add.
    };

    /// Objects drinks.
    drinks m_drinks;

    /**
     * Contains the variables and related objects (Wine).
     */
    struct wine {
        QList<QVariant> datalocal; //!<  Store in list drinks the local values.
        QList<QVariant> id; //!< Store in list the number id foods.
        QMap<int, int> mapspins; //!< Store in map the values spinbox.
        QList<QSpinBox*> spinlist; //!< Store spinboxs.
        QString filename; //!< Store name save data filename.
        QString filenameids; //!< Store name save data ids.
        QString filenamespin; //!< Store name save data spinbox.
        QButtonGroup* groupbuttonremove; //!< Group buttons list remove.
        QButtonGroup* groupbuttonadd; //!< Group buttons list add.
    };

    /// Objects wine.
    wine m_wine;

    /// The id foods.
    int m_idfood;

    /// The id drinks.
    int m_iddrinks;

    /// The id wine.
    int m_idwine;
};

#endif // LISTORDER_H
