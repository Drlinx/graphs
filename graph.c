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
 * @detail Free memory will not exist after you add enough verticies.
 * 
 * @bugs none
 * 
 * @todo none
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum color {UNEXPLORED = 0, EXPLORING, EXPLORED};

struct edge {
        struct verticy *locs;
        struct edge *next;
};


struct verticy {
        char *key;
        struct edge *egdes;
        int col;
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


struct items {
        char *entry;
        struct items *next;
};


struct queue {
        struct verticy *loc;
        struct queue *next;
};


void help();
struct graph *initgraph(struct verticy *addon);
struct verticy *initvert(char *s);
struct edge *initedge(struct verticy *connect);
int createvert(struct graph *list, char *find);
void printverticies(struct graph *list);
void printgraphall(struct graph *list);
void printvert(struct verticy *vert);
void nlrm(char *s);
char *get_input(void);
struct verticy *searchvert(struct graph *list, char *s);
int breadthfs(struct verticy *start, struct verticy *end);
struct items *inititem(char *s);
struct queue *initqueue(struct verticy *spot);
void printbfspath(struct queue *head, struct verticy *end, struct verticy *start);
int itemsprint(struct items *path, int len);
int comppaths(char *key, struct verticy *comp);


int main ()
{
        struct graph *list = malloc(sizeof(struct graph));
        printf("Before getting started lets create an initial veritcy: ");
        list->vert = initvert(get_input());
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
                printf("What option would you like to perform (Use H for help): ");
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
                                temp = searchvert(list, longinp);
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
                                printf("For the graph we are searching for: ");
                                fgets(longinp, 128, stdin);
                                nlrm(longinp);
                                temp = searchvert(list, longinp);
                                if (temp != NULL){
                                        printvert(temp);
                                } else {
                                        printf("Error | Node does not exist\n");
                                }
                                break;
                        case('B'):
                        case('b'):
                                printf("Where are we starting our search: ");
                                longinp = get_input();
                                temp = searchvert(list, longinp);
                                printf("What are we connecting it to: ");
                                secinp = get_input();
                                extra = searchvert(list, secinp);
                                if(extra == NULL || temp == NULL){
                                        printf("Error one of your inputs do not exist");
                                } else {
                                        breadthfs(temp, extra);
                                }
                                break;
                        case('e'):
                        case('E'):
                                inputs = 'e';
                                break;
                }
        }
        return 0;
}


/**
 * @brief A function that prints out the operations in the menu. 
 */
