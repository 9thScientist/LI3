#ifndef __GENERIC__
#define __GENERIC__

typedef char bool;

typedef void* (*init_t)      ();
typedef void* (*clone_t)     (void*);
typedef bool  (*condition_t) (void*, void*);
typedef int   (*compare_t)   (void*, void*, void*);
typedef void  (*free_t)      (void*);

#define true 1
#define false 0

#endif
