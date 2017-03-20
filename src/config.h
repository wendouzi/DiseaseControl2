#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QVariant>
#include <QObject>
#include <QSettings>
#include <QDir>

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
    enum ScaleMode {
        ScaleModeBegin = 0,

        ScaleLargeImageToFitWidget = 0,
        KeepImageSize,
        FitWidgetWidth,
        FitWidgetHeight,
        ScaleToFitWidget,
        ScaleToExpandWidget,

        ScaleModeEnd = ScaleToExpandWidget
    };

    enum AlignMode {
        AlignModeBegin = 0,

        AlignLeftTop = 0,
        AlignCenterTop,
        AlignRightTop,
        AlignLeftCenter,
        AlignCenterCenter,
        AlignRightCenter,
        AlignLeftBottom,
        AlignCenterBottom,
        AlignRightBottom,

        AlignModeEnd = AlignRightBottom
    };

    enum AntialiasMode {
        AntialiasModeBegin = 0,

        AntialiasWhenZoomIn = 0,
        AlwaysAntialias,
        NoAntialias,

        AntialiasModeEnd = NoAntialias
    };
    const static int   ClickInterval;
    const static int   ClickThreshold;
    const static int   AutoScrollInterval;
    const static int   FileSizePrecision;
    const static qreal ScaleMinLimit;
    const static qreal ScaleMaxLimit;
    const static QDir::SortFlags DefaultDirSortFlag;

    const static QRect AutoFilesViewGeometry;

    const static ScaleMode DefaultScaleMode = ScaleLargeImageToFitWidget;
    const static AlignMode DefaultAlignMode = AlignCenterCenter;
    const static AntialiasMode DefaultAntialiasMode = AntialiasWhenZoomIn;

    Config(const Config &);
    Config & operator = (const Config &);
    const static QPointF OriginPoint;
    const static QSize SizeAdjusted;
    const static QString DefaultBgColor;
    const static QSize WindowFitSize;
    const static QSize WindowMinSize;
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
