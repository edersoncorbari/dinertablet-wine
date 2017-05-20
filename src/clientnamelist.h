/**
 * @file clientnamelist.h
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

#ifndef CLIENTNAMELIST_H
#define CLIENTNAMELIST_H

#include <QWidget>

// Override.
namespace Ui {
class ClientNameList;
}

// Override.
class MainWidget;

/**
 * @brief When user clicks to add another account, and
 * put the person's name.
 */
class ClientNameList : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit ClientNameList(QWidget *parent = 0);

    /// Destructor.
    ~ClientNameList();

    /**
     * @brief Print the short name.
     *
     * @return The name.
     */
    static QString printShortName();

private Q_SLOTS:
    /**
     * @brief Cancel and close form.
     */
    void cancel();

    /**
     * @brief Add text in list the @class MainWidget.
     */
    void addList();

    /**
     * @brief Slot called by LineEdit when the text is changed.
     * @param text - The text typed in LineEdit.
     */
    void textChanged(const QString &text);

private:
    /// The interface design of this class.
    Ui::ClientNameList *ui;

    /// The pointer @class MainWidget.
    MainWidget *m_mainwidget;

    /// String store shortname.
    static QString m_shortname;
};

#endif // CLIENTNAMELIST_H
