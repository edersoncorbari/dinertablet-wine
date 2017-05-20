/**
 * @file filedownloader.h
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

#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

/**
 * @brief This class downloads a file to a http web server.
 */
class FileDownloader : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param imageUrl - Full url to download.
     * @param parent - The object.
     */
    explicit FileDownloader(QUrl imageUrl, QObject *parent = 0);

    /// Virtual desctructor.
    virtual ~FileDownloader();

    /**
     * @brief The downloaded data.
     *
     * @return The file data.
     */
    QByteArray downloadedData() const;

signals:
    /**
     * @brief The signal is triggered when the download
     * finishes.
     */
    void downloaded();

private slots:
    /**
     * @brief File download process.
     * @param reply - The requests.
     */
    void fileDownloaded(QNetworkReply* reply);

private:
    /// The network objects.
    QNetworkAccessManager m_webctrl;

    /// File byte array download.
    QByteArray m_download;

};

#endif // FILEDOWNLOADER_H
