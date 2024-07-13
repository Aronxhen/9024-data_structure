#include "graph.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>


typedef struct list_node *Linkedlist;

//struct node
//every node represent a vertex
//in edges add vertex to tail
typedef struct node {
    string vertex;
    size_t weight;
    Linkedlist edges;
    struct node *next;
    struct node *pre;
} *LinkedNode;

//struct list
//put vertex in the linkedlist
//add vertex to head is different to edges
struct list_node {
    LinkedNode head;
    LinkedNode tail;
    int total;
};

//struct graph
struct Graph_Repr {
    //put edge
    Linkedlist vertexes;
    //ignore
    list ignore_list;
};


/***************************** GENERAL INTERFACE ******************************/

Linkedlist create_linkedlist() {
    Linkedlist new_linkedlist = malloc(sizeof(struct list_node));
    assert(new_linkedlist != NULL);
    new_linkedlist->head = NULL;
    new_linkedlist->tail = NULL;
    new_linkedlist->total = 0;

    return new_linkedlist;
}

LinkedNode create_linkednode(string vertex, size_t weight) {
    LinkedNode new_linkednode = malloc(sizeof(struct node));
    assert(new_linkednode != NULL);
    new_linkednode->vertex = malloc(strlen(vertex) + 1);
    assert(new_linkednode->vertex != NULL);
    //let vertex copy in new.vertex
    strcpy(new_linkednode->vertex, vertex);
    new_linkednode->weight = weight;
    new_linkednode->edges = NULL;
    new_linkednode->next = NULL;
    new_linkednode->pre = NULL;
    return new_linkednode;
}

void insert_linkedlist_to_head(Linkedlist linked_l, string vertex, size_t weight) {
    if (linked_l != NULL) {
        if (linked_l->head == NULL) {
            linked_l->head = linked_l->tail = create_linkednode(vertex, weight);
            linked_l->total++;
        } else {
            LinkedNode new_Node = create_linkednode(vertex, weight);
            //3,2,1
            //4
            //4,3,2,1
            //firstly new_node follow first
            new_Node->next = linked_l->head;
            linked_l->head->pre = new_Node;
            //then update first
            linked_l->head = new_Node;
            linked_l->total++;
        }
    }
}

void insert_linkedlist_to_tail(Linkedlist linked_l, string vertex, size_t weight) {
    if (linked_l != NULL) {
        if (linked_l->head == NULL) {
            linked_l->head = linked_l->tail = create_linkednode(vertex, weight);
            linked_l->total++;
        } else {
            LinkedNode new_Node = create_linkednode(vertex, weight);
            //1,2,3
            //4
            //1,2,3,4
            //firstly new_node follow last
            new_Node->pre = linked_l->tail;
            linked_l->tail->next = new_Node;
            //then update first
            linked_l->tail = new_Node;
            linked_l->total++;
        }
    }
}

bool contains_linkedlist(Linkedlist linked_l, string vertex) {
    bool contains = false;
    if (linked_l != NULL) {
        LinkedNode current = linked_l->tail;
        while (current != NULL) {
            //find vertex
            if (strcmp(current->vertex, vertex) != 0) {
                current = current->pre;
            } else if (strcmp(current->vertex, vertex) == 0) {
                contains = true;
                break;
            }
        }
    }
    return contains;
}

void change_linkedlist_weight(Linkedlist linked_l, string vertex1, string vertex2, size_t weight) {
    if (linked_l != NULL) {
        LinkedNode current = linked_l->head;
        while (current != NULL) {
            if (strcmp(current->vertex, vertex1) == 0) {
                LinkedNode edge_vertexes = current->edges->head;
                while (edge_vertexes != NULL) {
                    if (strcmp(edge_vertexes->vertex, vertex2) == 0) {
                        //find vertexes2
                        //and update weight
                        edge_vertexes->weight = weight;
                        break;
                    }
                    //change edge_vertexes
                    edge_vertexes = edge_vertexes->next;
                }
                //if vertex2 not in edge_vertexes
                break;
            }
            //change current vertex
            current = current->next;
        }
        //end while current
    }
}

