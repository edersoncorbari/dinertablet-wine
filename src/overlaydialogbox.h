/**
 * @file overlaydialogbox.h
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

#ifndef OVERLAYDIALOGBOX_H
#define OVERLAYDIALOGBOX_H

#include <QtWidgets>

// Override.
namespace Ui {
class OverlayDialogBox;
}

/**
 * @brief To show the system message box in application.
 *
 * In iOS system is no problem with transparency with QMessageBox alerts
 * then this class is designed to circumvent this problem.
 */
class OverlayDialogBox : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     * @param text - The text message.
     * @param confirm - If true, show message mode confimation.
     */
    explicit OverlayDialogBox(QWidget *parent = 0, const QString &text = QString(""),
                              bool confirm = false);

    /// Destructor.
    ~OverlayDialogBox();

    /**
     * Used for confirmation messages.
     *
     * @return True if clicked in button Yes.
     */
    bool ok();

private slots:
    /**
     * @brief Cancel and close form.
     */
    void cancel();

    /**
     * @brief Click button OK, simple close form.
     */
    void yes();

Q_SIGNALS:
    /**
     * @brief Accepted.
     */
    void accepted();

    /**
     * @brief Button OK is cliked.
     */
    void okClicked();

    /**
     * @brief Button cancel is clicked.
     */
    void cancelClicked();

protected:
    /**
     * @brief Monitor close app events.
     *
     * @param event - Some events.
     */
    virtual void closeEvent(QCloseEvent *event);

private:
    /// The interface design of this class.
    Ui::OverlayDialogBox *ui;

    /// True or false to the confirmation message.
    bool m_confirm;
};

#endif // OVERLAYDIALOGBOX_H
