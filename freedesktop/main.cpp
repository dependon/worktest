#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <QLocale>
#include <QSettings>
#include <QFile>
#include <QProcess>
#include <QDebug>

#include <DDesktopEntry>
#include <QFileInfo>
#include <iostream>
#include <vector>
DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE
using namespace std;

int main(int argc, char *argv[])
{
    QString localPath;
    QVector <QString> vec;
    QMap <QString ,QString >map;
    for(int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-d") == 0){
            if(i+1<argc){
                localPath=argv[i+1];
            }
        }
    }
    QFileInfo file(localPath);
    if(!file.exists()) return -1;
    if( file.suffix()!="desktop"){
        return 1;
    };
    DDesktopEntry desktop(localPath);  //指定需要解析的 desktop 文件名

    for(int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-n") == 0){
            QString name =desktop.name();
            if(!name.isNull()){
                cout <<name.toStdString();
            }else {
                return -1;
            }
        }
        if (strcmp(argv[i], "-i") == 0){
            QString IconPath = desktop.stringValue("Icon");
            if(!IconPath.isNull()){
                cout <<IconPath.toStdString().c_str();
            }else {
                return -1;
            }

        }
        QVector<QString > vector1;
        QString deepinVendor;
        if (strcmp(argv[i], "-e") == 0){
            while((i+1)<argc){
                QString Exec = desktop.stringValue("Exec");
                QFileInfo file(argv[i+1]);
                if(Exec.isNull() ||!Exec.contains("cat"))
                {
                   return -1;
                }
                if(file.isReadable())
                {
                    vector1.push_back(argv[i+1]);
                }else {
                    break;
                }
                i++;
            }
           for(QString str:vector1)
           {
               QProcess p;
               p.start("cat "+str);
               p.waitForFinished();
               std::cout<< p.readAllStandardError().toStdString();
           }
        }
    }



    return 0;
}
