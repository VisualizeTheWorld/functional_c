// Test code
#include <stdlib.h>
#include <stdio.h>

#include "maybe.h"

int inc(int a) {
  putc(a,stdout);
  return a+1;
}

int main(int argc, char* argv[]) {
  Maybe m = Maybe_New(1,(void*)'!');
  volatile Maybe_F f = Maybe_Fmap((void*)inc, 0);
  printf("%lx\n",m);
  m = (f)((void*)m);
  printf("%lx\n",m);
  m = (f)((void*)m);
  printf("%lx\n",m);
  m = (f)((void*)m);
  printf("%lx\n",m);
  m = (f)((void*)m);
  printf("%lx\n",m);
  printf("%c\n",Maybe_Open(m));
  return 0;
}