void free_linked_l(Linkedlist linked_l) {
    if (linked_l != NULL) {
        LinkedNode current = linked_l->head;
        //define a next
        LinkedNode next;
        while (current != NULL) {
            next = current->next;
            free(current->vertex);
            free_linked_l(current->edges);
            free(current);
            //change current
            current = next;
        }
    }
}


/**
 * graph_create
 *
 * @brief Allocate the required memory for a new graph.
 *
 * @return The new graph. If there's an error (e.g. out of memory),
 *         return NULL.
 */
graph graph_create(void) {
    graph dw_gra = malloc(sizeof(struct Graph_Repr));
    assert(dw_gra != NULL);
    dw_gra->vertexes = create_linkedlist();
    dw_gra->ignore_list = NULL;

    return dw_gra;
}

/**
 * graph_destroy
 *
 * @brief Free all memory associated with the given graph.
 *
 * @param graph The graph to be destroyed. If it's NULL, do nothing.
 */
void graph_destroy(graph dw_gra) {
    if (dw_gra != NULL) {
        free_linked_l(dw_gra->vertexes);
        free(dw_gra);
    }
}

/**
 * graph_show
 *
 * @brief Print the contents of the graph to the given file.
 *
 * The graph should be printed in the following format:
 *
 *      vertex1
 *      vertex2
 *      vertex3
 *      ...
 *      vertexN
 *      vertex1 vertex2 weight
 *      vertex2 vertex4 weight
 *      vertexN vertexM weight
 *
 * Where the label of each vertex is first printed, then the directed edges
 * between each vertex along with the weight of that edge.
 *
 * An ignore list is also passed, indicating that certain vertices are required
 * to be excluded from the output, including any incident edges.
 *
 * @param  graph The graph to show. If it's NULL, do nothing.
 * @param FILE * The file to print the graph to. If it's NULL, print to stdout.
 * @param   list The vertices to ignore.
 */
void graph_show(graph dw_gra, FILE *file, list ignore_list) {
    if (file == NULL) {
        file = stdout;
    }
    if (dw_gra != NULL) {
        if (dw_gra->vertexes != NULL) {
            //output vertex
            LinkedNode current_v = dw_gra->vertexes->tail;
            while (current_v != NULL) {
                if (list_contains(ignore_list, current_v->vertex) == false) {
                    fprintf(file, "%s\n", current_v->vertex);
                }
                current_v = current_v->pre;
            }

            //output edges
            current_v = dw_gra->vertexes->tail;
            while (current_v != NULL) {
                if (list_contains(ignore_list, current_v->vertex) == false) {
                    if (current_v->edges != NULL) {
                        //count machine
                        int count = 0;
                        LinkedNode edge_vertexes = current_v->edges->head;
                        while (edge_vertexes != NULL) {
                            if (list_contains(ignore_list, edge_vertexes->vertex) == false) {
                                count++;
                            }
                            // insert to tail so use next
                            edge_vertexes = edge_vertexes->next;
                        }
                        //count>0 represent vertex1 have edge with vertex2 not in ignore list
                        if (count > 0) {
                            edge_vertexes = current_v->edges->head;
                            while (edge_vertexes != NULL) {
                                if (list_contains(ignore_list, edge_vertexes->vertex) == false) {
                                    fprintf(file, "%s ", current_v->vertex);
                                    fprintf(file, "%s ", edge_vertexes->vertex);
                                    fprintf(file, "%zu\n", edge_vertexes->weight);
                                }
                                // insert to tail so use next
                                edge_vertexes = edge_vertexes->next;
                            }
                        }
                        //end if count > 0
                    }
                }
                current_v = current_v->pre;
            }
            //end while output edges

        }
        //end if gra_vertexes != NULL
    } else {
        return;
    }
}


/****************************** VERTEX INTERFACE ******************************/

