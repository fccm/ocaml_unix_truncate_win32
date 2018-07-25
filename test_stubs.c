#define CAML_INTERNALS

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/signals.h>
//#include <caml/io.h>
//#include "unixsupport.h"

#include <stdio.h>

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include <windows.h>

int my_win_truncate(char * filename, int len)
{
  HANDLE fh;
  LARGE_INTEGER fp;
  fp.QuadPart = len;
  fh = CreateFile(filename,
                  GENERIC_WRITE,          // open for writing
                  0,                      // do not share
                  NULL,                   // default security
                  OPEN_EXISTING,          // existing file only
                  FILE_ATTRIBUTE_NORMAL,  // normal file
                  NULL); 
  if (fh == INVALID_HANDLE_VALUE) { 
    printf("failure: Unable to open file %s\n", filename);
    return -1;
  }
  if (SetFilePointerEx(fh, fp, NULL, FILE_BEGIN) == 0 ||
      SetEndOfFile(fh) == 0) {
    CloseHandle(fh);
    return -1;
  }
  CloseHandle(fh);
  return 0;
}

CAMLprim value
my_truncate(value path, value len)
{
  CAMLparam2(path, len);
  //char * p;
  int ret;
  //caml_unix_check_path(path, "truncate");
  //p = caml_stat_strdup(String_val(path));
  caml_enter_blocking_section();
  //ret = my_win_truncate(p, Long_val(len));
  ret = my_win_truncate(String_val(path), Long_val(len));
  caml_leave_blocking_section();
  //caml_stat_free(p);
  if (ret == -1) {
  //  uerror("truncate", path);
    printf("my_win_truncate() failed\n");
  }
  CAMLreturn(Val_unit);
}

