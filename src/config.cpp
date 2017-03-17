#include "config.h"
#include <QPointF>
#include <QString>
#include <QFileSystemWatcher>
#include <QSize>
#include <QCoreApplication>
#include <QObject>
#include <QImageReader>
const QPointF Config::OriginPoint(0.0, 0.0);
const QSize Config::WindowFitSize(800, 500);

const QString ConfigFileName = "DCD.ini";
const QString GeometryKey = "geometry";


const int Config::CacheNumber = 10;
const QString Config::DefaultBgColor = "#C7EDCC";
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


