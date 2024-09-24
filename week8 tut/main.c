#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Function to create a graph with 'num_vertices' vertices
Graph* create_graph(int num_vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));   // Allocate memory for the graph
    graph->V = num_vertices;                         // Set the number of vertices
    graph->edges = (EdgeList*)malloc(num_vertices * sizeof(EdgeList));  // Allocate memory for the edge lists

    // Initialize each vertex's edge list to NULL
    for (int vertex = 0; vertex < num_vertices; vertex++) {
        graph->edges[vertex].head = NULL;
    }

    return graph;
}

// Function to insert an edge at the front of the edge list for a vertex
void insert_at_front(EdgeList* list, Edge edge) {
    EdgeNodePtr new_node = (EdgeNodePtr)malloc(sizeof(struct edgeNode)); // Allocate memory for a new edge node
    new_node->edge = edge;                                                // Assign the edge to the node
    new_node->next = list->head;                                          // Point the new node's next to the current head
    list->head = new_node;                                                // Set the new node as the head of the list
}

// Function to add an edge to the graph from 'from_vertex' to 'to_vertex' with a weight 'weight'
void add_edge(Graph* graph, int from_vertex, int to_vertex, int weight) {
    Edge new_edge;
    new_edge.to_vertex = to_vertex;  // Set the destination vertex of the edge
    new_edge.weight = weight;        // Set the weight of the edge
    insert_at_front(&graph->edges[from_vertex], new_edge);  // Insert the edge at the front of the list for 'from_vertex'
}

// Function to free the memory allocated for the graph
void free_graph(Graph* graph) {
    // Loop through each vertex's edge list and free the nodes
    for (int vertex = 0; vertex < graph->V; vertex++) {
        EdgeNodePtr current_node = graph->edges[vertex].head;
        while (current_node != NULL) {
            EdgeNodePtr temp = current_node;
            current_node = current_node->next;
            free(temp);  // Free each node in the edge list
        }
    }
    free(graph->edges);  // Free the edge list array
    free(graph);         // Free the graph structure
}

int main() {
    // Open the input file containing the graph data
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;  // Exit with an error code if the file can't be opened
    }

    // Read the number of vertices from the file
    int num_vertices;
    fscanf(file, "%d", &num_vertices);

    // Initialize the graph with 'num_vertices' vertices
    Graph* graph = create_graph(num_vertices);

    // Variables to hold the source vertex, destination vertex, and edge weight
    int source_vertex, destination_vertex, edge_weight;

    // Loop through the edges in the file and add them to the graph
    while (fscanf(file, "%d,%d,%d", &source_vertex, &destination_vertex, &edge_weight) == 3) {
        add_edge(graph, source_vertex, destination_vertex, edge_weight);  // Add an edge to the graph
    }

    // Close the file after reading
    fclose(file);

    // Free the dynamically allocated memory for the graph
    free_graph(graph);

    return 0;  // Program completed successfully
