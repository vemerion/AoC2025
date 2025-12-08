#include <iostream>
#include <vector>
#include <string>
#include <print>
#include <set>
#include <queue>
#include <cassert>
#include <algorithm>

using Num = long long;

struct Node {
  Num x{};
  Num y{};
  Num z{};
  size_t circuit{};

  Num distance(const Node& other) const {
    return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z);
  }
};

struct Edge {
  Node* n1{};
  Node* n2{};

  bool operator<(const Edge& other) const {
    return n1->distance(*n2) > other.n1->distance(*other.n2);
  }
};

using Nodes = std::vector<Node>;

Nodes parse() {
  Nodes nodes{};
  Node node{};
  char unused{};
  while (std::cin >> node.x >> unused >> node.y >> unused >> node.z) {
    nodes.push_back(node);
  }

  return nodes;
}

Num connect(Nodes nodes, bool part1) {
  std::priority_queue<Edge> candidates{};
  std::vector<std::set<Node*>> circuits{};

  for (auto& node : nodes) {
    node.circuit = circuits.size();
    circuits.push_back({&node});
  }

  for (size_t i = 0; i < nodes.size(); i++) {
    for (size_t j = i + 1; j < nodes.size(); j++) {
      candidates.push(Edge{&nodes[i], &nodes[j]});
    }
  }


  for (size_t i = 0; !candidates.empty(); i++) {
    const auto edge = candidates.top();
    candidates.pop();
    if (edge.n1->circuit != edge.n2->circuit) {
      auto& emptying = circuits[edge.n2->circuit];
      for (auto node : emptying) {
        circuits[edge.n1->circuit].insert(node);
        node->circuit = edge.n1->circuit;
      }
      emptying.clear();
    }

    
    if (part1 && i == 999) {
      std::ranges::sort(circuits, [](const auto& e1, const auto& e2) { return e1.size() > e2.size(); });
      return circuits[0].size() * circuits[1].size() * circuits[2].size();
    } else if (!part1 && circuits[edge.n1->circuit].size() == nodes.size()) {
      return edge.n1->x * edge.n2->x;
    }
  }

  assert(false);
}

int main() {
  auto nodes = parse();
  std::println("Part 1 result = {}", connect(nodes, true));
  std::println("Part 2 result = {}", connect(nodes, false));
  return 0;
}
