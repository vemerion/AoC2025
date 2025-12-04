#include <iostream>
#include <string>
#include <vector>
#include <print>

class Grid {
  friend std::istream& operator>>(std::istream& is, Grid& grid);
public:
  unsigned papers(bool part1) {
    unsigned count{};
    for (bool changed = true; changed;) {
      changed = false;
      for (int row = 0; row < std::ssize(rows); row++) {
        for (int col = 0; col < std::ssize(rows[row]); col++) {
          if (isPaper(row, col) && adjacent(row, col) < 4) {
            count++;
            if (!part1) {
              remove(row, col);
              changed = true;
            }
          }
        }
      }
    }
    return count;
  }

private:
  bool inside(int row, int col) const {
    return row >= 0 && row < std::ssize(rows) && col >= 0 && col < std::ssize(rows[row]);
  }

  bool isPaper(int row, int col) const {
    return inside(row, col) && rows[row][col] == '@';
  }

  void remove(int row, int col) {
    if (inside(row, col)) {
      rows[row][col] = '.';
    }
  }

  unsigned adjacent(int row, int col) const {
    unsigned count{};
    for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
        if ((i != 0 || j != 0) && isPaper(row + i, col + j)) {
          count++;
        }
      }
    }
    return count;
  }

  std::vector<std::string> rows{};
};

std::istream& operator>>(std::istream& is, Grid& grid) {
  std::string row{};
  while (std::getline(is, row)) {
    grid.rows.push_back(std::move(row));
  }

  return is;
}

int main() {
  Grid grid{};
  std::cin >> grid;
  std::println("Part 1 result = {}", grid.papers(true));
  std::println("Part 2 result = {}", grid.papers(false));
  return 0;
}
