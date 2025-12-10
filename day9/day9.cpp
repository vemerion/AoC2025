#include <iostream>
#include <string>
#include <vector>
#include <print>
#include <map>
#include <flat_set>
#include <array>

using Num = long long;

struct Pos {
  Num x{};
  Num y{};
  auto operator<=>(const Pos&) const = default;

  Pos operator+(const Pos& other) const {
    return {x + other.x, y + other.y};
  }
};

template <>
struct std::hash<Pos> {
  std::size_t operator()(const Pos& p) const {
    return p.x + p.y * 31;
  }
};

using Tiles = std::vector<Pos>;

Tiles parse() {
  Tiles result{};
  Pos pos{};
  char unused{};
  while (std::cin >> pos.x >> unused >> pos.y) {
    result.push_back(pos);
  }
  
  return result;
};

Num rectangle(const Tiles& tiles, bool part1) {
  static constexpr Pos east{1, 0};
  static constexpr Pos south{0, 1};
  static constexpr Pos west{-1, 0};
  static constexpr Pos north{0, -1};
  static constexpr std::array directions{east, south, west, north};

  static constexpr auto turnLeft = [](unsigned dir) { return (dir + 3) % directions.size(); };
  static constexpr auto turnRight = [](unsigned dir) { return (dir + 1) % directions.size(); };

  Num result{};

  std::flat_set<Pos> border{};
  std::flat_set<Pos> outside{};

  if (!part1) {
    for (size_t i = 0; i < tiles.size(); i++) {
      const auto [x1, y1] = tiles[i];
      const auto [x2, y2] = tiles[i == tiles.size() - 1 ? 0 : i + 1];

      if (x1 == x2) {
        for (auto y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
          border.insert({x1, y});
        }
      } else {
        for (auto x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
          border.insert({x, y1});
        }
      }
    }

    Pos pos{};
    for (const auto& p : border) {
      if (p.x > pos.x) {
        pos = p;
      }
    }
    pos = pos + east;
    const auto start = pos;
    auto dir = 3;
    while (outside.empty() || (pos != start || dir != 3)) {
      outside.insert(pos);
      if (const auto left = pos + directions[turnLeft(dir)]; !border.contains(left)) {
        dir = turnLeft(dir);
        pos = left;
      } else if (border.contains(pos + directions[dir])) {
        dir = turnRight(dir);
      } else {
        pos = pos + directions[dir];
      }
    }
  }

  for (size_t i = 0; i < tiles.size(); i++) {
    for (size_t j = i + 1; j < tiles.size(); j++) {
      const auto [x1, y1] = tiles[i];
      const auto [x2, y2] = tiles[j];
      if (const Num area = (std::max(x1, x2) - std::min(x1, x2) + 1) * (std::max(y1, y2) - std::min(y1, y2) + 1); area > result) {
        bool ok = true;
        if (!part1) {
          for (Num x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
            if (outside.contains({x, y1}) || outside.contains({x, y1})) {
              ok = false;
              break;
            }
          }
          if (!ok) {
            continue;
          }
          for (Num y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
            if (outside.contains({x1, y}) || outside.contains({x2, y})) {
              ok = false;
              break;
            }
          }
          if (!ok) {
            continue;
          }
        }
        result = area;
      }
    }
  }

  return result;
}

int main() {
  const auto tiles = parse();
  std::println("Part 1 result = {}", rectangle(tiles, true));
  std::println("Part 2 result = {}", rectangle(tiles, false));
  return 0;
}
