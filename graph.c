/**
 * @file grah.c
 * 
 * @author Kassidy Maberry
 * 
 * @date 2022/11/17
 * 
 * Assignment: graphs
 * 
 * @brief A working graph.
 * 
 * @detail
 * 
 * @bugs none
 * 
 * @todo none
 */

#include <stdio.h>
#include <stdlib.h>


struct edge {
        struct verticy *locs;
};


struct verticy {
        char *key;
        struct edge *egdes;
};

/**
 * @brief this is meant to serve as a list of graph due to the limitation
 * that dynamic arrays/lists do not exist in c. So we made a single linked
 * list.
 */
struct graph {
        struct verticy *vert;
        struct graph *next; 
};


int main ()
{
        struct graph list;
        list.vert = NULL;
        list.next = NULL;

        
        return 0;
}


