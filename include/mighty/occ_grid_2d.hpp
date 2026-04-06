#pragma once

#include <cmath>
#include <memory>
#include <queue>
#include <vector>

#include <nav_msgs/msg/occupancy_grid.hpp>

/** @brief 2D binary occupancy grid with precomputed distance-based heat map.
 *
 *  Built from the mapper's occ_2d_topic (nav_msgs::OccupancyGrid, binary 0/100).
 *  Computes a BFS distance transform from occupied cells, then converts to a
 *  linear heat ramp for A* cost.
 *
 *  Immutable after construction — safe to share across threads via shared_ptr<const>.
 */
class OccGrid2D {
 public:
  static std::shared_ptr<const OccGrid2D> fromOccupancyGrid(
      const nav_msgs::msg::OccupancyGrid& msg) {
    auto grid = std::make_shared<OccGrid2D>();
    grid->origin_x_ = msg.info.origin.position.x;
    grid->origin_y_ = msg.info.origin.position.y;
    grid->resolution_ = msg.info.resolution;
    grid->inv_resolution_ = 1.0 / grid->resolution_;
    grid->width_ = static_cast<int>(msg.info.width);
    grid->height_ = static_cast<int>(msg.info.height);

    const size_t n = msg.data.size();
    grid->occupied_.resize(n);
    for (size_t i = 0; i < n; ++i) {
      grid->occupied_[i] = (msg.data[i] >= 100);
    }
    return grid;
  }

  bool isOccupied(int ix, int iy) const {
    if (ix < 0 || ix >= width_ || iy < 0 || iy >= height_) return true;
    return occupied_[iy * width_ + ix];
  }

  /** @brief Query occupancy at world coordinates. */
  bool isOccupiedWorld(double x, double y) const {
    int ix = static_cast<int>(std::floor((x - origin_x_) * inv_resolution_));
    int iy = static_cast<int>(std::floor((y - origin_y_) * inv_resolution_));
    return isOccupied(ix, iy);
  }

  /** @brief Compute BFS distance transform (in cells) from all occupied cells.
   *  Returns a float vector of distances in meters, truncated at max_dist_m. */
  std::vector<float> computeDistanceField(double max_dist_m) const {
    const size_t n = static_cast<size_t>(width_) * height_;
    const int max_cells = static_cast<int>(std::ceil(max_dist_m * inv_resolution_));
    const float INF = static_cast<float>(max_dist_m);
    std::vector<float> dist(n, INF);

    // BFS from all occupied cells
    struct Cell { int x, y; };
    std::queue<Cell> q;
    for (int y = 0; y < height_; ++y) {
      for (int x = 0; x < width_; ++x) {
        if (occupied_[y * width_ + x]) {
          dist[y * width_ + x] = 0.0f;
          q.push({x, y});
        }
      }
    }

    // 8-connected BFS with Euclidean distance
    const int dx8[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    const int dy8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const float dd8[] = {1.414f, 1.0f, 1.414f, 1.0f, 1.0f, 1.414f, 1.0f, 1.414f};

    while (!q.empty()) {
      auto [cx, cy] = q.front();
      q.pop();
      float cd = dist[cy * width_ + cx];

      for (int i = 0; i < 8; ++i) {
        int nx = cx + dx8[i], ny = cy + dy8[i];
        if (nx < 0 || nx >= width_ || ny < 0 || ny >= height_) continue;
        float nd = cd + dd8[i] * static_cast<float>(resolution_);
        if (nd >= max_dist_m) continue;
        size_t nidx = ny * width_ + nx;
        if (nd < dist[nidx]) {
          dist[nidx] = nd;
          q.push({nx, ny});
        }
      }
    }
    return dist;
  }

  int width() const { return width_; }
  int height() const { return height_; }
  double originX() const { return origin_x_; }
  double originY() const { return origin_y_; }
  double resolution() const { return resolution_; }
  double invResolution() const { return inv_resolution_; }
  const std::vector<bool>& occupiedData() const { return occupied_; }

 private:
  double origin_x_ = 0.0, origin_y_ = 0.0;
  double resolution_ = 0.2;
  double inv_resolution_ = 5.0;
  int width_ = 0, height_ = 0;
  std::vector<bool> occupied_;
};
