/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/number-of-islands/
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "utils.hpp"

class Solution1_DFS {
public:
    /*
        Depth first search for an island, given starting coordinates.
     
        Time = O(n + 4**n) => O(4**n)
               n = number of cells in grid (nodes in graph)
     
        Space = O(n + 1 + n) => O(2n+1) => O(n)  [for call stack]
                Call stack is n + 1.
                Visited set is n.
    */
    void findIslandAreaDFS(vector<vector<char>>& grid, size_t x, size_t y) const {
        auto const inRange = 0 <= x && 0 <= y && grid.size() > y && grid[y].size() > x;
        if (inRange) {
            auto const isLand = '0' != grid[y][x];
            if (isLand) {
                grid[y][x] = '0';

                findIslandAreaDFS(grid, x + 1, y + 0);
                findIslandAreaDFS(grid, x + 0, y + 1);
                findIslandAreaDFS(grid, x - 1, y + 0);
                findIslandAreaDFS(grid, x + 0, y - 1);
            }
        }
    }
    
    int numIslands(vector<vector<char>>& grid) {
        int result = 0;

        for (size_t y = 0; grid.size() > y; ++y) {
            for (size_t x = 0; grid[y].size() > x; ++x) {
                if ('0' != grid[y][x]) {
                    ++result;
                    findIslandAreaDFS(grid, x, y);
                }
            }
        }

        return result;
    }
};

class Solution1_BFS {
    static constexpr const std::array<std::tuple<ssize_t, ssize_t>, 4> neighbors_ = {
        std::make_tuple(1, 0), std::make_tuple(0, 1), std::make_tuple(-1, 0), std::make_tuple(0, -1)
    };
    std::deque<std::tuple<size_t, size_t>> que_{};
public:
    /*
        Breadth first search for an island.
        
        Time = O(n + 4*n) => O(n)
               n = number of cells in grid (nodes in graph)
        
        Space = O(n/2) => O(n)
                Queue contains up to n/2 items.
    */
    int numIslands(vector<vector<char>>& grid) {
        int result = 0;

        for (size_t gy = 0; grid.size() > gy; ++gy) {
            for (size_t gx = 0; grid[gy].size() > gx; ++gx) {
                if ('0' != grid[gy][gx]) {
                    ++result;

                    assert(que_.empty());
                    grid[gy][gx] = '0';
                    que_.push_back(std::make_tuple(gx, gy));
                    while (!que_.empty()) {
                        for (auto _ = que_.size(); _; --_) {
                            auto [ox, oy] = que_.front(); // Original (x, y).
                            que_.pop_front();

                            for (auto [dx, dy] : neighbors_) {
                                auto const nx = ox + dx; // New x.
                                auto const ny = oy + dy; // New y.
                                auto const inRange = 0 <= nx && 0 <= ny && grid.size() > ny && grid[ny].size() > nx;
                                if (inRange) {
                                    auto const isLand = '0' != grid[ny][nx];
                                    if (isLand) {
                                        grid[ny][nx] = '0';
                                        que_.push_back(std::make_tuple(nx, ny));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return result;
    }
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

namespace doctest {
    const char* testName() noexcept { return doctest::detail::g_cs->currentTest->m_name; }
} // namespace doctest {

TEST_CASE("Case 1")
{
    cerr << doctest::testName() << '\n';
    auto grid = vector<vector<char>>{
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    int expected = 1;
    auto solution = Solution1_DFS{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.numIslands(grid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 2")
{
    cerr << doctest::testName() << '\n';
    auto grid = vector<vector<char>>{
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    int expected = 3;
    auto solution = Solution1_DFS{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.numIslands(grid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 3")
{
    cerr << doctest::testName() << '\n';
    auto grid = vector<vector<char>>{
        {'0','1','0'},
        {'1','0','1'},
        {'0','1','0'}
    };
    int expected = 4;
    auto solution = Solution1_DFS{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.numIslands(grid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 10")
{
    cerr << doctest::testName() << '\n';
    auto grid = vector<vector<char>>{
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    int expected = 1;
    auto solution = Solution1_BFS{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.numIslands(grid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 20")
{
    cerr << doctest::testName() << '\n';
    auto grid = vector<vector<char>>{
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    int expected = 3;
    auto solution = Solution1_BFS{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.numIslands(grid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 30")
{
    cerr << doctest::testName() << '\n';
    auto grid = vector<vector<char>>{
        {'0','1','0'},
        {'1','0','1'},
        {'0','1','0'}
    };
    int expected = 4;
    auto solution = Solution1_BFS{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.numIslands(grid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

/*
    End of "main.cpp"
*/
