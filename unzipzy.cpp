#include "unzipzy.h"
#include"mainwindow.h"
#include"minizip/unzip.h"
#include <minizip/zip.h>
#include<thread>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include<QDebug>
#include <direct.h>
#include <iostream>
#include <fstream>
#include"utils.h"

UnZipZy::UnZipZy()
{

}
bool UnZipZy::voilent_dezip(const std::string& path,const std::string password){

    unzFile zipFile = unzOpen(path.c_str());
    if (unzOpenCurrentFilePassword(zipFile, password.c_str()) == UNZ_OK) {

         unzClose(zipFile);
         return true;
     }
    return false;
}

bool UnZipZy::worker(std::vector<MainWindow::Grade>&grades,int charactor_numbers){

}
int UnZipZy::extractAllFiles(const char *zipFilePath, const char *password, const char *outputDir) {
    // 打开 ZIP 文件
    unzFile zipFile = unzOpen(zipFilePath);
    if (zipFile == NULL) {
        qDebug()<<"无法打开 ZIP 文件: %s\n"<< zipFilePath;

        return -1;
    }

    // 遍历 ZIP 文件中的所有文件
    int err = unzGoToFirstFile(zipFile);
    while (err == UNZ_OK) {
        char filename[256];
        unz_file_info fileInfo;

        // 获取当前文件的文件名
        unzGetCurrentFileInfo(zipFile, &fileInfo, filename, sizeof(filename), NULL, 0, NULL, 0);

        // 如果 filename 以 '/' 结尾，则表示它是一个目录
        if (filename[strlen(filename) - 1] == '/') {
            // 构建完整的输出目录路径
            char dirPath[512];
            snprintf(dirPath, sizeof(dirPath), "%s/%s", outputDir, filename);

            // 创建目录
            if (createDirectory(dirPath) != 0) {
                qDebug()<<"无法创建目录: %s\n"<< dirPath;
                unzClose(zipFile);
                return -1;
            }
            printf("创建目录: %s\n", dirPath);
        } else {
            // 文件处理部分
            qDebug()<<"正在解压文件: %s\n"<< filename;

            // 尝试使用密码打开文件（如果有密码）
            if (unzOpenCurrentFilePassword(zipFile, password) != UNZ_OK) {
                qDebug()<<"无法打开文件: %s，可能是密码错误。\n" <<filename;
                break;
            }

            // 构建输出文件路径
            char outputPath[512];
            snprintf(outputPath, sizeof(outputPath), "%s/%s", outputDir, filename);

            // 创建父目录结构（如果需要）
            char *lastSlash = strrchr(outputPath, '/');
            if (lastSlash != NULL) {
                *lastSlash = '\0';  // 临时截断路径
                createDirectory(outputPath);
                *lastSlash = '/';  // 恢复路径
            }

            // 打开输出文件

            FILE *outputFile = fopen(Utils::convertToDoubleBackslashes(outputPath), "wb");
            if (outputFile == NULL) {
                qDebug()<<"无法创建输出文件: %s\n"<<outputPath;
                unzCloseCurrentFile(zipFile);
                break;
            }

            // 读取文件内容并写入输出文件
            QSharedPointer<char> buff(new char[8192000]);
            char *buffer=buff.get();
            int bytesRead;
            while ((bytesRead = unzReadCurrentFile(zipFile, buffer, sizeof(buffer))) > 0) {
                fwrite(buffer, 1, bytesRead, outputFile);
            }

            // 关闭输出文件和当前 ZIP 文件条目
            fclose(outputFile);
            unzCloseCurrentFile(zipFile);
        }

        // 移动到下一个文件
        err = unzGoToNextFile(zipFile);
    }

    if (err == UNZ_END_OF_LIST_OF_FILE) {
        qDebug()<<"所有文件已解压完成。\n";
    } else {
        qDebug()<<"解压过程中出现错误。\n";
    }

    // 关闭 ZIP 文件
    unzClose(zipFile);
    return 0;
}
int createDirectory(const char *path) {
    #ifdef _WIN32
        return _mkdir(path);  // Windows 上使用 _mkdir
    #else
        return mkdir(path, 0755);  // UNIX 上使用 mkdir
    #endif
}

void UnZipZy::zipFile_(const char* zipFilePath, const char* fileToZip, const char* password) {
    // 使用不同的变量名，避免与类型冲突
    zipFile zipHandle = zipOpen(zipFilePath, APPEND_STATUS_CREATE);
    if (!zipHandle) {
        std::cerr << "无法创建 ZIP 文件!" << std::endl;
        return;
    }

    // 设置压缩文件的属性
    zip_fileinfo zipFileInfo;
    memset(&zipFileInfo, 0, sizeof(zipFileInfo));

    // 打开要压缩的文件
    std::ifstream file(fileToZip, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << fileToZip << std::endl;
        zipClose(zipHandle, nullptr);
        return;
    }

     // 为压缩文件设置密码
    if (zipOpenNewFileInZip3(zipHandle,
                            Utils::keep_after_last_backslash(fileToZip),
                            &zipFileInfo,
                            nullptr, 0,
                            nullptr, 0,
                            nullptr, Z_DEFLATED,
                            (password != nullptr) ? 9 : 0,
                            0, -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                            password, 0) != ZIP_OK) {
        std::cerr << "无法打开压缩文件!" << std::endl;
        zipClose(zipHandle, nullptr);
        return;
    }
    // 将文件内容写入 ZIP 文件
    char buffer[8192];
    while (file.read(buffer, sizeof(buffer))) {
        zipWriteInFileInZip(zipHandle, buffer, sizeof(buffer));
    }
    zipWriteInFileInZip(zipHandle, buffer, file.gcount()); // 写入剩余数据

    // 关闭压缩文件
    zipCloseFileInZip(zipHandle);
    zipClose(zipHandle, nullptr);
    file.close();

    std::cout << "文件已成功压缩到: " << zipFilePath << std::endl;
}