/**
 * graph_add_vertex
 *
 * @brief Add a vertex with the given label to the graph.
 *
 * @param  graph The graph in which to add the vertex. If it's NULL, do nothing.
 * @param string The label of the vertex to be added.  If it's NULL, or already
 *               in the graph, do nothing.
 */
void graph_add_vertex(graph dw_gra, string vertex) {
    if (dw_gra != NULL && dw_gra->vertexes != NULL) {
        insert_linkedlist_to_head(dw_gra->vertexes, vertex, 0);
    }
}
/**
 * graph_has_vertex
 *
 * @brief Determines whether a vertex with a particular label exists in the
 *        graph.
 *
 * @param  graph The graph to search. If it's NULL, return false.
 * @param string The label of the vertex to search for. If it's NULL, return false.
 * @return       true if a vertex with the given label exists in the graph,
 *               false otherwise.
 */
bool graph_has_vertex(graph dw_gra, string vertex) {
    bool has_contain = false;
    if (dw_gra != NULL && dw_gra->vertexes != NULL) {
        has_contain = contains_linkedlist(dw_gra->vertexes, vertex);
    }
    return has_contain;
}

/**
 * graph_vertices_count
 *
 * @brief Returns the number of vertices in the graph.
 *
 * @param graph The graph to count. If it's NULL, the graph is empty.
 * @return      The number of vertices in the graph.
 */
size_t graph_vertices_count(graph dw_gra) {
    size_t number = 0;
    if (dw_gra != NULL && dw_gra->vertexes != NULL) {
        number = dw_gra->vertexes->total;
    }
    return number;
}


/******************************* EDGE INTERFACE *******************************/
/**
 * graph_add_edge
 *
 * @brief Add a new weighted, directed edge to the graph.
 *
 * @param  graph The graph in which to add the edge. If it's NULL, do nothing.
 * @param string The label of the source vertex. If it's NULL, do nothing.
 * @param string The label of the destination vertex. If it's NULL, do nothing.
 * @param size_t The weight of the edge. If the edge already exists, do nothing.
 */
void graph_add_edge(graph dw_gra, string vertex1, string vertex2, size_t weight) {
    if (dw_gra != NULL && dw_gra->vertexes != NULL && vertex1 != NULL && vertex2 != NULL) {
        //if not exist
        //add these vertex in the graph
        if (contains_linkedlist(dw_gra->vertexes, vertex1) == false) {
            graph_add_vertex(dw_gra, vertex1);
        }
        if (contains_linkedlist(dw_gra->vertexes, vertex2) == false) {
            graph_add_vertex(dw_gra, vertex2);
        }

        //add edge
        LinkedNode current_v = dw_gra->vertexes->tail;
        while (current_v != NULL) {
            //find vertex1
            if (strcmp(current_v->vertex, vertex1) == 0) {
                //vertex1_edges is not NULL
                if (current_v->edges != NULL) {
                    // if vertex2 exist in edges do nothing
                    if (contains_linkedlist(current_v->edges, vertex2) == false) {
                        //insert to tail
                        insert_linkedlist_to_tail(current_v->edges, vertex2, weight);
                        break;
                    }
                } else {
                    // vertex1 edges is NULL
                    current_v->edges = create_linkedlist();
                    insert_linkedlist_to_tail(current_v->edges, vertex2, weight);
                    break;
                }
            }
            current_v = current_v->pre;
        }
    }
}

/**
 * graph_has_edge
 *
 * @brief Determines whether an edge exists between two vertices in the graph.
 *
 * @param  graph The graph to search. If it's NULL, return false.
 * @param string The label of the source vertex. If it's NULL, return false.
 * @param string The label of the destination vertex. If it's NULL, return false.
 * @return       true if an edge between two vertices exists in the graph,
 *               false otherwise.
 */
