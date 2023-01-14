#ifndef NODE_
#define NODE_
#include "graph.h"


pnode create_node(int index);
pnode get_node(pnode head, int ver);
void del_all_ver(pnode* head);
void del_ver(pnode ver,pnode* head);




#endif