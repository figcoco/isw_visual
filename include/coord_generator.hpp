#pragma once


#include <vector>
#include <cmath>

class XyCoordGenerator{
public:
    std::vector<std::vector<int>> __call__(int x0, int y0, int x1, int y1) {
        std::vector<std::vector<int>> coord;
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int x = x0;
        int y = y0;
        int sx = x0 > x1 ? -1 : 1;
        int sy = y0 > y1 ? -1 : 1;
        if (dx > dy) {
            float err = static_cast<float>(dx) / 2.0;
            while (x != x1) {
                coord.push_back({x, y});
                err -= dy;
                if (err < 0) {
                    y += sy;
                    err += dx;
                }
                x += sx;
            }
            coord.push_back({x, y});
        }
        else {
            float err = static_cast<float>(dy) / 2.0;
            while (y != y1) {
                coord.push_back({x, y});
                err -= dx;
                if (err < 0) {
                    x += sx;
                    err += dy;
                }
                y += sy;
            }
            coord.push_back({x, y});
        }
        return coord;
    }
};

