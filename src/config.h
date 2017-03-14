#ifndef CONFIG_H
#define CONFIG_H

class QPointF;
class QString;
class QSize;
class Config
{
public:
    Config();
    ~Config();
    const static QPointF OriginPoint;
    const static QString DefaultBgColor;
    const static QSize WindowFitSize;
};

#endif // CONFIG_H
