/* Linked List */

typedef struct list_node list_node;

extern void add_to_list(list_node **head, int value);

extern void print_list(list_node *head);

extern void remove_from_list(list_node **head, int value);

list_node* sort_list(list_node *head, list_node *previous, list_node *current);//     !!! retorna a head !!!
                                                                               //chamar sort_list com previous = NULL
////////////////////////////////////////////

/* Doubly Linked List */

typedef struct d_linked d_linked;

extern void add_to_doubly(d_linked **head, int value);

extern void remove_d_linked(d_linked **head, int value);

extern void print_doubly(d_linked *head);

////////////////////////////////////////////

/* Stack */

typedef struct stack stack;

extern void push(stack **stack, int item);

extern int pop(stack **stack);//  <<--
                            /*        Retornarao -1 caso stack esteja vazia       */
extern int peek(stack *stack);//  <<--

////////////////////////////////////////////

/* Queue */

typedef struct queue_node queue_node;

typedef struct queue queue;

void create_queue(queue **q);

int is_empty(queue *queue);

void enqueue(queue **queue, int value);

int dequeue(queue **queue);

/* Graph */

#define MAX_SIZE 20

typedef struct adj_list adj_list;

typedef struct graph graph;

void create_graph(graph **g);

void add_edge(graph *g, int vertex1, int vertex2);

void dfs(graph *g, int source);

void bfs(graph *g, int source);

/* Binary Tree */

typedef struct binary_tree binary_tree;

binary_tree* create_binary_tree(int item, binary_tree *left, binary_tree *right);

void add_binary_search(binary_tree **bt, int item);

void print_tree_pre_order(binary_tree *tree);
void print_tree_post_order(binary_tree *tree);
void print_tree_in_order(binary_tree *tree);

binary_tree* build(binary_tree *tree, char *str, int *count, int size);

/* AVL */

typedef struct binary_tree_avl binary_tree_avl;

binary_tree_avl* create_empty_avl();

int max(int a, int b);

int h(binary_tree_avl *bt);

int is_balanced(binary_tree_avl *bt);

int balance_factor(binary_tree_avl *bt);

binary_tree_avl* create_binary_tree_avl(int item, binary_tree_avl *left, binary_tree_avl *right);

binary_tree_avl* rotate_left(binary_tree_avl *bt);

binary_tree_avl* rotate_right(binary_tree_avl *bt);

binary_tree_avl* add(binary_tree_avl *bt, int item);

void print_avl_in_order(binary_tree_avl *tree);

void print_avl_pre_order(binary_tree_avl *tree);

void print_avl_post_order(binary_tree_avl *tree);
