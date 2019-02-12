#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "maybe.h"

// TODO: actual maybe template
//char prog[44] = {0x55,0x48,0x89,0xe5,0x48,0xb8,0xef,0xbe,0xad,0xde,0xef,0xbe,0xad,0xde,0xff,0xd0,0x5d,0xc3};
char prog[55] = {0x55,0x48,0x89,0xe5,0x48,0x85,0xff,0x74,0x21,0x48,0x83,0xec,0x10,0x48,0x89,0x7d,0xf8,0x48,0x8b,0x3f,0x48,0xb8,0xef,0xbe,0xad,0xde,0xef,0xbe,0xad,0xde,0xff,0xd0,0x48,0x8b,0x7d,0xf8,0x48,0x89,0x07,0x48,0x89,0xf8,0x48,0x89,0xf8,0x48,0x83,0xc4,0x10,0x5d,0xc3,0x0f,0x1f,0x40,0x00};

// TODO: do math on pointers in a way I know is defined
void* align(size_t to, void* ptr) {
  uint64_t p = (uint64_t)ptr;
  p = (p + to - 1) / to * to;
  assert(p % to == 0);
  assert(p - to < (uint64_t)ptr);
  return (void*)p;
}

// TODO: make this maintain a buffer
// TODO: cache page size
void* jit_malloc(size_t size) {
  size_t pagesize = sysconf(_SC_PAGESIZE);
  void* ptr = malloc(size + pagesize);
  if (!ptr) return NULL;

  ptr = align(pagesize,ptr);
  if (mprotect(ptr,size,PROT_READ|PROT_WRITE|PROT_EXEC) < 0) perror("mprotect: ");
  return ptr;
}

// TODO: do this
void jit_free(void* ptr) {
  return;
}

// A maybe is None or Some x

// Creates a Maybe
// If !e, it's None; if e, Some x
// If !e, the second argument is ignored
Maybe Maybe_New(int e, void* x) {
  if (e) {
    Maybe m = malloc(sizeof(void*));
    *m = x;
    return m;
  }
  else return NULL;
}

// Returns 1 if m is None, 0 otherwise
int Maybe_IsNone(Maybe m) {
  return !m;
}

// Applies f to the value in m, and returns a Maybe with the result.
// If inPlace, consumes m in the process.
Maybe Maybe_Apply(Maybe m, void* (*f)(void*), int inPlace) {
  if (Maybe_IsNone(m)) {
    if (inPlace) return m;
    else return Maybe_New(0,NULL);
  }
  void* v = f(*m);
  if (!inPlace) return Maybe_New(1,v);
  *m = v;
  return m;
}

void memecpy(void* dest, void* src, size_t n) {
  for (size_t i = 0; i < n; i++) {
    ((char*)dest)[i] = ((char*)src)[i];
  }
}

// A functor on Maybes
// The return function will be in-place if inPlace
typedef Maybe (*Maybe_F)(void*);
Maybe_F Maybe_Fmap(void* (*f)(void*), int inPlace) {
  if (inPlace) {
  
  } else {


  }
  size_t lfun = 64;
  void* fun = jit_malloc(lfun);
  memecpy(fun,prog,lfun);
  for (int i = 0; i < sizeof(void*); i++) {
    ((char*)fun)[22+i] = ((char*)(&f))[i];
  }
  __asm("mfence\n\t"
        "lfence");
  return fun;

}

// Unpacks and destroys a Maybe
// Undefined return value if the Maybe was nothing
void* Maybe_Open(Maybe m) {
  if (Maybe_IsNone(m)) return NULL;
  void* x = *m;
  free(m);
  return x;
}
