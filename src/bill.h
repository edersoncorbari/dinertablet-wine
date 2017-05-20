/**
 * @file bill.h
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

#ifndef BILL_H
#define BILL_H

#include <QtWidgets>

// Override.
namespace Ui {
class Bill;
}

// Override.
class XmlRpcClient;

/**
 * @brief Does closing the bill (check).
 */
class Bill : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit Bill(QWidget *parent = 0);

    /// Destructor.
    ~Bill();

    /**
     * @brief Start and show List Foods.
     * @param id - The id food.
     */
    void startListFoods(int id = 0);

    /**
     * @brief Set background image in windown.
     *
     * @param img - Image path.
     * @param pix - Image pixmap.
     */
    void setBackgroundImage(const QString &img, const QPixmap &pix);

    /**
     * @brief Print Total.
     * @return Value total.
     */
    static double printTotal();

private Q_SLOTS:
    /**
     * @brief Calls the slot method when an error occurs
     * in the RPC Server.
     */
    //void xmlRpcError();

    /**
     * @brief Call method to get the dishes
     * RPC Server.
     */
    //void xmlRpcCallDishes();

    void localCallDishes();

    /**
     * @brief Cancel and close form.
     */
    void cancel();

protected:
    /**
     * @brief orderNow
     */
    //void orderNow();

private:
    /// The interface design of this class.
    Ui::Bill *ui;

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
        //QButtonGroup* groupbuttonremove; //!< Group buttons list remove.
        //QButtonGroup* groupbuttonadd; //!< Group buttons list add.
    };

    /// Object foods.
    foods m_foods;

    /// The id foods.
    int m_idfood;

    /// Store amount items.
    static QVariantList m_listcalc;
};

#endif // BILL_H
