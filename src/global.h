#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QObject>
namespace Global {

const QString Version = "2.0";
const QString CopyRightYear = "2017-";
const QString BuildTime = __TIME__ ", " __DATE__;
const QString AuthorEmail = "735196447@qq.com";

static QString LoadFileErrorInfo();

static inline QString ProjectName(){
    return QObject::tr("CDC");
}

static inline QString ProjectAuthor()
{ return QObject::tr("ShangHai ChenCan Technology Ltd"); }



QString LoadFileErrorInfo(){
    return QObject::tr("Cannot load picture:'%3'" \
                       "\nYou can help to improve %1 by email the picture to %2")
            .arg(ProjectName()).arg(AuthorEmail);
}

static inline QString AboutInfo()
{
    return QObject::tr("<p align='center'>%1 - Chinese Center for Disease Control and Prevention</p>" \
                       "<p>Version: v%2"
                       "<br>Build Time: %3"  \
                       "<br>CopyRight &#169; %4 by %5</p>" \
                       "<br>Send Email: <a href='mailto:%6'>%6</a></p>" )
            .arg(ProjectName()).arg(Version).arg(BuildTime).arg(CopyRightYear)
            .arg(ProjectAuthor()).arg(AuthorEmail);
}


}

#endif // GLOBAL_H
