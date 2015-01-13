//
//  mkdir.c
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 11.01.2015.
//
//

#include "mkdir.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void handleCommandMkdir(char* args[], int numargs) {

}

void makeDirectory(char *directoryName) {
  struct stat st = {0};
  if (stat(directoryName, &st) == -1) {
    if (mkdir(directoryName, 0700) != 0) {
      fprintf(stderr, "Couldn't create directory\n");
    }
  } else {
    fprintf(stderr, "Directory already exists\n");
  }
}
