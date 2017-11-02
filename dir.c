#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int dir_size(char * path) {
  int ret=0;
  DIR *d;
  d=opendir(path);
  struct dirent * entry;
  struct stat sb;
  char file_path[256];
  file_path[0]=0;
  while (entry=readdir(d)) {
    if (entry->d_type==DT_REG) {
      strcat(file_path,path);
      strcat(file_path,"/");
      strcat(file_path,entry->d_name);
      stat(file_path, &sb);
      //printf("file name: %s\n",entry->d_name);
      //printf("file path: %s\n",file_path);
      //printf("file size: %d\n",sb.st_size);
      ret+=sb.st_size;
      file_path[0]=0;
    }
  }
      
  closedir(d);
  return ret;

}

void print_dir(char * path) {
  struct stat ds;
  stat(path,&ds);
  printf("statistics for dir: %s\n",path);
  printf("Directory total size: %d bytes\n",dir_size(path));
  DIR * d;
  d=opendir(path);
  struct dirent * entry;
  printf("Directories:\n");
  while (entry=readdir(d)) {
    if (entry->d_type==DT_DIR || entry->d_type==DT_CHR)
      printf("%s\n",entry->d_name);
  }
  closedir(d);
  printf("Regular files:\n");
  d=opendir(path);
  while (entry=readdir(d)) {
    if (entry->d_type==DT_REG)
      printf("%s\n",entry->d_name);
  }
  closedir(d);

}

int main() {
  print_dir(".");



  return 0;
}
