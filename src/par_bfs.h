#pragma once

#include <cstdint>
#include <queue>
#include <vector>

inline std::vector<int64_t> par_bfs(int64_t start, const std::vector<std::vector<int64_t>> &g) {
    std::vector<int64_t> dist(g.size(), -1);
    std::queue<int64_t> q;
    dist.at(start) = 0;
    q.push(start);
    while (!q.empty()) {
        int64_t from = q.front();
        q.pop();
        for (int64_t to: g.at(from)) {
            if (dist.at(to) == -1) {
                q.push(to);
                dist.at(to) = dist.at(from) + 1;
            }
        }
    }
    return dist;
}
