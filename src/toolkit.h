#ifndef TOOLKIT_H
#define TOOLKIT_H
#include <QString>
#include <QFileInfo>

#define SaftDelete(arg) \
{ \
    if(arg){ \
    ::delete arg; \
    arg = NULL; \
    } \
    }

namespace ToolKit {
inline QString fileName(const QString & filepath){
    return QFileInfo(filepath).fileName();
}
uint getFilesHash(const QString &filePath);
}

#endif // TOOLKIT_H
