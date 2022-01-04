#include "config.h"

#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>
#include <QApplication>
#include <QDir>

Config	g_cfg;

Config::Config()
{
	m_height = 10;
	m_width = 10;
	m_mineCount = 30;
	m_lastLanguage = 0;

	m_saveConfig = false;
}

Config::~Config()
{
}

QString Config::getJsonConfigPath()
{
	QString path = getConfigPath(qApp->applicationName(), "GamesPak");
	path = mpath({path, "settings.json"});
	return path;
}

void Config::save()
{
	if (m_saveConfig == false) {
		return;
	}
	QJsonObject cfg;
	cfg["lastOpenFile"] = m_lastOpenFile;
	cfg["saveConfig"] = m_saveConfig;
	cfg["width"] = QString::number(m_width);
	cfg["height"] = QString::number(m_height);
	cfg["mineCount"] = QString::number(m_mineCount);
	cfg["lastLanguage"] = QString::number(m_lastLanguage);
	cfg["windowGeometry"] = QVariant(m_windowGeometry.toBase64()).toString();

	QJsonDocument doc(cfg);
	QString path = getJsonConfigPath();
	if (path.isEmpty()) {
		return;
	}
	QDir d(QFileInfo(path).absoluteDir());
	if (!d.exists()) {
		d.mkpath(".");
	}
	QFile f(path);
	if (!f.open(QFile::WriteOnly)) {
		return;
	}
	f.write(doc.toJson());
}

void Config::load()
{
	if (m_saveConfig == false) {
		return;
	}

	QString path = getJsonConfigPath();
	QFile f(path);
	if (!f.exists()) {
		return;
	}
	if (!f.open(QFile::ReadOnly)) {
		return;
	}
	QByteArray jsonData = f.readAll();
	if (jsonData.isEmpty()) {
		return;
	}
	QJsonParseError jpe;
	QJsonDocument doc = QJsonDocument::fromJson(jsonData, &jpe);
	if (jpe.error != QJsonParseError::NoError) {
		return;
	}

	// разбор
	QJsonObject obj = doc.object();
	m_windowGeometry = QByteArray::fromBase64(obj["windowGeometry"].toString().toLatin1());
	m_lastOpenFile = obj["lastOpenFile"].toString();
	m_saveConfig = obj["saveConfig"].toBool();
	m_width = obj["width"].toInt();
	m_height = obj["height"].toInt();
	m_mineCount = obj["mineCount"].toInt();
	m_lastLanguage = obj["lastLanguage"].toInt();
}

QString Config::mpath(std::initializer_list<QString> list)
{
	QString result;
	if (list.size() == 0) {
		return result;
	}
	result += *list.begin();
	for (auto it = list.begin() + 1; it != list.end(); it++) {
		result += "/" + *it;
	}
	return result;
}

QString Config::getConfigPath(const QString &appName, const QString &companyName)
{
	QString path = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
	path = mpath({path, companyName});
	path = mpath({path, appName});
	return path;
}
