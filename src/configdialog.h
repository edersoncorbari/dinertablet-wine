/**
 * @file configdialog.h
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

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QWidget>

// Override!
QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

// Override!
class ConfigDialogConn;
class MainWidget;

/**
 * @brief Used to make the local configuration of the tablet.
 */
class ConfigDialog : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit ConfigDialog(QWidget *parent = 0);

    /// Destructor.
    ~ConfigDialog();

public Q_SLOTS:
    /**
     * @brief Slot called by QListWidget when the widget is changed.
     *
     * @param current - The widget current.
     * @param previous - The widget next.
     */
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private Q_SLOTS:
    /**
     * @brief Save config file.
     */
    void save();

    /**
     * @brief Show message afeter save.
     */
    void saveMsg();

    /**
     * @brief Cancel and close widget.
     */
    void cancel();

    /**
     * @brief Cancel Message Box.
     */
    void cancelMsg();

protected:
    /**
     * @brief Create the icon configuration in listwidget.
     */
    void createIcons();

private:
    /// The pointer @class ConfigDialogConn.
    ConfigDialogConn *m_configdialogconn;

    /// The pointer list widgets.
    QListWidget *m_contentswidget;

    /// The pointer pages widgets.
    QStackedWidget *m_pageswidget;

    /// Cancel button.
    QPushButton *m_cancelbt;

    /// Save button.
    QPushButton *m_savebt;

    /// The pointer @class MainWidget.
    MainWidget *m_mainwidget;
};

#endif // CONFIGDIALOG_H
