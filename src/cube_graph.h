#pragma once

#include <cstdint>
#include <vector>

namespace cube_graph {

constexpr int64_t CUBE_LENGTH = 400;
constexpr size_t VERTICES_NUM = CUBE_LENGTH * CUBE_LENGTH * CUBE_LENGTH;

inline int64_t get_vertex_num(int64_t x, int64_t y, int64_t z) {
    if (x < 0 || y < 0 || z < 0 || x >= CUBE_LENGTH || y >= CUBE_LENGTH || z >= CUBE_LENGTH) {
        return -1;
    }
    return z * CUBE_LENGTH * CUBE_LENGTH + y * CUBE_LENGTH + x;
};

inline std::vector<std::vector<int64_t>> make_test_graph() {
    std::vector<std::vector<int64_t>> g(VERTICES_NUM);
    for (int64_t z = 0; z < CUBE_LENGTH; ++z) {
        for (int64_t y = 0; y < CUBE_LENGTH; ++y) {
            for (int64_t x = 0; x < CUBE_LENGTH; ++x) {
                int64_t v = get_vertex_num(x, y, z);
                static int64_t neighbor_shifts[6][3] = {
                        {-1, 0,  0},
                        {1,  0,  0},
                        {0,  -1, 0},
                        {0,  1,  0},
                        {0,  0,  -1},
                        {0,  0,  1},
                };
                for (const auto &item: neighbor_shifts) {
                    int64_t to = get_vertex_num(x + item[0], y + item[1], z + item[2]);
                    if (to > 0) {
                        g.at(v).push_back(to);
                    }
                }
            }
        }
    }
    return g;
}
}
