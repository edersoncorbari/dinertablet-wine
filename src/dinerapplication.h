/**
 * @file dinerapplication.h
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

#ifndef DINERAPPLICATION_H
#define DINERAPPLICATION_H

#include <QApplication>
#include <QEvent>
#include <QObject>
#include <QTimer>

/**
 * @brief Reimplementation of Qt Application class.
 *
 * @see IDLE Application: http://blog.surgeons.org.uk/2010/08/detecting-application-idle-in-qt-4.html
 */
class DinerApplication : public QApplication
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param argc - Command line arguments count.
     * @param argv - Command line arguments string.
     */
    DinerApplication(int argc, char* argv[]);

    /// Virtual destructor.
    virtual ~DinerApplication();

    /**
     * @brief The inactivity of the system when the user is
     * not using the app.
     *
     * @param time - The time in milliseconds to call idle.
     */
    void setUserIdle(int time = 0);

    /**
     * @brief Used to open the widget on the center screen.
     *
     * @param width - The width of the widget.
     * @param height - The height of the widget.
     * @param screenWidth - The width of the parent widget.
     * @param screenHeight - The height of the parent widget.
     */
    static void calcCenter(int width = 0, int height = 0,
                           int screenWidth = 0, int screenHeight = 0);

    /**
     * @brief After calling calcCenter() method, we can print
     * the retrieved values​​.
     *
     * @return The calculated values.
     */
    static QMap<QString, int> printCalcCenter();

    /**
     * @brief Print the path where the configuration file should
     * be written and read.
     *
     * @return The full path and directory.
     */
    static QString printPathDirConfig();

    /**
     * @brief Print current list files.
     */
    static void printListFiles();

signals:
    /**
     * @brief Signal triggered when the idle is called.
     */
    void idleCalled();

private slots:
    /**
     * @brief Stop the timer idle and call signal idleCalled().
     */
    void idle();

protected:
    /**
     * @brief Application notify.
     *
     * @param receiver - The object receiver.
     * @param event - The event.
     * @return The object application notify.
     */
    virtual bool notify(QObject *receiver, QEvent *event);

    /**
     * @brief Print the path where the configuration file should
     * be written and read iOS7.
     *
     * @return The full path and directory.
     */
    static QString printPathDirIos7();

    /**
     * @brief Print the path where the configuration file should
     * be written and read iOS8.
     *
     * @return The full path and directory.
     */
    static QString printPathDirIos8();

private:
    /// The timer idle.
    QTimer m_timer;

    /// Store values mapcenter widget.
    static QMap<QString, int> m_mapcenter;
};

#endif // DINERAPPLICATION_H
