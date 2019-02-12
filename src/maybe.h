#ifndef MAYBE_H
#define MAYBE_H

// A maybe is None or Some x

typedef void** Maybe;

// Creates a Maybe
// If !e, it's None; if e, Some x
Maybe Maybe_New(int e, void* x);

// Returns 1 if m is None, 0 otherwise
int Maybe_IsNone(Maybe m);

// Applies f to the value in m, and returns a Maybe with the result.
// If inPlace, consumes m in the process.
Maybe Maybe_Apply(Maybe m, void* (*f)(void*), int inPlace);

// A functor on Maybes
// The return function will be in-place if inPlace
typedef Maybe (*Maybe_F)(void*);
Maybe_F Maybe_Fmap(void* (*f)(void*), int inPlace);

// Unpacks and destroys a Maybe
// Undefined return if the Maybe was nothing
void* Maybe_Open(Maybe m);

#endif /* MAYBE_H */
