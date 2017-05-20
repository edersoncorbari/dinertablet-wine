/**
 * @file menuwinefilter.h
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

#ifndef MENUWINEFILTER_H
#define MENUWINEFILTER_H

#include <QtWidgets>

// Override.
namespace Ui {
class MenuWineFilter;
}

// Override.
class XmlRpcClient;

/**
 * @brief This is the menus wine filter.
 */
class MenuWineFilter : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit MenuWineFilter(QWidget *parent = 0);

    /// Destructor.
    ~MenuWineFilter();

    /**
     * @brief Set background image in windown.
     *
     * @param img - Image path.
     * @param pix - Image pixmap.
     */
    void setBackgroundImage(const QString &img, const QPixmap &pix);

    /**
     * @brief Calls the filter options to (Types of Wine).
     */
    void setFilterType();

    /**
     * @brief Calls the filter options for (Wine Grape).
     */
    void setFilterVarietals();

    /**
     * @brief Calls the filter options for (Wine Countries).
     */
    void setFilterCountries();

    /**
     * @brief Calls the filter options for (Wine Region).
     */
    void setFilterRegion();

    /**
     * @brief Calls the filter options for (Wine Producer).
     */
    void setFilterProducer();

    /**
     * @brief Contains the filter to be passed to the
     * RPC server.
     *
     * @return A query to pass to the RPC server.
     */
    static QString printQueryFilter();

    /**
     * @brief Clean the filter variable.
     */
    static void clearQueryFilter();

    /**
     * @brief Contains the name filter selected.
     */
    static QString printNameFilterSelected();

    /**
     * @brief Clean the name filter variable.
     */
    static void clearNameFilterSelected();

private Q_SLOTS:
    /**
     * @brief Calls the slot method when an error occurs
     * in the RPC Server.
     */
    void xmlRpcError();

    /**
     * @brief Call method to get type wines
     * RPC Server.
     */
    void xmlRpcCallTypeWines();

    /**
     * @brief Called by the group buttons menu to get the (id)
     * number of the button that was clicked.
     *
     * @param buttonid - Button id.
     */
    void buttonMenuWasClicked(int buttonid = 0);

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
     * @brief Cancel and close form.
     */
    void cancel();

Q_SIGNALS:
    /**
     * @brief Sends a signal when the button is
     * clicked.
     */
    void buttonClicked();

protected:
    /**
     * @brief Monitor close app events.
     *
     * @param event - Some events.
     */
    virtual void closeEvent(QCloseEvent *event);

private:
    /// The interface design of this class.
    Ui::MenuWineFilter *ui;

    /// The XML Rpc Client.
    XmlRpcClient* m_xmlrpc;

    /// Group button.
    QButtonGroup* m_groupbutton;

    /// Store list of dynamically created buttons.
    QList<QPushButton*> m_buttonlist;

    /// Store values Server RPC (categories).
    QList<QVariant> m_data;

    /// Store query filters.
    static QString m_paramquery;

    /// Store name filter selected.
    static QString m_namefilter;

    /// The filter types.
    static int m_winefilter;

    /// Store query filter type.
    static QString m_paramquerytype;

    /// Store query filter varietals.
    static QString m_paramqueryvarietals;

    /// Store query filter countries.
    static QString m_paramquerycountries;

    /// Store query filter region.
    static QString m_paramqueryregion;

    /// Store query filter producer.
    static QString m_paramqueryproducer;
};

#endif // MENUWINEFILTER_H
