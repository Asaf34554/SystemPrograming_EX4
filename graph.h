#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
//    int prev;   //holds the previous node num in the known shortest route through me.(dijkstra)
    int dist;   //holds the value of the shortest distance known from search starting vertex to me.(dijkstra)
    int didvisit; //holds boolean Flag to know if was in vertex before
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

char build_graph_cmd(pnode *head);
char insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);

#endif
