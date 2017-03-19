#include "config.h"
#include <QPointF>
#include <QString>
#include <QFileSystemWatcher>
#include <QSize>
#include <QCoreApplication>
#include <QObject>
#include <QImageReader>
#include <QDir>
const QPointF Config::OriginPoint(0.0, 0.0);
const QSize Config::WindowFitSize(800, 500);
const QSize Config::WindowMinSize(280, 200);
const int Config::ClickInterval = 1500;
const int Config::ClickThreshold = 30;
const int Config::AutoScrollInterval = 20;
const int Config::FileSizePrecision = 2;
const QSize Config::SizeAdjusted(0, 1);
const qreal Config::ScaleMinLimit = 0.1;
const qreal Config::ScaleMaxLimit = 20;
const QString ConfigFileName = "DCD.ini";
const QString GeometryKey = "geometry";

const bool DefaultShowDialog = true;
const bool DefaultEnableBgColor = true;
const bool DefaultAutoRotateImage = true;
const int  DefaultTimerInterval = 4;
const int  TimerIntervalMinLimit = 1;
const int  TimerIntervalMaxLimit = 1000;

const int Config::CacheNumber = 10;
const QString Config::DefaultBgColor = "#C7EDCC";
const QDir::SortFlags Config::DefaultDirSortFlag = QDir::LocaleAware;//QDir::Name | QDir::IgnoreCase;
Config * Config::sInstance = NULL;
Config::Config():QObject(qApp)
{
    initConfigValue();
    QList<QByteArray> list = QImageReader::supportedImageFormats();
    for(int i=0; i < list.size(); ++i)
        mFormatsLst.append(list.at(i));
    mFormats = mFormatsLst.join(" *.");
    mFormats.prepend("*.");
}
void Config::setLastGeometry(const QByteArray & geometry){
    setValue(GeometryKey,geometry);
}

QString Config::ConfigFilePath(){
    if(!qApp) {
        qDebug("qApp is Null");
    }
    return qApp->applicationDirPath() + '/' + ConfigFileName;
}

void Config::initConfigValue(){
    qDebug("initConfigValue");
    QSettings settings(ConfigFilePath(),QSettings::IniFormat);
    mLastGeometry = settings.value(GeometryKey).toByteArray();
    emit configChanged();
}

void Config::insertConfigWatcher(QObject * receiver, const char * method){
    QObject::connect(instance(),SIGNAL(configChanged()),receiver, method);
}

void Config::cancelConfigWatcher(QObject * receiver, const char * method){
    QObject::disconnect(instance(),SIGNAL(configChanged()),receiver, method);
}


