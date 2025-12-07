#include <iostream>
#include <string>
#include <vector>
#include <print>
#include <set>
#include <map>
#include <utility>

using Num = unsigned long long;

struct Pos {
  int row{};
  int col{};
  auto operator<=>(const Pos&) const = default;

  Pos operator+(const Pos& other) const {
    return {row + other.row, col + other.col};
  }
};

class Grid {
  friend std::istream& operator>>(std::istream& is, Grid& grid);
public:
  std::pair<Num, Num> analyze() const {
    std::set<Pos> splits{};
    std::map<Pos, Num> positions{};
    Num timelines{};
    
    for (int col = 0; col < std::ssize(rows[0]); col++) {
      if (const Pos p{0, col}; get(p) == 'S') {
        positions[p] = 1;
      }
    }
    
    while (!positions.empty()) {
      std::map<Pos, Num> next{};
      for (const auto& [pos, count] : positions) {
        const Pos moved = pos + down;
        switch (get(moved)) {
          case '.':
            next[moved] += count;
            break;
          case '^':
            splits.insert(pos);
            next[pos + left] += count;
            next[pos + right] += count;
            break;
          case ' ':
            timelines += count;
            break;
          default:
            break;
        }
      }
      positions = std::move(next);
    }
    return {splits.size(), timelines};
  }
private:
  bool inside(const Pos& p) const {
    return p.row >= 0 && p.row < std::ssize(rows) && p.col >= 0 && p.col < std::ssize(rows[p.row]);
  }

  char get(const Pos& p) const {
    return inside(p) ? rows[p.row][p.col] : ' ';
  }

  static constexpr Pos down{1 , 0};
  static constexpr Pos left{0 , -1};
  static constexpr Pos right{1 , 1};

  std::vector<std::string> rows{};
};

std::istream& operator>>(std::istream& is, Grid& grid) {
  std::string line{};
  while (std::getline(is, line)) {
    grid.rows.push_back(std::move(line));
  }

  return is;
}

int main() {
  Grid grid{};
  std::cin >> grid;
  const auto [part1, part2] = grid.analyze();
  std::println("Part 1 result = {}", part1);
  std::println("Part 2 result = {}", part2);
  return 0;
}
