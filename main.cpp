#include "mainwindow.h"

#include <QApplication>
#include"unzipzy.h"
#include<QDebug>

#include<windows.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UnZipZy zzz;
   zzz.zipFile_("C:\\Users\\22413\\Desktop\\34.zip","C:\\Users\\22413\\Desktop\\6c35ca9cgy1hr1wtprjkbj21hc1z449d.jpg","1234");
  // zzz.extractAllFiles("C:\\Users\\22413\\Desktop\\33.zip","1234","C:\\Users\\22413\\Desktop");
    MainWindow w;
    w.show();
    return a.exec();
}
