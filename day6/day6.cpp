#include <iostream>
#include <vector>
#include <string>
#include <print>
#include <algorithm>
#include <ranges>

using Num = unsigned long long;

class Math {
  friend std::istream& operator>>(std::istream& is, Math& math);
public:
  Num grandTotal(bool part1) const {
    Num total{};
    int col = 0;
    while (col < cols()) {
      std::vector<Num> numbers{};
      const char op = get(rows() - 1, col);
      do {
        numbers.push_back({});
        for (int row = 0; row < rows() - 1; row++) {
          const char digit = get(row, col);
          if (digit != ' ') {
            if (part1) {
              while (row >= std::ssize(numbers)) {
                numbers.push_back({});
              }
              numbers[row] = numbers[row] * 10 + (digit - '0');
            } else {
              numbers.back() = numbers.back() * 10 + (digit - '0');
            }
          }
        }
        col++;
      } while (get(rows() - 1, col) == ' ');
      total += std::ranges::fold_left(numbers | std::views::filter([](const auto e) { return e != 0; }), op == '*' ? Num{1} : Num{0}, [op](const auto e1, const auto e2) { return op == '*' ? e1 * e2 : e1 + e2; });
    }
    return total;
  }

private:
  bool inside(int row, int col) const {
    return row >= 0 && row < std::ssize(grid) && col >= 0 && col < std::ssize(grid[row]);
  }

  char get(int row, int col) const {
    return inside(row, col) ? grid[row][col] : '*';
  }

  int rows() const {
    return std::ssize(grid);
  }

  int cols() const {
    return std::ssize(grid[0]);
  }

  std::vector<std::string> grid{};
};

std::istream& operator>>(std::istream& is, Math& math) {
  std::string line{};
  while (std::getline(is, line)) {
    math.grid.push_back(std::move(line));
  }
  return is;
}

int main() {
  Math math{};
  std::cin >> math;
  std::println("Part 1 result = {}", math.grandTotal(true));
  std::println("Part 2 result = {}", math.grandTotal(false));
  return 0;
}
