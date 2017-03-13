#ifndef CONFIG_H
#define CONFIG_H

class QPointF;
class QString;
class Config
{
public:
    Config();
    ~Config();
    const static QPointF OriginPoint;
    const static QString DefaultBgColor;
};

#endif // CONFIG_H
