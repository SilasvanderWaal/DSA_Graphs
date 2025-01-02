#include "algorithm.h"
// queue - defines a queue as a pointer to an array of pointers to nodes
typedef pnode *queue;
// local prototypes
void init_single_source(pnode G, char s);
void relax(pnode u, pnode v, int w);
int Q_insert(queue Q, pnode u, int index);
int Q_is_empty(queue Q, int size);
pnode Q_extract_min(queue Q, int size);
bool Q_exists(queue Q, int qsize, char name);
int name_to_pos(pnode G, char c);
void list_to_matrix(pnode G, double matrix[MAXNODES][MAXNODES]);
//--------------------------------------------------------------------------
// init single source, relax and min are to be used by algorithms
//--------------------------------------------------------------------------
void init_single_source(pnode G, char s)
{
	for (pnode node = G; !is_empty(node); node = get_next(node)) {
		if (get_name(node) == s) // start node
			set_d(node, 0);
		else
			set_d(node, INFINITY);
		set_pi(node, '-');
	}
}
void relax(pnode u, pnode v, int w)
{
	if (get_d(v) > (get_d(u) + w)) {
		set_d(v, get_d(u) + w);
		set_pi(v, get_name(u));
	}
}
double min(double a, double b)
{
	return a < b ? a : b;
}
//--------------------------------------------------------------------------
// Q functions - used by other algorithms
//--------------------------------------------------------------------------
int Q_insert(queue Q, pnode u, int index)
{
	// TODO
	return 0;
}
int Q_is_empty(queue Q, int size)
{
	return !Q;
}
pnode Q_extract_min(queue Q, int size)
{
	// TODO
	return NULL;
}
bool Q_exists(queue Q, int qsize, char name)
{
	// TODO
	return false;
}
//--------------------------------------------------------------------------
// Dijkstra's algorithm, single source shortest path tree generator
// a -> b(1) -> c(5)
// b -> c(2)           --> d: [  0,   1,   3]
// c                       e: [  -,   a,   b]
//--------------------------------------------------------------------------
void dijkstra(pnode G, char s, double *d, char *e)
{
	// TODO
}
//--------------------------------------------------------------------------
// Prim's algorithm - Minimum Spanning Tree generator
// start_node: a
// a -> b(1) -> c(5)
// b -> c(2)           --> d: [inf,   1,   2]
// c                       e: [  -,   a,   b]
//--------------------------------------------------------------------------
void prim(pnode G, char start_node, double *d, char *e)
{
	// TODO
}

//--------------------------------------------------------------------------
// Floyd's algorithm: returns matrix of distances
// a -> b(1)
// |                   |0  |1  |3  |
// b -> c(2)    -->    |INF|0  |2  |
// |                   |INF|INF|0  |
// c
//--------------------------------------------------------------------------
void floyd(pnode G, double W[MAXNODES][MAXNODES])
{
	//Initializng the weights of the graf
	list_to_matrix(G, W);
	//Looping over the all the nodes as intermediate nodes
	for (size_t i = 0; i < MAXNODES; i++)
	{
		//Setting the distance of every node to itself to zero. We do this in the first loop because it has the least ammount of iterations.
		W[i][i] = 0;
		//Looping over the nodes as source nodes
		for (size_t j = 0; j < MAXNODES; j++)
		{
			//Looping over the nodes as destination ndoes
			for (size_t k = 0; k < MAXNODES; k++)
			{
				//If we find a shorter path when using the intermediate node, we use that path instead
				if (W[j][i] + W[i][k] < W[j][k])
                    W[j][k] = W[j][i] + W[i][k];
			}
		}
	}
}
//--------------------------------------------------------------------------
// Warshall's algorithm: returns matrix of closures, i.e. if paths exists
// a -> b(1)
// |                   |T  |T  |T  |
// b -> c(2)    -->    |F  |T  |T  |
// |                   |F  |F  |T  |
// c
//--------------------------------------------------------------------------
void warshall(pnode G, double W[MAXNODES][MAXNODES])
{
	//We use the floyd function for the shortes path between all nodes
	floyd(G, W);
	//Check if the value is INF, if so, there is no path. 
	for (size_t i = 0; i < MAXNODES; i++)
	{
		for (size_t j = 0; j < MAXNODES; j++)
		{
			if(W[i][j] == INFINITY)
				W[i][j] = false;
			else 
				W[i][j] = true;
		}
	}
}
