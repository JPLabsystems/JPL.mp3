#ifndef queries_h
#define queries_h

#include "config.h"

const char *queries[]{
    "SELECT piecename FROM library ORDER BY composer",
    "SELECT DISTINCT composer FROM library",
    "SELECT DISTINCT era FROM library",
    "SELECT piecename FROM library WHERE composer = ?",
    "SELECT piecename FROM library WHERE era = ?",
    "SELECT filepath FROM library WHERE piecename = ?",
    "SELECT * FROM library WHERE piecname = ?",


    "SELECT filepath, piecename, composer, performer, instrumentation FROM library WHERE filepath = ?",
    "SELECT piecename FROM library WHERE filepath = ?",

    "SELECT * FROM library ORDER BY RANDOM() LIMIT 1"};

/*
**multi page library**
SELECT piecename
FROM library
ORDER BY composer
LIMIT 20 
OFFSET ?;
*/
//load first 20, render first ten, moveto next ten and load subsequent ten again
#endif
