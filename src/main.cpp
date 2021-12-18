#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

#include "cube_graph.h"
#include "par_bfs.h"
#include "seq_bfs.h"
#include "timer.h"

template <typename T>
void check_distances(const T &dist) {
    using namespace cube_graph;
    constexpr int64_t max_coord = CUBE_LENGTH - 1;
    assert(0 == dist[get_vertex_num(0, 0, 0)]);
    assert(max_coord == dist[get_vertex_num(max_coord, 0, 0)]);
    assert(max_coord == dist[get_vertex_num(0, max_coord, 0)]);
    assert(max_coord == dist[get_vertex_num(0, 0, max_coord)]);
    assert(max_coord * 2 == dist[get_vertex_num(0, max_coord, max_coord)]);
    assert(max_coord * 2 == dist[get_vertex_num(max_coord, 0, max_coord)]);
    assert(max_coord * 2 == dist[get_vertex_num(max_coord, max_coord, 0)]);
    assert(max_coord * 3 == dist[get_vertex_num(max_coord, max_coord, max_coord)]);
}


int main() {
    static constexpr int iters_cnt = 5;
    auto g = cube_graph::make_test_graph();
    SteadyTimer<std::chrono::duration<double>> t;
    double seq_avg = 0, par_avg = 0;
    for (int i = 0; i < iters_cnt; ++i) {
        t.start();
        auto dist_sec = seq_bfs(0, g);
        seq_avg += t.time().count();
        check_distances(dist_sec);

        t.start();
        auto dist_par = par_bfs(0, g);
        par_avg += t.time().count();
        check_distances(dist_par);
    }
    seq_avg /= iters_cnt;
    par_avg /= iters_cnt;

    std::cout << "Average of " << iters_cnt << " bfs runs on cubic graph with edge = " << cube_graph::CUBE_LENGTH << ":\n"
              << std::setprecision(4) << std::fixed
              << "Seq bfs: " << seq_avg << "s\n"
              << "Par bfs: " << par_avg << "s\n"
              << "Seq / par: " << seq_avg / par_avg << std::endl;
    return 0;
}
