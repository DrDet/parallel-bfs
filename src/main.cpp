#include <iostream>
#include <vector>
#include <cassert>

#include "cube_graph.h"
#include "par_bfs.h"
#include "seq_bfs.h"

void check_distances(const std::vector<int64_t> &dist) {
    using namespace cube_graph;
    constexpr int64_t max_coord = CUBE_LENGTH - 1;
    assert(0 == dist.at(get_vertex_num(0, 0, 0)));
    assert(max_coord == dist.at(get_vertex_num(max_coord, 0, 0)));
    assert(max_coord == dist.at(get_vertex_num(0, max_coord, 0)));
    assert(max_coord == dist.at(get_vertex_num(0, 0, max_coord)));
    assert(max_coord * 2 == dist.at(get_vertex_num(0, max_coord, max_coord)));
    assert(max_coord * 2 == dist.at(get_vertex_num(max_coord, 0, max_coord)));
    assert(max_coord * 2 == dist.at(get_vertex_num(max_coord, max_coord, 0)));
    assert(max_coord * 3 == dist.at(get_vertex_num(max_coord, max_coord, max_coord)));
}


int main() {
    auto g = cube_graph::make_test_graph();
    auto dist = seq_bfs(0, g);
    check_distances(dist);
    return 0;
}
