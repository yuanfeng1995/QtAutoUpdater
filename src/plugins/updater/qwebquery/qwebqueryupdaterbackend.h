#ifndef QWEBQUERYUPDATERBACKEND_H
#define QWEBQUERYUPDATERBACKEND_H

#include <QtCore/QLoggingCategory>
#include <QtCore/QVariant>
#include <QtCore/QJsonValue>

#include <QtAutoUpdaterCore/UpdaterBackend>

#include <QtNetwork/QNetworkAccessManager>

class QWebQueryUpdaterBackend : public QtAutoUpdater::UpdaterBackend
{
	Q_OBJECT

public:
	explicit QWebQueryUpdaterBackend(QString &&key, QObject *parent = nullptr);

	Features features() const override;
	void checkForUpdates() override;
	void abort(bool force) override;
	bool triggerUpdates(const QList<QtAutoUpdater::UpdateInfo> &infos, bool track) override;
	QtAutoUpdater::UpdateInstaller *createInstaller() override;

Q_SIGNALS:
	void abortCheck(QPrivateSignal);

protected:
	bool initialize() override;

private Q_SLOTS:
	void handleReply();
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
	static const QString ParserAuto;
	static const QString ParserVersion;
	static const QString ParserJson;

	QNetworkAccessManager *_nam = nullptr;

	void addStandardQuery(QUrl &url) const;

	void parseResult(QNetworkReply *device);
	void parseJson(QNetworkReply *device);
	void parseVersion(QNetworkReply *device);

	QString requestUrl(QNetworkReply *reply) const;

#if QT_CONFIG(process)
	std::optional<QString> testForProcess() const;
	bool runProcess(const QString &program, const QList<QtAutoUpdater::UpdateInfo> &infos, bool track);
#endif
};

Q_DECLARE_LOGGING_CATEGORY(logWebBackend)

#endif // QWEBQUERYUPDATERBACKEND_H
