#ifndef __CATALOG__
#define __CATALOG__

#include "generic.h"

typedef struct catalog      *CATALOG;
typedef struct catalog_set  *CATSET;

CATALOG initCatalog (int n,
					 void* (*init)   (), 
                     bool  (*equals) (void*, void*), 
                     void* (*clone)  (void*), 
                     void  (*free)   (void*));

CATALOG changeCatalogOps (CATALOG cat,
					      void* (*init)   (), 
                          bool  (*equals) (void*, void*), 
                          void* (*clone)  (void*), 
                          void  (*free)   (void*));

CATALOG cloneCatalog   (CATALOG cat);

CATALOG insertCatalog  (CATALOG c, int i, char* hash, void* content);
void*   replaceCatalog (CATALOG c, int i, char* hash, void* content);
void*   getCatContent  (CATALOG c, int i, char* hash);

void*   addCatalog     (CATALOG c, int index, char *hash);

bool lookUpCatalog (CATALOG c, int i, char* hash);
int  countPosElems (CATALOG c, int i);
int  countAllElems (CATALOG c);

void freeCatalog (CATALOG c);


CATSET initCatalogSet (int n);
CATSET fillCatalogSet (CATALOG cat, CATSET cs, int i);
CATSET allCatalogSet  (CATALOG cat, CATSET cs);
CATSET contcpy        (CATSET dest, CATSET src, int pos);

CATSET filterCat(CATALOG cat, condition_t condition, void* arg);
void   separateCat(CATALOG cat, compare_t compare, void* arg, CATSET set1, CATSET set2);

void   condSeparateCat(CATALOG cat, CATSET set1, CATSET set2,
                                    condition_t condition, void* cond_arg,
                                    compare_t   comparator, void* comp_arg);

CATSET sortCatSet(CATSET set, compare_t comparator);

CATSET unionCatalogDataSets (CATSET dest, CATSET source);
CATSET diffCatalogDataSets  (CATSET dest, CATSET source);
CATSET concatCatSet         (CATSET set1, CATSET set2);

char* getKeyPos         (CATSET cs, int pos);
void* getContPos        (CATSET cs, int pos);
int   getCatalogSetSize (CATSET cs); 
void  freeCatalogSet    (CATSET cs);

#endif
