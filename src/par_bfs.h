#pragma once

#include <atomic>
#include <vector>

#include "datapar.hpp"

inline pasl::pctl::parray<int64_t> par_bfs(int64_t start, const std::vector<std::vector<int64_t>> &g) {
    using namespace pasl::pctl;

    parray<int64_t> dist(g.size(), -1l);
    parray<std::atomic<bool>> used(g.size(), [](long) { return false; });

    parray<int64_t> frontier = {start};
    dist[start] = 0;
    used[start] = true;

    while (frontier.size() != 0) {
        parray<int64_t> degrees(frontier.size(), [&](long i) {
            return g[frontier[i]].size();
        });
        parray<int64_t> shifts = scan(degrees.cbegin(), degrees.cend(), static_cast<int64_t>(0),
                                      [](int64_t x, int64_t y) { return x + y; }, forward_exclusive_scan);
        assert(shifts.size() > 0);
        assert(degrees.size() > 0);
        size_t next_frontier_size = shifts[shifts.size() - 1] + degrees[degrees.size() - 1];
        degrees.clear();
        parray<int64_t> next_frontier(next_frontier_size, -1l);
        parallel_for(0l, frontier.size(), [&] (long i) {
            int64_t from = frontier[i];
            for (int to_idx = 0; to_idx < g.at(from).size(); ++to_idx) {
                int64_t to = g.at(from).at(to_idx);
                bool expected = false;
                if (used[to].compare_exchange_strong(expected, true)) {
                    int64_t pos_in_next_frontier = shifts[i] + to_idx;
                    next_frontier[pos_in_next_frontier] = to;
                    dist[to] = dist[from] + 1;
                }
            }
        });
        frontier = filter(next_frontier.cbegin(), next_frontier.cend(), [](int64_t v) {
           return v >= 0;
        });
    }
    return dist;
}
