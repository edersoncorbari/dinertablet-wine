/**
 * @file mainwidget.h
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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets>

// Override!
namespace Ui {
class MainWidget;
}

// Override!
class AdvertisingNews;
class Login;
class ConfigDialog;

/**
 * @brief The base class of the app DinerTablet.
 */
class MainWidget : public QWidget
{
    Q_OBJECT

    /// Must be your friend.
    friend class ClientNameList;

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit MainWidget(QWidget *parent = 0);

    /// Destructor.
    virtual ~MainWidget();

    /**
     * @brief Singleton MainWidget class get instance.
     *
     * @return The static MainWiget.
     */
    static MainWidget* getInstance();

    /**
     * @brief Check configurations and others stuff.
     */
    void startCheck();

    /**
     * @brief Print the size geometry window.
     * @return Size geometry widget.
     */
    QSize printSize();

    /**
     * @brief Print the name image background.
     * @return Path name the image.
     */
    static QString printBackgroundImage();

    /**
     * @brief Set a default ListWidget.
     */
    void setListWidget();

    /**
     * @brief Disable or enable objects form.
     * @param disable - True disable objects, false enable.
     */
    void disableObjects(bool disable = false);

    /**
     * @brief Show object listWidget or not.
     *
     * @param show - If true show object else hide.
     */
    void showObjectListWidget(bool show = false);

    /**
     * @brief Print the current number order.
     * @return Current number order.
     */
    static int printNumberOrder();

    /**
     * @brief Enable separate orders, returns according
     * to the configuration file of the tablet.
     *
     * @return Returns true if it is enabled otherwise false.
     */
    static bool enableSeparateOrder();

    /**
     * @brief Print language selected in app.
     * @return Name current language.
     */
    static QString printLanguage();

protected:
    /**
     * @brief Monitor change event in widget, eg language change.
     *
     * @param event - Some events.
     */
    virtual void changeEvent(QEvent *event);

    /**
     * @brief Monitor close app events.
     *
     * @param event - Some events.
     */
    virtual void closeEvent(QCloseEvent *event);

    /**
     * @brief Monitor resize events in widget.
     *
     * @param event - Some events.
     */
    virtual void resizeEvent(QResizeEvent *event);

    /**
     * @brief Reading the configuration file of the tablet.
     *
     * @param conf - The name config file.
     */
    void readSettings(const QString &conf);

    /**
     * @brief Set background image in windown.
     *
     * @param img - Image path.
     * @param pix - Image pixmap.
     */
    void setBackgroundImage(const QString &img, const QPixmap &pix);

    /**
     * @brief Change app language. Look at the dir translations.
     *
     * @param language - The language, eg pt_BR, en, etc.
     */
    void changeLanguageTo(const QString &language);

    /**
     * @brief Status button. Green is good, red we have problems!
     *
     * @param status - Set red or green button.
     */
    void tabletButtonStatus(bool status = false);

    /**
     * @brief Add item in my list widget.
     *
     * @param identify - Put a number to each item.
     * @param texticon - Path icon.
     */
    void addItemListView(int identify = 0, const QString texticon = QString());

    /**
     * @brief Animating a bit some objects from widget.
     */
    void animatewidgets();

    /// Pointer class for singleton instance.
    static MainWidget *instance;

public Q_SLOTS:
    /**
     * @brief In case the error, call dialog msg.
     */
    void callMsgErrorDinerServer();

    /**
     * @brief Call advertising news (idle).
     */
    void callAdvertisingNews();

    /**
     * @brief Call dialog the change configuration app.
     */
    void changeAppConfiguration();

    /**
     * @brief Print message not implemented method.
     */
    void printMsgNotImplemented();

    /// Used for tests.
    void test();

private Q_SLOTS:
    /**
     * @brief Change the language to Portuguese.
     */
    void changeLanguageToPortugueseBR();

    /**
     * @brief Change the language to English.
     */
    void changeLanguageToEnglishUS();

    /**
     * @brief Change the language to Spanish.
     */
    void changeLanguageToSpanish();

    /**
     * @brief Sets the image of the menu button, which were
     * downloaded from the server and are in the images directory.
     */
    void setDownloadButtonMenuImage();

    /**
     * @brief Check Login.
     */
    void checkLogin();

    /**
     * @brief Check Login Close Application.
     */
    void checkLoginClose();

    /**
     * @brief Call widget menu.
     */
    void menu();

    /**
     * @brief adds one more item on my list.
     */
    void addItemList();

    /**
     * @brief Check my bill.
     */
    void checkMyBill();

    /**
     * @brief adds one more item on my list.
     */
    void removeItemList();

    /**
     * @brief Called when the user clicks on the list.
     *
     * @param item - Item clicked.
     */
    void itemClicked(QListWidgetItem *item);

    /**
     * @brief Called when a list item is changed.
     *
     * @param item - Item changed.
     */
    void itemChanged(QListWidgetItem *item);

    /**
     * @brief Before inserting an object in the list, you
     * can put a name on it.
     */
    void setClientNameList();

    /**
     * @brief Close widget Advertising News.
     */
    void closeAdvertisingNews();

private:
    /// The interface design of this class.
    Ui::MainWidget *ui;

    /// When the language is changed.
    QTranslator *m_translator;

    /// Used when change the configuration.
    ConfigDialog *m_confdialog;

    /// Login is used to close the app or change config.
    Login *m_login;

    /// The class Advertising News.
    AdvertisingNews* m_advertisingnews;

    /// Store the geometry size in widget.
    QSize m_size;

    /// Control number order used in item list.
    static int m_numberorder;

    /// Store name background image.
    static QString m_backgroundimage;

    /// Store the name language selected.
    static QString m_language;

    /// Store if enabled order separates.
    static bool m_enableseparateorders;
};

#endif // MAINWIDGET_H
