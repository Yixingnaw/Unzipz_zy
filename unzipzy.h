#ifndef UNZIPZY_H
#define UNZIPZY_H
#include<vector>
#include<mainwindow.h>
#include<string>
class UnZipZy
{
public:
    UnZipZy();
    bool voilent_dezip(const std::string& path,const std::string password);
    bool worker(std::vector<MainWindow::Grade>&grades,int charactor_numbers);

    void zipFile_(const char* zipFilePath, const char* fileToZip, const char* password);
    int extractAllFiles(const char *zipFilePath, const char *password, const char *outputDir);
};

int createDirectory(const char *path);
#endif // UNZIPZY_H