bool graph_has_edge(graph dw_gra, string vertex1, string vertex2) {
    bool has_edge = false;
    if (dw_gra != NULL && dw_gra->vertexes != NULL && vertex1 != NULL && vertex2 != NULL) {
        LinkedNode current_v = dw_gra->vertexes->tail;
        while (current_v != NULL) {
            //find vertex1
            if (strcmp(current_v->vertex, vertex1) == 0) {
                //vertex1_edges is not NULL
                if (current_v->edges != NULL) {
                    // if vertex2 exist in edges return true
                    if (contains_linkedlist(current_v->edges, vertex2) == true) {
                        has_edge = true;
                        break;
                    }
                    //if no vertex in edges
                    break;
                }
            }
            current_v = current_v->pre;
        }
    }
    return has_edge;
}

/**
 * graph_set_edge
 *
 * @brief Update the weight of a edge between two vertices.
 *
 * @param  graph The graph in which to update the edge. If it's NULL, do nothing.
 * @param string The label of the source vertex. If it's NULL, do nothing.
 * @param string The label of the destination vertex. If it's NULL, do nothing.
 * @param size_t The new weight of the edge. If the edge doesn't exist, do nothing.
 */
void graph_set_edge(graph dw_gra, string vertex1, string vertex2, size_t weight) {
    if (dw_gra != NULL && dw_gra->vertexes != NULL && vertex1 != NULL && vertex2 != NULL) {
        //if edge exist
        if (contains_linkedlist(dw_gra->vertexes, vertex1) == true &&
            contains_linkedlist(dw_gra->vertexes, vertex2) == true) {
            change_linkedlist_weight(dw_gra->vertexes, vertex1, vertex2, weight);
        }
    }
}

/**
 * graph_get_edge
 *
 * @brief Return the weight of the edge between two vertices.
 *
 * @param  graph The graph to search. If it's NULL, return 0.
 * @param string The label of the source vertex. If it's NULL, return 0.
 * @param string The label of the destination vertex. If it's NULL, return 0.
 * @return       The weight of the edge between two vertices. If the edge doesn't
 *               exist, return 0.
 */
size_t graph_get_edge(graph dw_gra, string vertex1, string vertex2) {
    size_t weight = 0;
    if (dw_gra != NULL && dw_gra->vertexes != NULL && vertex1 != NULL && vertex2 != NULL) {
        LinkedNode current_v = dw_gra->vertexes->tail;
        while (current_v != NULL) {
            //find vertex1
            if (strcmp(current_v->vertex, vertex1) == 0) {
                //vertex1_edges is not NULL
                if (current_v->edges != NULL) {
                    // if vertex2 exist in edges return true
                    if (contains_linkedlist(current_v->edges, vertex2) == true) {
                        LinkedNode edge_vertexes = current_v->edges->head;
                        while (edge_vertexes != NULL) {
                            if (strcmp(edge_vertexes->vertex, vertex2) == 0) {
                                weight = edge_vertexes->weight;
                                break;
                            }
                            //insert to tail so is next not pre
                            edge_vertexes = edge_vertexes->next;
                        }
                    }
                    //if no vertex2 in edge_vertexes
                    break;
                }
            }
            //insert to tail so pre
            current_v = current_v->pre;
        }
    }
    return weight;
}


/**
 * graph_edges_count
 *
 * @brief Return the number of outgoing edges from a particular vertex in the
 *        graph.
 *
 * @param  graph The graph to search. If it's NULL, return 0.
 * @param string The label of the vertex. If it's NULL, return 0.
 * @return       The number of outgoing edges from the vertex. If the vertex
 *               doesn't exist, return 0.
 */
size_t graph_edges_count(graph dw_gra, string vertex) {
    size_t number = 0;
    if (dw_gra != NULL && dw_gra->vertexes != NULL && vertex != NULL) {
        if (contains_linkedlist(dw_gra->vertexes, vertex) == true) {
            LinkedNode current_v = dw_gra->vertexes->tail;
            while (current_v != NULL) {
                //find vertex1
                if (strcmp(current_v->vertex, vertex) == 0) {
                    //vertex1_edges is not NULL
                    if (current_v->edges != NULL) {
                        number = current_v->edges->total;
                        break;
                    }
                    //vertex1_edge is NULL
                    break;
                }
                //insert to tail so pre
                current_v = current_v->pre;
            }
        }
    }
    return number;
}

