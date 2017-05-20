/**
 * @file bill.cpp
 *
 * Implementations for an diner-tablet.
 *
 * MOBILE-APP - Project DinerTablet.
 *
 * Copyright (c) 2014 BlueSalute Company Ltda.
 *
 * @author Ederson Moura - <ederson.moura@bluesalute.com.br>
 *
 * $Id: Exp$
 */

#include "bill.h"
#include "ui_bill.h"
#include "xmlrpcclient.h"
#include "mainwidget.h"
#include "loader.h"
#include "printout.h"

// Start static variables and objects.
QVariantList Bill::m_listcalc = QVariantList();

Bill::Bill(QWidget *parent) :
    QWidget(parent), ui(new Ui::Bill)
{
    // Clean list.
    Bill::m_listcalc.clear();

    // Call ui interface.
    ui->setupUi(this);

    // Set font label message.
    QFont fontLB("Great Vibes", 35, QFont::Bold);
    ui->labelBill->setFont(fontLB);
    ui->labelBill->setStyleSheet("QLabel { background-color : transparent; "
                             "color : white; }");
    ui->labelBill->setText(QObject::tr("  Request the bill"));

    // Set read only.
    this->ui->textBrowser->setReadOnly(true);

    // Set name tab.
    ui->tabWidget->setTabText(0, QObject::tr("Order") + " N" +
                              QString::number(MainWidget::printNumberOrder()));

    //QWidget *tab = new QWidget();
    //tab->setObjectName(QStringLiteral("tab"));
    //ui->tabWidget->addTab(tab, QString());

    this->startListFoods(MainWidget::printNumberOrder());

    // Signals and slots.
    QObject::connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

Bill::~Bill()
{
    delete ui;
}

void Bill::cancel()
{
    //this->m_mainwidget->disableObjects(false);
    this->close();
}

void Bill::startListFoods(int id)
{

    // Set names store data.
    m_foods.filename = "billdatafoods-" + QString::number(MainWidget::printNumberOrder());
    m_foods.filenameids = "billdatafoodsids-" + QString::number(MainWidget::printNumberOrder());
    m_foods.filenamespin = "billdatafoodsspins-" + QString::number(MainWidget::printNumberOrder());

    m_idfood = id;

    localCallDishes();
}

void Bill::localCallDishes()
{
    // Extract data id foods in file.
    m_foods.id.append(Loader::serializeExtractData(m_foods.filenameids));

    // Avoids duplicate item!
    if(!m_foods.id.contains(this->m_idfood)) {

        // Store id food list.
        m_foods.id.append(this->m_idfood);
    }

    // Extract data foods in file.
    m_foods.datalocal.append(Loader::serializeExtractData(m_foods.filename));

    // Extract data spin map values.
    m_foods.mapspins = Loader::serializeExtractDataMap(m_foods.filenamespin);

    //qDebug() << m_foods.datalocal;
    //qDebug() << m_foods.mapspins;
    //qDebug() << m_foods.id;

    QStringList html;

    for(int i = 0; i < m_foods.datalocal.size(); ++i) {
        QString name = QString();
        QString price = QString();
        const int identify = m_foods.datalocal[i].toMap().value("cd_prato").toInt();
        const int active = m_foods.datalocal[i].toMap().value("ativo").toInt();

        if(active == 1) {
            // Check language.
            if(MainWidget::printLanguage() == "en_US") {
                name = m_foods.datalocal[i].toMap().value("nome_en").toString();
            } else if(MainWidget::printLanguage() == "pt_BR") {
                name = m_foods.datalocal[i].toMap().value("nome_br").toString();
            } else if(MainWidget::printLanguage() == "es") {
                name = m_foods.datalocal[i].toMap().value("nome_es").toString();
            }

            unsigned int amount = 0;

            QMap<int, int>::iterator im;
            for(im = m_foods.mapspins.begin(); im != m_foods.mapspins.end(); ++im) {
                if(im.key() == identify) {
                    amount = im.value();
                    break;
                }
            }

            // Check amount.
            if(amount == 0 | amount == 1) {
                amount = 1;
            }

            // Set price.
            price = "R$ " + m_foods.datalocal[i].toMap().value("preco").toString();

            // Multiply without having more than one item.
           if(amount >= 2) {
               double pricemulti = m_foods.datalocal[i].toMap().value("preco").toDouble() * amount;
               price = "R$ " + QString::number(pricemulti, 'd', 2);
           }

           // Replace R$ and add in list.
           const QString pricerep = price.replace("R$ ", "");
           Bill::m_listcalc.append(pricerep);

           // Set HTML.
           QString str = ("<tr>\n"
                          "<td align=\"center\">" + QString::number(amount) + "</td>\n"
                          "<td align=\"center\">" + name + "</td>\n"
                          "<td align=\"center\">" + price + "</td>\n"
                          "</tr>\n");
           html.append(str);
        }
    }

    // Set and print total.
    Bill::printTotal();

    // Create html to view.
    PrintOut::getInstance()->createHtmlToView(html, "FECHAMENTO");

    // Print html.
    ui->textBrowser->setHtml(PrintOut::getInstance()->printHtml());
}

double Bill::printTotal()
{
    double calc = 0.0;

    for(int i = 0; i < Bill::m_listcalc.size(); ++i) {
        calc = calc + Bill::m_listcalc[i].toDouble();
    }

    return calc;
}

void Bill::setBackgroundImage(const QString &img, const QPixmap &pix)
{
    // Using QPalette you can set background image as follows.
    QPalette p = palette();

    // Load image to QPixmap, Give full path of image.
    QPixmap pixmap1;
    if(!img.isEmpty()) {
        pixmap1 = img;
    } else {
        pixmap1 = pix;
    }

    // Resize image if it is larger than screen size.
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect rect = desktopWidget->availableGeometry();

    QSize size(rect.width(), rect.height());

    // Resize as per your requirement..
    QPixmap pixmap(pixmap1.scaled(size));

    p.setBrush(QPalette::Background,  pixmap);
    this->setPalette(p);
}
