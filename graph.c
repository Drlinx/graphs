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
        struct edge *next;
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


/**
 * @brief initiates a new member in the list containing the graph members.
 * 
 * @param addon a newly made veritcy we are making.
 * @return the location of the new graph member which will be appended on.
 */
struct graph *initgraph(struct verticy *addon)
{
        struct graph *new = malloc(sizeof(struct graph));
        new->next = NULL;
        new->vert = addon;
        return new;
}


/**
 * @brief inits a verticy for the graph.
 * 
 * @return the location of the new verticy.
 */
struct verticy *initvert(void)
{
        struct verticy *new = malloc(sizeof(struct verticy));
        char *s = malloc(sizeof(char) * 128);
        fgets(s, 128, stdin);   
        new->key = s;
        new->egdes = NULL;
        return new;
}


/**
 * @brief creates a new edge that we will add to our verticy.
 * 
 * @param connect what verticy we are connecting.
 * @return the location of the newly created edge.
 */
struct edge *initedge(struct verticy *connect)
{
        struct edge *new = malloc(sizeof(struct edge));
        new->next = NULL;
        new->locs = connect;
        return new;
}