/**
 * @file login.h
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

#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

// Override.
namespace Ui {
class Login;
}

// Override.
class MainWidget;

/**
 * @brief Login is required to close the app and change
 * the administrative configurations.
 */
class Login : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit Login(QWidget *parent = 0);

    /// Destructor.
    ~Login();

    /**
     * @brief Case login is set to true, after entering the
     * credentials the application is closed.
     *
     * @param type - Case set true close app.
     */
    void setLoginClose(bool type = false);

    /**
     * @brief Check login close or not.
     *
     * @return Returns true or false as defined in setLoginClose method.
     */
    static bool loginCloseApp();

private Q_SLOTS:
    /**
     * @brief Check if this is a valid login.
     */
    void checkLogin();

    /**
     * @brief Cancel and close widget.
     */
    void cancel();

protected:
    /**
     * @brief Reading the configuration file of the tablet.
     */
    void readSettings();

private:
    /// The interface design of this class.
    Ui::Login *ui;

    /// The pointer @class MainWidget.
    MainWidget *m_mainwidget;

    /// Login close app or not.
    bool m_LoginClose;

    /// Enable default login or not.
    bool m_enableDefaultLogin;

    /// Store login.
    QString m_loginUserName;

    /// Store password.
    QString m_loginPassword;

    /// Login close app or not (static).
    static bool m_loginCloseApp;
};

#endif // LOGIN_H
