//
// Created by RBT on 21/3/2024.
//
#include "graph.h"
#include <assert.h>
#include <string.h>

void test_01() {
    graph g = graph_create();
    string v1 = "v1";
    string v2 = "v2";
    string v3 = "v3";
    string v4 = "v4";
    string v5 = "v5";
    size_t result = 0;

    // 没有这条边
    assert(graph_has_vertex(g, v1) == false);
    graph_add_vertex(g, v1);
    assert(graph_has_vertex(g, v1) == true);
    assert(graph_vertices_count(g) == 1);

    assert(graph_has_vertex(g, v2) == false);
    graph_add_vertex(g, v2);
    assert(graph_has_vertex(g, v2) == true);
    assert(graph_vertices_count(g) == 2);

    graph_add_edge(g, v1, v2, 1);
    assert(graph_has_edge(g, v1, v2) == true);
    // 判断权重
    assert(graph_get_edge(g, v1, v2) == 1);
    // 判断边的个数
    assert(graph_edges_count(g, v1) == 1);
    // 判断边的个数
    assert(graph_edges_count(g, v2) == 0);

    graph_add_vertex(g, v4);
    graph_add_vertex(g, v3);
    graph_add_vertex(g, v5);
    graph_show(g, NULL, NULL);
    result = graph_vertices_count(g);
    assert(result == 5);

    graph_add_edge(g, v1, v3, 2);
    assert(graph_edges_count(g, v1) == 2);
    graph_add_edge(g, v1, v4, 10);
    assert(graph_edges_count(g, v1) == 3);
    graph_add_edge(g, v1, v5, 100);
    assert(graph_edges_count(g, v1) == 4);
    graph_add_edge(g, v2, v4, 1000);
    assert(graph_edges_count(g, v2) == 1);
    graph_add_edge(g, v2, v5, 1000);
    assert(graph_edges_count(g, v2) == 2);

    assert(graph_edges_count(g, v3) == 0);
    assert(graph_edges_count(g, v4) == 0);
    assert(graph_edges_count(g, v5) == 0);


    graph_set_edge(g, v1, v2, 100);
    // 判断权重
    assert(graph_get_edge(g, v1, v2) == 100);

    graph_show(g, NULL, NULL);

    printf("test_01() test passed.\n");

    graph_destroy(g);

}


void test_02() {
    graph g = graph_create();
    string v1 = "v1";
    string v2 = "v2";
//    string v3 = "v3";
//    string v4 = "v4";
//    string v5 = "v5";

    // 没有这条边
    assert(graph_has_vertex(g, v1) == false);
    graph_add_vertex(g, v1);
    assert(graph_has_vertex(g, v1) == true);

    assert(graph_has_vertex(g, v2) == false);
    graph_add_vertex(g, v2);
    assert(graph_has_vertex(g, v2) == true);

    assert(graph_has_edge(g, v1, v2) == false);
    graph_add_edge(g, v1, v2, 100);
    assert(graph_has_edge(g, v1, v2) == true);

    printf("test_02() test passed.\n");

    graph_destroy(g);

}

int main() {
    test_01();
    test_02();
    return 0;
}