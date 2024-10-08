#include <stdio.h>
#include <stdlib.h>

static FILE* fp = NULL;

void initLogs() {
  FILE* file_pointer = fopen("log.txt", "w");

  if (!file_pointer) {
    exit(1);
  }

  fp = file_pointer;
}

void closeLogs() {
  fclose(fp);
}

void funcStartLogger(char *funcName) {
  fprintf(fp, "[LOG] Start function '%s'\n", funcName);
}

void callLogger(char *callerName, char *calleeName, long int valID) {
  fprintf(fp, "[LOG] CALL '%s' -> '%s' {%ld}\n", callerName, calleeName, valID);
}

void funcEndLogger(char *funcName, long int valID) {
  fprintf(fp, "[LOG] End function '%s' {%ld}\n", funcName, valID);
}

void binOptLogger(int val, int arg0, int arg1, char *opName, char *funcName,
                  long int valID) {
  fprintf(fp, "[LOG] In function '%s': %d = %d %s %d {%ld}\n", funcName, val, arg0,
    opName, arg1, valID);
}

void optLogger(char* opName) {
  fprintf(fp, "OP: %s\n", opName);
}