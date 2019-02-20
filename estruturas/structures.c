/* Compilar com gcc data_structures.c structures.c -o data_structures */

#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

/* Linked List */

struct list_node{
    int val;
    struct list_node *next;
};

void add_to_list(list_node **head, int value){
    list_node *new_node = (list_node*) malloc(sizeof(list_node));
    new_node->val = value;
    new_node->next = *head;
    *head = new_node;
}

void print_list(list_node *head){//usavel tambem para doubly linked
    if(head == NULL)
        return;
    printf("%d ", head->val);
    print_list(head->next);
}

void remove_from_list(list_node **head, int value){
    list_node *previous = NULL;//mantendo a referencia do node anterior
    list_node *current = *head;
    while(current != NULL && current->val != value){//enquanto não chegar ao node desejado ou o fim da lista
        previous = current;
        current = current->next;
    }
    if (current == NULL)//saiu do while pois chegou ao fim da lista sem achar o node desejado
        head = head;
    if (previous == NULL)
        *head = current->next;//o node desejado foi o primeiro da lista, então para nao perder a referencia (ja que o previous ainda é NULL) move a head
    else
        previous->next = current->next;
    free(current);
}

list_node* sort_list(list_node *head, list_node *previous, list_node *current){//     !!! retorna a head !!!
    if(current != NULL){                                                       //chamar sort_list com previous = NULL
        list_node *aux = current;
        list_node *aux2 = current->next;
        while(aux2 != NULL && aux2->val >= current->val){
            aux = aux2;
            aux2 = aux2->next;
        }
        if(aux2 != NULL){
            aux->next = aux2->next;
            aux2->next = current;
            current = aux2;
            if(previous == NULL)
                head = current;
            else
                previous->next = current;
            sort_list(head, previous, current);
        } else{
            sort_list(head, current, current->next);
            return head;
        }
    }
}

/* Doubly Linked List */

struct d_linked{
    int val;
    struct d_linked *next;
    struct d_linked *previous;
};

void add_to_doubly(d_linked **head, int value){
    d_linked *new_d_linked = (d_linked*) malloc(sizeof(d_linked));
    new_d_linked->val = value;
    new_d_linked->next = *head;
    new_d_linked->previous = NULL;
    if(*head != NULL)
        (*head)->previous = new_d_linked;
    *head = new_d_linked;
}

void remove_from_doubly(d_linked **head, int value){
    d_linked *current = *head;
    while(current != NULL && current->val != value)
        current = current->next;
    if(current == NULL)
        return;
    if(current == *head)
        *head = current->next;
    else
        current->previous->next = current->next;
    if(current->next != NULL)
        current->next->previous = current->previous;
    free(current);
}

void print_doubly(d_linked *head){
    if(head == NULL)
        return;
    else{
        printf("%d ", head->val);
        print_doubly(head->next);
    }
}

/* Stack */

struct stack{
    int item;
    struct stack *next;
};

void push(stack **st, int item){
    stack *new_node = (stack*) malloc(sizeof(stack));
    new_node->item = item;
    new_node->next = *st;
    *st = new_node;
}

int pop(stack **st){
    if(st != NULL){
        stack *aux = *st;
        int popped = aux->item;
        *st = (*st)->next;
        free(aux);
        return popped;
    } else {
        printf("Stack Underflow\n");
        return -1;
    }
}

int peek(stack *st){
    if(st != NULL)
        return st->item;
    else {
        printf("Stack Underflow\n");
        return -1;
    }
}

/* Queue */

struct queue_node{
    int val;
    struct queue_node *next;
};

struct queue{
    queue_node *head;
    queue_node *tail;
};

void create_queue(queue **q){
    queue *new_queue = (queue*) malloc(sizeof(queue));
    new_queue->head = NULL;
    new_queue->tail = NULL;
    *q = new_queue;
}

int is_empty(queue *queue){
    if(queue->head == NULL)
        return 1;
    else
        return 0;
}

