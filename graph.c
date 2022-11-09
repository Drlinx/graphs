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
#include <string.h>


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
        struct graph *list = malloc(sizeof(struct graph));
        list->vert = NULL;
        list->next = NULL;

        
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
struct verticy *initvert(char *s)
{
        struct verticy *new = malloc(sizeof(struct verticy)); 
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


/**
 * @brief creates a new veritcy for the graph. Expands the linked list at the
 * same time.
 * 
 * @param list the list we are appending this to.
 * @param find the key for the verticy.
 * @return an exist status.
 * 
 */
int createvert(struct graph *list, char *find)
{
        struct graph *cur = list;
        while(cur->next != NULL){
                if(cur->vert->key == find){
                        printf("Key already exists\n");
                        return 1;
                }
        }
        struct graph *new = initgraph(initvert(find));
        cur->next = new;
        return 0;
}


/**
 * @brief prints out the element within a graph.
 * 
 * @param list the list we are printing out.
 */
void printverticies(struct graph *list)
{
        struct graph *cur = list;
        while(cur != NULL){
                print("%s\n", cur->vert->key);
                cur = cur->next;
        }
}

/**
 * @brief prints out every veritcy and their edges.
 * 
 * @param list all of the verticies we have.
 */
void printgraphall(struct graph *list)
{
        struct graph *cur = list;
        struct verticy *ver = NULL;
        struct edge *edg = NULL;
        while (cur != NULL){
                // Assigns the new verticy
                ver = cur->vert;
                print("%s\n", ver->key);
                // Assigns the edges of the new verticy.
                edg = ver->egdes;
                // goes through the linked list of edges.
                while(edg != NULL){
                        print("\t-->%s\n", edg->locs->key);
                        edg = edg->next;
                }
                // Updates the current node we are working on.
                cur = cur->next;
        }
        
}


/**
 * @brief prints a specified verticy and all of its edges.
 * 
 * @param vert the specified verticy
 */
void printvert(struct verticy *vert)
{
        struct edge *edg = vert->egdes;
        print("%s\n", vert->key);
        while(edg != NULL){
                print("\t-->%s\n", edg->locs->key);
                edg = edg->next;
        }
}


/**
 * @brief removes the new line of a given string.
 * 
 * @param s the string we are editing.
 */
void nlrm(char *s)
{
        for(int i = 0; s[i] != '\0'; i++){
                if(s[i] == '\n'){
                        s[i] == '\0';
                        break;
                }
        }
}


/**
 * @brief gets an input for a characterized message.
 * 
 * @return the message with the new line removed.
 */
char *get_input(void)
{
        char *z = malloc(sizeof(char) * 128);
        printf("enter the message: ");
        fgets(z, 128, stdin);
        nl_remove(z);
        return z;
}


/**
 * @brief finds a verticy we are going to be working with.
 * 
 * @param list the list of verticies we have.
 * @param s the string we are looking for
 * 
 * @return verticy we found.
 */
struct verticy *searchvert(struct graph *list, char *s)
{
        struct graph *cur = list;
        while(cur != NULL){
                if(strcmp(cur->vert->key, s)){
                        return cur->vert;
                }
                cur = cur->next;
        }
        printf("Verticy does not exist\n");
        return NULL;
}