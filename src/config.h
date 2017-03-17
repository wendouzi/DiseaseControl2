#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QVariant>
#include <QObject>
#include <QSettings>
class QPointF;
class QSize;
class Config:public QObject
{
    Q_OBJECT
private:
    // for release the resouce of Config;
    class Garbage{
        ~Garbage(){
            if(instance())
                delete Config::sInstance;
        }
    };
    static Garbage garbage;
public:
    Config(const Config &);
    Config & operator = (const Config &);
    const static QPointF OriginPoint;
    const static QString DefaultBgColor;
    const static QSize WindowFitSize;
    const static int CacheNumber;
    static QString supportFormats() { return instance()->mFormats; }
    static Config * instance();
    static QByteArray lastGeometry() { return instance()->mLastGeometry;}
    static void insertConfigWatcher(QObject * receiver, const char * method);
    static void cancelConfigWatcher(QObject * receiver, const char * method);
    static void setLastGeometry(const QByteArray & geometry);

signals:
    void configChanged();
private:
    Config();
    void initConfigValue();
    static void setValue(const QString &key, const QVariant &value);
    static QString ConfigFilePath() ;

    static Config* sInstance;
    QStringList mFormatsLst;
    QString mFormats;
    QByteArray mLastGeometry;
};

inline Config * Config::instance() {
    if(!sInstance)
        sInstance = new Config();
    return sInstance;
}

inline void Config::setValue(const QString &key, const QVariant &value){
    QSettings settings(ConfigFilePath(),QSettings::IniFormat);
    settings.setValue(key,value);
}

#endif // CONFIG_H
