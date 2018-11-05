#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

typedef struct Cat
{
    int faceDirection, line, column, initialColumn, initialLine, exists, immortal;
    char overlaid;
    clock_t start_immortal_time;
    struct Cat *nextCat;
}CAT;

#endif // CAT_H_INCLUDED
