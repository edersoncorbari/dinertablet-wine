/**
 * @file listitemwinedetails.h
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

#ifndef LISTITEMWINEDETAILS_H
#define LISTITEMWINEDETAILS_H

#include <QtWidgets>

// Override.
namespace Ui {
class ListItemWineDetails;
}

// Override.
class XmlRpcClient;

/**
 * @brief Shows all the details of the wine.
 */
class ListItemWineDetails : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit ListItemWineDetails(QWidget *parent = 0);

    /// Destructor.
    ~ListItemWineDetails();

    /**
     * @brief Start and show details Wine.
     * @param id - The id wine.
     */
    void startDetailsWine(int id = 0);

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
     * @brief Call method to get detail wine
     * RPC Server.
     */
    void xmlRpcCallDetailWine();

    /**
     * @brief Call method to get photos in
     * RPC Server.
     */
    void xmlRpcCallPhotos();    

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
     * @brief Set background image in windown.
     *
     * @param img - Image path.
     * @param pix - Image pixmap.
     */
    void setBackgroundImage(const QString &img, const QPixmap &pix);

private:
    /// The interface design of this class.
    Ui::ListItemWineDetails *ui;

    /// The XML Rpc Client.
    XmlRpcClient* m_xmlrpc;

    /// The id wine.
    int m_id;

    /// Store name wine photo.
    QString m_photo;
};

#endif // LISTITEMWINEDETAILS_H
