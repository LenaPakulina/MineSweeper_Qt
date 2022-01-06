#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QTranslator>

class Config
{
public:
	Config();
	~Config();

	int			m_width;
	int			m_height;
	int			m_mineCount;
	int			m_lastLanguage;
	bool		m_saveConfig;
	QString		m_lastOpenFile;
	QByteArray	m_windowGeometry;

public:
	QString		getJsonConfigPath();
	QString		getConfigPath(const QString &appName, const QString &companyName);
	void		save();
	void		load();
	void		changeLanguage();
	bool		checkParams(int width, int height, int mineCount);

private:
	QString		mpath(std::initializer_list<QString> list);

private:
	QTranslator	m_translator;
};

extern Config	g_cfg;

#endif // CONFIG_H