void help()
{
        printf("-----\n");
        printf("H) prints out a help menu\n");
        printf("A) Adds a new verticy to the graph\n");
        printf("N) adds a new edge to a requested verticy\n");
        printf("P) Prints out all the verticies and their edges\n");
        printf("V) Prints out all the verticies\n");
        printf("S) Prints a specificied verticy and its edges\n");
        printf("B) Does a breadth first search.\n");
        printf("E) Exits the program\n");
        printf("-----\n");
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
        new->col = UNEXPLORED;
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
 * @brief resets the nodes colors after a search.
 * 
 * @param list the current list containing pointers to every node.
 */
void colorreset(struct graph *list)
{
        struct verticy *cur;
        struct graph *nav = list;
        while(nav != NULL){
                cur = nav->vert;
                cur->col = UNEXPLORED;
                nav = nav->next;
        }
}


/**
 * @brief creates a new element for our queue.
 * 
 * @param spot the edge we are appending into the queue.
 * @return the newly created queue element.
 */
struct queue *initqueue(struct verticy *spot)
{
        struct queue *new = malloc(sizeof(struct queue));
        new->loc = spot;
        new->next = NULL;
        return new;
}



/**
 * @brief creates a new item for the array we will be printing out.
 * 
 * @param s the name of the veritcy our bfs lead to.
 * @return the location of the newly created element.
 */
struct items *inititem(char *s)
{
        struct items *new = malloc(sizeof(struct items));
        new->entry = s;
        new->next = NULL;
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
                if(strcmp(cur->vert->key, find) == 0){
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
                printf("%s\n", cur->vert->key);
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
        printf("%s\n", vert->key);
        while(edg != NULL){
                printf("\t-->%s\n", edg->locs->key);
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
        nlrm(z);
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
                if(strcmp(cur->vert->key, s) == 0){
                        return cur->vert;
                }
                cur = cur->next;
        }
        printf("Verticy does not exist\n");
        return NULL;
}


/**
 * @brief Does a breadth first search. Feeding in the two ends of the verticies.
 * First it will create a queue of the verticies we have gone through. Going through
 * changing the exploration status of the verticy. After chaing said status once it
 * has been explored. We append the verticies based upon the edges of the current
 * verticy we are looking at. Afterwards moving onto the next verticy currently
 * within the queue. Afterwards we save the queue and work backwards to find the
 * path we used to find where the end verticy was found.
 * 
 * @param start the node we are starting the search from.
 * @param end the node we are ending the search from.
 * @return the function status of the program.
 */
int breadthfs(struct verticy *start, struct verticy *end)
{
        //Head of queue
        struct queue *find = initqueue(start);
        //Tail of queue
        struct queue *cur = find;
        //Node we are performing the BFS on.
        struct queue *inc = find;
        //For searching at the destinations.
        struct edge *edg;
        while(inc != NULL || inc->loc != end){
                inc->loc->col = EXPLORING;
                //Adds each element to the key if they are unexplored.
                while(edg != NULL){
                        if(edg->locs->col == UNEXPLORED){
                                cur->next = initqueue(edg->locs);
                                cur = cur->next;
                        }
                        edg = edg->next;
                }
                //Sets as explored.
                inc->loc->col = EXPLORED;
                inc = inc->next;
        }
        if (inc == NULL)
                return 0;
        printbfspath(find, end, start);
        return 1;
}


/**
 * @brief prints out the result of the breadth first search. 
 * 
 * @param head the head of the queue that holds the bfs data.
 * @param end the node we are finding.
 * @param start the node we are starting from.
 */
void printbfspath(struct queue *head, struct verticy *end, struct verticy *start)
{
        struct items *path = inititem(end->key);
        struct items *temp = path;
        struct queue *nav = head;
        struct queue *tail;
        // Finds the tail.
        while (nav->next != NULL){
                nav = nav->next;
        }
        tail = nav;
        nav = head;
        while(!strcmp(temp->entry, start->key) == 0 || nav == tail){
                nav = nav->next;
                
                if(comppaths(temp->entry, nav->loc) == 1){
                        temp->next = inititem(nav->loc->key);
                        temp = temp->next;
                        nav = head;
                }
        }
        temp = path;
        // Finds the length of the list;
        int i = 0;
        while (temp != NULL){
                i++;
                temp = temp->next;
        }
        itemsprint(path, i - 1);
}


/**
 * @brief compares the edges to the node we are looking for.
 * 
 * @param key the key we are looking for
 * @param comp the verticy we are comparing the edges to.
 * @return the success case.
 */
int comppaths(char *key, struct verticy *comp)
{
        struct edge *edg = comp->egdes;
        while(edg != NULL){
                if (strcmp(edg->locs->key, key) == 0){
                        // Verticy found.
                        return 1;
                }
                edg = edg->next;
        }
        // Verticy not found.
        return 0;
}


/**
 * @brief Prints the list in reverse. Due to the fact we build the list from
 * end to start.
 * 
 * @param path the path to find our verticy.
 * @param len the length of our list.
 */
int itemsprint(struct items *path, int len)
{
        struct items *temp = path;
        for(int i = 0; i < len; i++){
                path = path->next;
        }
        if(len <= 0){
                printf("%s\n", path->entry);
                return 0;
        }
        printf("%s->", temp->entry);
        itemsprint(path, len - 1);
        return 1;
}