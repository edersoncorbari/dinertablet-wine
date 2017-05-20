/**
 * @file advertisingnews.cpp
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

#include "advertisingnews.h"
#include "ui_advertisingnews.h"

AdvertisingNews::AdvertisingNews(QWidget *parent) :
    QWidget(parent), ui(new Ui::AdvertisingNews)
{
    // Call ui interface.
    ui->setupUi(this);

    // Read settings.
    this->readSettings("DinerTabletGlobal.conf");

    // Set background image.
    this->imageBackgroundRandom();

    // Check timer image random.
    if(m_timerandomadsimages >= 5000) {
        QTimer *timer = new QTimer(this);
        timer->start(m_timerandomadsimages);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(imageBackgroundRandom()));
    }

    // Signals and slots.
    QObject::connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

AdvertisingNews::~AdvertisingNews()
{
    delete ui;
}

void AdvertisingNews::closeEvent(QCloseEvent *event)
{
    this->cancel();
    event->accept();
}

void AdvertisingNews::cancel()
{
    this->close();
    //Q_EMIT addClicked();
}

void AdvertisingNews::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    Q_EMIT clicked();
}

void AdvertisingNews::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    Q_EMIT clicked();
}

void AdvertisingNews::readSettings(const QString &conf)
{
    QSettings settings(conf, QSettings::IniFormat);

    settings.beginGroup("AdvertisingNews");

    // Read time random images.
    m_timerandomadsimages = settings.value("timeRandomAdsImages").toInt();

    settings.endGroup();
}

void AdvertisingNews::imageBackgroundRandom()
{
    QList<QString> str_list;
    str_list << "Ads-1.jpg" << "Ads-2.jpg";

    QString str = str_list.at(qrand() % str_list.size());
    //QString setImg = "/Users/edm/workspace/install/tmp/" + str;
    QString setImg = ":/images/" + str;

    // Using QPalette you can set background image as follows.
    QPalette p = palette();

    // Load image to QPixmap, Give full path of image.
    QPixmap pixmap1;
    pixmap1 = setImg;

    // Resize image if it is larger than screen size.
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect rect = desktopWidget->availableGeometry();

    QSize size(rect.width(), rect.height());

    // Resize as per your requirement..
    QPixmap pixmap(pixmap1.scaled(size));

    p.setBrush(QPalette::Background,  pixmap);
    this->setPalette(p);
}
