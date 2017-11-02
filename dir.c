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
  while ((entry=readdir(d))) {
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
    else if (entry->d_type==DT_DIR && strcmp(entry->d_name,".") && strcmp(entry->d_name,"..")) {
      strcat(file_path,path);
      strcat(file_path,"/");
      strcat(file_path,entry->d_name);
      //stat(file_path, &sb);
      ret+=dir_size(file_path);
      file_path[0]=0;
    }
  }
      
  closedir(d);
  return ret;

}

void print_subdir(char * path,int i) {
  char buffer[i+1];
  int j=0;
  for (;j<i;j++){
    buffer[j]='\t';
  }
  buffer[i]=0;
  struct stat ds;
  stat(path,&ds);
  printf("%sstatistics for dir: %s\n",buffer,path);
  printf("%sDirectory total size: %d bytes\n",buffer,dir_size(path));
  DIR * d;
  d=opendir(path);
  struct dirent * entry;
  printf("%sDirectories:\n",buffer);
  char s[256];
  strcpy(s,path);
  while ((entry=readdir(d))) {
    if (entry->d_type==DT_DIR /*|| entry->d_type==DT_CHR*/) {
      printf("%s%s\n",buffer,entry->d_name);
      if (strcmp(entry->d_name,".") && strcmp(entry->d_name,"..")) {
	strcat(s,"/");
	strcat(s,entry->d_name);
	print_subdir(s,i+1);
	strcpy(s,path);
      }
    }
  }
  closedir(d);
  printf("%sRegular files:\n",buffer);
  d=opendir(path);
  while ((entry=readdir(d))) {
    if (entry->d_type==DT_REG)
      printf("%s%s\n",buffer,entry->d_name);
  }
  closedir(d);

}

void print_dir(char * path) {
  print_subdir(path,0);
}





int main() {
  print_dir(".");



  return 0;
}
