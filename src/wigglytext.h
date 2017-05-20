/**
 * @file wigglytext.h
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

#ifndef WIGGLYTEXT_H
#define WIGGLYTEXT_H

#include <QBasicTimer>
#include <QWidget>

/**
 * @brief Makes a text with grace, let him dancing. :-)
 */
class WigglyText : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    WigglyText(QWidget *parent = 0);

    /// Destructor.
    ~WigglyText();

public slots:
    /**
     * @brief The text that we do cute.
     *
     * @param newText - The text.
     */
    void setText(const QString &newText) {
        m_text = newText;
    }

protected:
    /**
     * @brief Monitor paint event in widget.
     *
     * @param event - Some events.
     */
    virtual void paintEvent(QPaintEvent *event);

    /**
     * @brief Monitor timer event in widget.
     *
     * @param event - Some
     */
    virtual void timerEvent(QTimerEvent *event);

private:
    /// Store timer.
    QBasicTimer m_timer;

    /// Store the text.
    QString m_text;

    /// Store step timer.
    int m_step;
};

#endif