void enqueue(queue **queue, int value){
    queue_node *new_node = (queue_node*) malloc(sizeof(queue_node));
    new_node->val = value;
    if(is_empty(*queue)){
        new_node->next = new_node;
        (*queue)->head = new_node;
        (*queue)->tail = new_node;
        (*queue)->tail->next = NULL;
    } else {
        new_node->next = NULL;
        (*queue)->tail->next = new_node;
        (*queue)->tail = new_node;
    }
}

int dequeue(queue **queue){
    if(!is_empty(*queue)){
        int aux = (*queue)->head->val;
        (*queue)->head = (*queue)->head->next;
        return aux;
    }
}

/* Graph */

typedef struct adj_list{
    int item;
    struct adj_list *next;
}adj_list;

typedef struct graph{
    adj_list *vertices[MAX_SIZE];
    int visited[MAX_SIZE];
}graph;

void create_graph(graph **g){
    graph *new_graph = (graph*) malloc(sizeof(graph));
    int i;
    for(i = 0; i < MAX_SIZE; i++){
        new_graph->vertices[i] = NULL;
        new_graph->visited[i] = 0;
    }
    *g = new_graph;
}

void add_edge(graph *g, int vertex1, int vertex2){
    adj_list *new_node = (adj_list*) malloc(sizeof(adj_list));
    new_node->item = vertex2;
    new_node->next = g->vertices[vertex1];
    g->vertices[vertex1] = new_node;

    /* Undirected Graph */
    new_node = (adj_list*) malloc(sizeof(adj_list));
    new_node->item = vertex1;
    new_node->next = g->vertices[vertex2];
    g->vertices[vertex2] = new_node;
}


void dfs(graph *g, int source){
    g->visited[source] = 1;
    printf("%d\n", source);
    adj_list *adj = g->vertices[source];
    while(adj != NULL){
        if(!g->visited[adj->item])
            dfs(g, adj->item);
        adj = adj->next;
    }
}

void bfs(graph *g, int source){
    queue *queue;
    create_queue(&queue);
    int dequeued;
    g->visited[source] = 1;
    enqueue(&queue, source);

    while(!is_empty(queue)){
        dequeued = dequeue(&queue);
        printf("%d\n", dequeued);

        adj_list *adj = g->vertices[dequeued];
        while(adj != NULL){
            if(!g->visited[adj->item]){
                g->visited[adj->item] = 1;
                enqueue(&queue, adj->item);
            }
            adj = adj->next;
        }
    }
}

/* Binary Tree */

struct binary_tree{
    int item;
    binary_tree *left, *right;
};

binary_tree* create_binary_tree(int item, binary_tree *left, binary_tree *right){
    binary_tree *new_tree = (binary_tree*) malloc(sizeof(binary_tree));
    new_tree->item = item;
    new_tree->left = left;
    new_tree->right = right;
    return new_tree;
}

void add_binary_search(binary_tree **bt, int item){
    if(*bt == NULL)
        *bt = create_binary_tree(item, NULL, NULL);
    else if((*bt)->item > item)
        add_binary_search(&(*bt)->left, item);
    else
        add_binary_search(&(*bt)->right, item);
}

void print_tree_pre_order(binary_tree *tree){
    if(tree != NULL){
        printf("%d\n", tree->item);
        print_tree_pre_order(tree->left);
        print_tree_pre_order(tree->right);
    }
}

void print_tree_post_order(binary_tree *tree){
    if(tree != NULL){
        print_tree_post_order(tree->left);
        print_tree_post_order(tree->right);
        printf("%d\n", tree->item);
    }
}

void print_tree_in_order(binary_tree *tree){
    if(tree != NULL){
        print_tree_in_order(tree->left);
        printf("%d\n", tree->item);
        print_tree_in_order(tree->right);
    }
}

binary_tree* build(binary_tree *tree, char *str, int *count, int size){
    if(*count < size){
        if(str[*count] >= 48 && str[*count] < 58){
            int aux = str[*count] - '0';
            while(str[*count + 1] >= 48 && str[*count + 1] < 58){
                aux *= 10;
                *count += 1;
                aux += str[*count] - '0';
            }
            *count += 1;
            binary_tree *l = build(tree, str, count, size);
            binary_tree *r = build(tree, str, count, size);
            return create_binary_tree(aux, l, r);
        } else if(str[*count] == ')') {
            *count += 1;
            if(str[*count - 2] == '(')
                return NULL;//create_binary_tree(0, NULL, NULL);
            else
                return build(tree, str, count, size);
        } else if(str[*count] == '(' || str[*count] == ' '){
            *count += 1;
            return build(tree, str, count, size);
        }
    }
}

