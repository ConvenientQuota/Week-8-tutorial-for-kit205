#pragma once
#ifndef GRAPH_H
#define GRAPH_H

typedef struct edge {
    int to_vertex;
    int weight;
} Edge;

typedef struct edgeNode {
    Edge edge;
    struct edgeNode* next;
} *EdgeNodePtr;

typedef struct edgeList {
    EdgeNodePtr head;
} EdgeList;

typedef struct graph {
    int V;
    EdgeList* edges;
} Graph;

// Function to initialize a graph
Graph* create_graph(int V);

// Function to add an edge to the graph
void add_edge(Graph* self, int from, int to, int weight);

// Function to insert an edge at the front of an edge list
void insert_at_front(EdgeList* list, Edge edge);

// Function to free allocated memory
void free_graph(Graph* self);

#endif