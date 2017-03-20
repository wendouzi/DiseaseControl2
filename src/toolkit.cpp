#include "toolkit.h"
#include <QFileInfo>
#include <QDateTime>
#include <QString>
#include <QStringList>
namespace ToolKit {
uint getFilesHash(const QString & filePath) {
    QFileInfo fileInfo(filePath);
    uint hash = 0;
    if(fileInfo.exists()){
        hash = qHash(filePath) + qHash(fileInfo.size())+qHash(fileInfo.created().toTime_t())
                + qHash(fileInfo.lastModified().toTime_t());
    }
    return hash;
}

QStringList getFilesExist(const QStringList &list)
{
    QStringList fileList;
    QFileInfo fileInfo;
    QString fileName;
    for (int size = list.size(), i = 0; i < size; ++i) {
        fileName = list.at(i);
        fileInfo.setFile(fileName);
        if(fileInfo.isFile())//no directory
            fileList.append(fileName);  //! fileInfo.absolutePath()??
    }
    return fileList;
}

}