/* AVL */

/* USAR AVL DESSA FORMA:    binary_tree_avl *avl = create_empty_avl();
                            avl = create_binary_tree_avl(5, NULL, NULL);
                            avl = add(avl, 2);
                            avl = add(avl, 4);
                            avl = add(avl, 12);
*/

struct binary_tree_avl{
    int item;
    int h;
    binary_tree_avl *left, *right;
};

binary_tree_avl* create_empty_avl(){
    return NULL;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int h(binary_tree_avl *bt){
    if(bt == NULL)
        return -1;
    else
        return 1 + max(h(bt->left), h(bt->right));
}

int is_balanced(binary_tree_avl *bt){
    int bf = h(bt->left) - h(bt->right);
    return((-1 <= bf) && (bf <= 1));
}

int balance_factor(binary_tree_avl *bt){
    if(bt == NULL)
        return 0;
    else if((bt->left != NULL) && (bt->right != NULL))
        return (bt->left->h - bt->right->h);
    else if((bt->left != NULL) && (bt->right == NULL))
        return (1 + bt->left->h);
    else
        return (-bt->right->h - 1);
}

binary_tree_avl* create_binary_tree_avl(int item, binary_tree_avl *left, binary_tree_avl *right){
    binary_tree_avl *new_tree = (binary_tree_avl*) malloc(sizeof(new_tree));
    new_tree->item = item;
    new_tree->left = left;
    new_tree->right = right;
    new_tree->h = h(new_tree);
    return new_tree;
}

binary_tree_avl* rotate_left(binary_tree_avl *bt){
    binary_tree_avl *subtree_root = NULL;

    if(bt != NULL && bt->right != NULL){
        subtree_root = bt->right;
        bt->right = subtree_root->left;
        subtree_root->left = bt;
    }

    subtree_root->h = h(subtree_root);
    bt->h = h(bt);
    return subtree_root;
}

binary_tree_avl* rotate_right(binary_tree_avl *bt){
    binary_tree_avl *subtree_root = NULL;

    if(bt != NULL && bt->left != NULL){
        subtree_root = bt->left;
        bt->left = subtree_root->right;
        subtree_root->right = bt;
    }

    subtree_root->h = h(subtree_root);
    bt->h = h(bt);
    return subtree_root;
}

binary_tree_avl* add(binary_tree_avl *bt, int item){
    if(bt == NULL)
        return create_binary_tree_avl(item, NULL, NULL);
    else if(bt->item > item)
        bt->left = add(bt->left, item);
    else
        bt->right = add(bt->right, item);

    bt->h = h(bt);
    binary_tree_avl *child;

    if(balance_factor(bt) == 2 || balance_factor(bt) == -2){
        if(balance_factor(bt) == 2){
            child = bt->left;
            if(balance_factor(child) == -1)
                bt->left = rotate_left(child);
            bt = rotate_right(bt);
        } else if(balance_factor(bt) == -2){
            child = bt->right;
            if(balance_factor(child) == 1)
                bt->right = rotate_right(child);
            bt = rotate_left(bt);
        }
    }
    return bt;
}

void print_avl_in_order(binary_tree_avl *tree){
    if(tree != NULL){
        print_avl_in_order(tree->left);
        printf("%d\n", tree->item);
        print_avl_in_order(tree->right);
    }
}

void print_avl_pre_order(binary_tree_avl *tree){
    if(tree != NULL){
        printf("%d\n", tree->item);
        print_avl_pre_order(tree->left);
        print_avl_pre_order(tree->right);
    }
}

void print_avl_post_order(binary_tree_avl *tree){
    if(tree != NULL){
        print_avl_post_order(tree->left);
        print_avl_post_order(tree->right);
        printf("%d\n", tree->item);
    }
}
