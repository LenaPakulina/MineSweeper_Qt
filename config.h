#ifndef CONFIG_H
#define CONFIG_H

class Config
{
public:
	Config();
	~Config();

	int		m_width;
	int		m_height;
	int		m_mineCount;
};

extern Config	g_cfg;

#endif // CONFIG_H
