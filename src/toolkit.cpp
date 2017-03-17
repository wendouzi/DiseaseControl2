#include "toolkit.h"
#include <QFileInfo>
#include <QDateTime>
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
}
