#ifndef PRIM_H_
#define PRIM_H_

#include "Graph.h"

class EdgeComparator
{
public:
    bool operator()(Edge edge1, Edge edge2)
    {
        return edge1.weight > edge2.weight;
    }
};

void primMatrix(Graph &graph);

void primList(Graph &graph);

#endif /* PRIM_H_ */
