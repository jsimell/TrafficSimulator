#include "node.hpp"

Node::Node(NodeType type, const std::pair<int, int> location)
    : type_(type), location_(location) {}

std::pair<int, int> Node::GetLocation() const { return location_; }

NodeType Node::GetType() const { return type_; }

std::vector<std::pair<Node*, int>> Node::GetConnections() const {
  return connections_;
}

void Node::AddConnection(Node* node, int weight) {
  connections_.push_back({node, weight});
}
