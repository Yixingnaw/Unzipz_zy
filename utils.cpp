#include "utils.h"
#include <iostream>
#include <cstring>
  char* Utils::convertToDoubleBackslashes(char* path){
    // 计算新字符串需要的长度
       size_t newLength = 0;
       for (const char* p = path; *p; ++p) {
           if (*p == '\\') {
               newLength += 2;  // 每个反斜杠需要两个字符
           } else {
               newLength += 1;
           }
       }

       // 分配新字符串的内存
       char* newPath = new char[newLength + 1];  // +1 是为了末尾的 '\0'
       char* dest = newPath;

       // 转换过程
       while (*path) {
           if (*path == '\\') {
               *dest++ = '\\';
               *dest++ = '\\';
           } else {
               *dest++ = *path;
           }
           path++;
       }

       *dest = '\0';  // 添加字符串结束符

       return newPath;
}
  char* Utils::keep_after_last_backslash(const char *str) {
      char *last_backslash = strrchr(str, '\\');  // 找到最后一个 '\\' 的位置
      char* newdest= (char*) malloc(strlen(str)+1);
      if (last_backslash != NULL) {
          // 将最后一个 '\\' 及其后的部分移到字符串的开头
          memmove(newdest, last_backslash + 1, strlen(last_backslash + 1) + 1);
          return  newdest;
      }else {
          memmove(newdest,str,strlen(str)+1);
          return newdest;
}

  }
