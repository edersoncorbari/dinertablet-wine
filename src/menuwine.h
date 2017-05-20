/**
 * @file menuwine.h
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

#ifndef MENUWINE_H
#define MENUWINE_H

#include <QtWidgets>

// Override.
namespace Ui {
class MenuWine;
}

// Override.
class XmlRpcClient;

/**
 * @brief This is the main menus of dishes foods.
 */
class MenuWine : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     * @param idorder - The number id order.
     */
    explicit MenuWine(QWidget *parent = 0, int idorder = 1);

    /// Destructor.
    ~MenuWine();

    /**
     * @brief Set number id order..
     *
     * @param idorder - This order id.
     */
    void setIdOrder(int idorder = 1);

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
     * @brief Call method to get the all photos
     * RPC Server.
     */
    void xmlRpcCallPhotos();

    /**
     * @brief Call method to get the all wines
     * RPC Server.
     */
    void xmlRpcCallWines();

    /**
     * @brief Change the image of the label randomly.
     */
    void imageFrameRandom();

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
     * @brief List all wines.
     */
    void listAllWines();

    /**
     * @brief List wine query parameter.
     */
    void listWineParameter();

    /**
     * @brief List filter wine type.
     */
    void listWineType();

    /**
     * @brief List filter wine varietals.
     */
    void listWineVarietals();

    /**
     * @brief List filter wine contries.
     */
    void listWineCountries();

    /**
     * @brief List filter wine region.
     */
    void listWineRegion();

    /**
     * @brief List filter wine producer.
     */
    void listWineProducer();

    /**
     * @brief Slot execute query in RPC Server.
     */
    void getQueryParam();

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

    /**
     * @brief Slot called by class Loader when the image was
     * downloaded.
     */
    void finishedDownload();

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
    Ui::MenuWine *ui;

    /// The XML Rpc Client.
    XmlRpcClient* m_xmlrpc;

    /// Group buttons list add.
    QButtonGroup* m_groupbuttonadd;

    /// Group buttons list detail.
    QButtonGroup* m_groupbuttondetail;

    /// Store RPC parameters.
    QVariantList m_rpcparam;

    /// Store time random images.
    unsigned int m_timerandomadsimages;

    /// The order number.
    int m_idorder;

    /// The filter types.
    int m_winefilter;

    /// Store id wine selected in listwidget.
    int m_idwine;


};

#endif // MENUWINE_H
