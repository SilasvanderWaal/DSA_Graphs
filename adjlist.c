#include "adjlist.h"
// local prototypes
pnode create_node(char nname);
pnode node_cons(pnode first, pnode second);
pedge create_edge(char to, double weight);
pedge edge_cons(pedge first, pedge second);
pedge _add_edge(pedge edge, char to, double weight);
pedge _rem_edge(pedge edges, char to);
void remove_all_edges_to(pnode G, char name);
void remove_all_edges_from(pnode G, char name);

// create_node: creates node with name nname
pnode create_node(char nname)
{
	pnode new_node = (pnode)calloc(1, sizeof(node));
	new_node->name = nname;
	new_node->d = INFINITY;
	new_node->pi = '-';
	new_node->next_node = NULL;
	new_node->edges = NULL;
	return new_node;
}
// function implementations
bool is_empty(pnode G)
{
	return !G;
}
char get_name(pnode G)
{
	return is_empty(G) ? '-' : G->name;
}
pnode set_name(pnode G, char name)
{
	if (!is_empty(G))
		G->name = name;
	return G;
}
pedge get_edges(pnode G)
{
	return is_empty(G) ? NULL : G->edges;
}
pnode set_edges(pnode G, pedge E)
{
	if (!is_empty(G))
		G->edges = E;
	return G;
}
pnode get_next(pnode G)
{
	return is_empty(G) ? NULL : G->next_node;
}
// see node_cons() for the corresponding "set-next" function
double get_d(pnode G)
{
	return is_empty(G) ? INFINITY : G->d;
}
pnode set_d(pnode G, double d)
{
	if (!is_empty(G))
		G->d = d;
	return G;
}
char get_pi(pnode G)
{
	return is_empty(G) ? '-' : G->pi;
}
pnode set_pi(pnode G, char pi)
{
	if (!is_empty(G))
		G->pi = pi;
	return G;
}
// node_cons: connects two nodes in adjacency list
pnode node_cons(pnode first, pnode second)
{
	if (is_empty(first))
		return NULL;
	first->next_node = second;
	return first;
}
// add_node: adds a new node with name nname to adjacency list G
//           in lexicographical order. If it already exists
//           in graph, nothing is done
pnode add_node(pnode G, char nname)
{
    if(is_empty(G))
        return create_node(nname);

    pnode current_node = G;
    pnode trailer_node = NULL;

    //Looping over the list of nodes, searching for the right posistion
    while(current_node && get_name(current_node) <= nname){
        trailer_node = current_node;
        current_node = get_next(current_node);
    }

    //Adding a new node to the list IF we do not have a node with the same already
    if(get_name(trailer_node) != nname){
        pnode new_node = create_node(nname);
        if(!node_cons(trailer_node, new_node))  //If the new node is a new root, trailer_node will be NULL. We set G to new node.
            G = new_node;
        node_cons(new_node, current_node);
    }

	return G;
}
// rem_node: removes node with name name from adjacency list G
//           if node does not exist, nothing happens
pnode rem_node(pnode G, char name)
{
    pnode trailer_node = NULL;
    pnode current_node = G;
    //Looping until correct node or no node is left
    while(current_node && get_name(current_node) != name){
        trailer_node = current_node;
        current_node = get_next(current_node);
    }

    //The node does not exist, return without adjusting the list
    if(!current_node){
        return G;
    }

    //Removing edges and exisctance in edges from other nodes
   	remove_all_edges_from(G, name);
	remove_all_edges_to(G, name);
	//If the construction returns zero, the node to be deleted is root, then we have to move the start pointer
	if(!node_cons(trailer_node, get_next(current_node))){
        G = get_next(current_node);
	}
	free(current_node);
	current_node = NULL;
	return G;
}
// get_node: returns pointer to node with name name from adjacency list G. Returns NULL if not found in list
pnode get_node(pnode G, char name){
	return is_empty(G)	   ?  NULL :
	       get_name(G) == name ?  G :
					get_node(get_next(G), name);
}
// get_node: returns true if node with name name exists in adjacency list G
//           false otherwise
bool find_node(pnode G, char name)
{
	return is_empty(G)	   ? false :
	       get_name(G) == name ? true :
				     find_node(get_next(G), name);
}
// create_edge: creates edge
pedge create_edge(char to, double weight)
{
	pedge new_edge = (pedge)calloc(1, sizeof(edge));
	new_edge->to = to;
	new_edge->weight = weight;
	return new_edge;
}
bool edge_empty(pedge E)
{
	return !E;
}
char get_to(pedge E)
{
	return edge_empty(E) ? '-' : E->to;
}
pedge set_to(pedge E, char to)
{
	if (!edge_empty(E))
		E->to = to;
	return E;
}
double get_weight(pedge E)
{
	return edge_empty(E) ? INFINITY : E->weight;
}
pedge set_weight(pedge E, double weight)
{
	if (!edge_empty(E))
		E->weight = weight;
	return E;
}
pedge get_next_edge(pedge E)
{
	return edge_empty(E) ? NULL : E->next_edge;
}
// edge_cons: connects two edges in edge list
pedge edge_cons(pedge first, pedge second)
{
	if (edge_empty(first))
		return NULL;
	first->next_edge = second;
	return first;
}
// upd_edge: updates edge E to new weight
// Checks if the new weight is less then the orignial one, if so, the weight is updated
pedge upd_edge(pedge E, double weight)
{
	return get_weight(E) < weight ?  NULL : set_weight(E, weight);
}
// _add_edge: creates and connects new edge to edge-list
pedge _add_edge(pedge E, char to, double weight)
{
    if(edge_empty(E))
        return create_edge(to, weight);

    pedge current_edge = E;
    pedge trailer_edge = NULL;

    //Looping over the list of edges, searching for the right posistion
    while(current_edge && get_to(current_edge) <= to){
        trailer_edge = current_edge;
        current_edge = get_next_edge(current_edge);
    }

    //If edge alreadt exsist the weight is updated
    if(get_to(trailer_edge) == to){
        upd_edge( E, weight);
        return E;
    }

    //Creating and inserting new edge
    pedge new_edge = create_edge(to, weight);
    if(!edge_cons(trailer_edge, new_edge))
        E = edge_cons(new_edge, current_edge);

    return E;
}
// add_edge: adds an edge to G by finding correct start node
//           and then calling _add_edge to create new edge
void add_edge(pnode G, char from, char to, double weight)
{
    //Check that the to node exists
    if(!find_node(G, to))
        return;
    //Getting pointer to the node
    G = get_node(G, from);
	set_edges(G, _add_edge(get_edges(G), to, weight));
}
// _find_edge: finds edge in edge-list
bool _find_edge(pedge E, char to)
{
    while(!edge_empty(E)){
        if(get_to(E) == to)
            return true;
        E = get_next_edge(E);
    }
	return false;
}
// find_edge: returns true if edge between from and to exists, false otherwise
bool find_edge(pnode G, char from, char to)
{
    while (!is_empty(G)) {
        if(get_name(G) == from)
            return _find_edge(get_edges(G), to);
        G = get_next(G);
    }
	return false;
}
// _edge_cardinality: returns the number of edges from one node
int _edge_cardinality(pedge E)
{
    int count = 0;
	while(!edge_empty(E)){
	   count++;
	   E = get_next_edge(E);
	}
	return count;
}
// edge_cardinality: returns the total number of edges in G
int edge_cardinality(pnode G)
{
    int count = 0;
    while (!is_empty(G)) {
        count += _edge_cardinality(get_edges(G));
		G = get_next(G);
	}
	return count;
}
// _self_loops: returns the number of edges going back to
//              source node
int _self_loops(pedge E, char src)
{
    int count = 0;
	while(!edge_empty(E)){
	   if(get_to(E) == src)
	       count++;
	   E = get_next_edge(E);
	}
	return count;
}
// self_loops: counts the number of self-loops, i.e. edges to and from
//             the same node
int self_loops(pnode G)
{
    int count = 0;
    while (!is_empty(G)) {
        count += _self_loops(get_edges(G), get_name(G));
		G = get_next(G);
	}
	return count;
}
// _rem_edge: removes edge from edge-list
pedge _rem_edge(pedge E, char to)
{
    pedge current_edge = E;
    pedge trailer_edge = NULL;
    //Looping over until correct edge or no edge left
    while(get_to(current_edge) != to && current_edge){
        trailer_edge = current_edge;
        current_edge = get_next_edge(current_edge);
    }
    //Edge is not found
    if(!current_edge){
        return E;
    }
    //If edge_cons returns NULL, the edge is first in the list and E must be changed
    if(!edge_cons(trailer_edge, get_next_edge(current_edge))){
        E = get_next_edge(current_edge);
    }
    free(current_edge);
    current_edge = NULL;
    return E;
}
// rem_edge: removes edge from G
void rem_edge(pnode G, char from, char to)
{
    if(!(G = get_node(G, from)))
        return;
    set_edges(G, _rem_edge(get_edges(G), to));
}
// remove_all_edges_to: removes all edges going towards node with name name
void remove_all_edges_to(pnode G, char name){
    while(!is_empty(G)){
        rem_edge(G, get_name(G), name);
        G = get_next(G);
    }
}
// remove_all_edges_from: removes all edges from node with name name
void remove_all_edges_from(pnode G, char name)
{
    G = get_node(G, name);
    if (G == NULL) return;

    pedge current_edge = get_edges(G);
    pedge trailer_edge = NULL;
    while(!edge_empty(current_edge)){
        trailer_edge = current_edge;
        current_edge = get_next_edge(current_edge);
        free(trailer_edge);
        trailer_edge = NULL;
    }
    set_edges(G, NULL);
}
// node_cardinality: returns the number of nodes in G
int node_cardinality(pnode G)
{
	int count = 0;
	while(G){
        count++;
        G = get_next(G);
	}
	return count;
}
// name_to_pos: returns position of node with name c, -1s if not found
int name_to_pos(pnode G, char c)
{
    int count = -1;
    while (!is_empty(G)) {
        count++;
        if(get_name(G) == c)
            break;
        G = get_next(G);
    }
	return count;
}
// pos_to_name: returns name of node at position pos in G
char pos_to_name(pnode G, int pos)
{
    pnode buff = G;
	for (size_t i = 0; i < pos; i++) {
	   buff = get_next(buff);
	}
	return get_name(buff);
}
// list_to_pos: creates adjacency matrix from adjacency list
void list_to_matrix(pnode G, double matrix[MAXNODES][MAXNODES])
{
    if(is_empty(G)){return;}
    //Initializing the matrix default values
    for(size_t i = 0; i < MAXNODES; i++){
        for(size_t j = 0; j < MAXNODES; j++){
            matrix[i][j] = INFINITY;
        }
    }
    //Setting the existing edges to their weight
    for (pnode node = G; node != NULL; node = get_next(node)) {
        int from = name_to_pos(G, get_name(node));
        for (pedge edge = get_edges(node); edge != NULL; edge = get_next_edge(edge)) {
            int to = name_to_pos(G, get_to(edge));
            matrix[from][to] = get_weight(edge);
        }
    }
}
