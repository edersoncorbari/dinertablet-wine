/**
 * @file listitemdetails.h
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

#ifndef LISTITEMDETAILS_H
#define LISTITEMDETAILS_H

#include <QtWidgets>

// Override.
namespace Ui {
class ListItemDetails;
}

// Override.
class XmlRpcClient;

/**
 * @brief When user clicks to add another account, and
 * put the person's name.
 */
class ListItemDetails : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit ListItemDetails(QWidget *parent = 0);

    /// Destructor.
    ~ListItemDetails();

    /**
     * @brief Start and show details Foods.
     * @param id - The id food.
     */
    void startDetailsFoods(int id = 0);

    /**
     * @brief Start and show details Drinks.
     * @param id - The id drink.
     */
    void startDetailsDrinks(int id = 0);

private Q_SLOTS:    
    /**
     * @brief Add more foods.
     */
    void add();

    /**
     * @brief Cancel and close form.
     */
    void cancel();

     /**
     * @brief Calls the slot method when an error occurs
     * in the RPC Server.
     */
    void xmlRpcError();

    /**
     * @brief Call method to get detail dishe
     * RPC Server.
     */
    void xmlRpcCallDetailDishe();

    /**
     * @brief Call method to get detail drink
     * RPC Server.
     */
    void xmlRpcCallDetailDrink();

    /**
     * @brief Call method to get photos in
     * RPC Server.
     */
    void xmlRpcCallPhotos();    

    /**
     * @brief When the user clicks on the image of
     * the cover flow, we moved to the clicked window the
     * whole picture.
     */
    void changePicture();

    /**
     * @brief Hide widget PictureFlow.
     */
    void hidePictureFlow();

    /**
     * @brief Show widget PictureFlow.
     */
    void showPictureFlow();

    /**
     * @brief Slot called by class Loader when the image was
     * downloaded.
     */
    void finishedDownload();

Q_SIGNALS:
    /**
     * @brief Sends a signal when the method addMore() is
     * clicked.
     */
    void addClicked();

protected:    
    /**
     * @brief Monitor close app events.
     *
     * @param event - Some events.
     */
    virtual void closeEvent(QCloseEvent *event);

    /**
     * @brief pictureFlow
     */
    void pictureFlow();

    /**
     * @brief Set background image in windown.
     *
     * @param img - Image path.
     * @param pix - Image pixmap.
     */
    void setBackgroundImage(const QString &img, const QPixmap &pix);

private:
    /// The interface design of this class.
    Ui::ListItemDetails *ui;

    /// The XML Rpc Client.
    XmlRpcClient* m_xmlrpc;

    /// The id food, drinks, wine, etc.
    int m_id;

    /// Store count picture flow.
    unsigned int m_countpictureflow;

    /// Store image picture flow.
    QString m_imagepictureflow;

    /// Check type form.
    unsigned int m_typeform;
};

#endif // LISTITEMDETAILS_H
