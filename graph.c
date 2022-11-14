/**
 * @file grah.c
 * 
 * @author Kassidy Maberry
 * 
 * @date 2022/11/17
 * 
 * Assignment: graphs
 * 
 * @brief A working graph with various functions but the most important one is
 * breath search. You can also add and print other nodes.
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
        printf("Before getting started lets create an initial veritcy: \n");
        list->vert = initvert(get_input);
        list->next = NULL;
        char inputs = 'a';
        //Grabs any required user inputs.
        char *longinp = malloc(128);
        char *secinp = malloc(128);
        // Tempory variables.
        struct verticy *temp, *extra;
        struct graph *curen;
        struct edge *use;
        help();
        while(inputs != 'e'){
                curen = list;
                temp = NULL;
                printf("What option would you like to perform(Use H for help): ");
                fgets(longinp,128,stdin);
                inputs = longinp[0];
                switch(inputs){
                        case('H'):
                        case('h'):
                                help();
                                break;
                        case('A'):
                        case('a'):
                                while(curen->next != NULL){
                                        curen = curen->next;
                                }
                                printf("What is the new verticy we are creating: ");
                                curen->next = initgraph(initvert(get_input()));
                                break;
                        case('N'):
                        case('n'):
                                //Getting user input.
                                printf("Enter the node we are attaching to: ");
                                longinp = get_input();
                                temp = searchvert(list, inputs);
                                printf("What are we connecting it to: ");
                                secinp = get_input();
                                extra = searchvert(list, secinp);
                                if(extra == NULL || temp == NULL){
                                        printf("Error one of your inputs do not exist");
                                } else {
                                        use = temp->egdes;
                                        // If it has no edges adds the first edge.
                                        if (use == NULL){
                                                temp->egdes = initedge(extra);
                                        //Otherwise finds the newest edges.
                                        } else{
                                                while(use->next != NULL){
                                                        use = use->next;
                                                }
                                                use->next = initedge(extra);
                                        }
                                }
                                break;
                        case('P'):
                        case('p'):
                                printgraphall(list);
                                break;
                        case('V'):
                        case('v'):
                                printverticies(list);
                                break;
                        case('S'):
                        case('s'):
                                printf("For the graph we are searching for.\n");
                                fgets(longinp, 128, stdin);
                                nl_remove(longinp);
                                temp = searchvert(list, longinp);
                                if (temp != NULL){
                                        printvert(temp);
                                } else {
                                        printf("Error | Node does not exist\n");
                                }
                                break;
                        case('B'):
                        case('b'):

                                break;
                        case('e'):
                        case('E'):
                                inputs = 'e';
                                break;
                }
        }
        return 0;
}


void help()
{
        print("H) prints out a help menu\n");
        print("A) Adds a new verticy to the graph\n");
        print("N) adds a new edge to a requested verticy\n");
        print("P) Prints out all the verticies and their edges\n");
        print("V) Prints out all the verticies\n");
        print("S) Prints a specificied verticy and its edges\n");
        print("B) Does a breadth first search.\n");
        print("E) Exits the program\n");
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
                if(strcmp(cur->vert->key, find)){
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
        while (cur != NULL){
                printvert(cur->vert);
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