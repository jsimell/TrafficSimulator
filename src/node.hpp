#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "trafficlight.hpp"

/**
 * @brief An enum class for representing different node types. A node can be
 * either a Building or an Intersection.
 *
 */
enum class NodeType { Building, Intersection };

/**
 * @brief A class for representing a node in the simulated city. A node can be
 * either a Building or an Intersection, and two nodes can be  connected with a
 * Road object.
 *
 */
class Node {
 public:
  /**
   * @brief Construct a new Node object
   *
   * @param type The type of the node as NodeType (Building or Intersection)
   * @param location The coordinates of the node as std::pair<int, int>
   */
  Node(NodeType type, const std::pair<int, int> location);

  /**
   * @brief Returns the type of the node.
   *
   * @return A NodeType object (Building or Intersection)
   */
  NodeType GetType() const;

  /**
   * @brief Get the nodes that this node is connected to.
   *
   * @return std::vector<std::pair<Node*, int>>
   */
  std::vector<std::pair<Node*, int>> GetConnections() const;

  /**
   * @brief Connects this node with the node that is given as parameter
   *
   * @param node The node that the connection will be made with
   * @param weight The weight of the node that the connection is made with
   */
  void AddConnection(Node* node, int weight);

  /**
   * @brief Get the location of the node.
   *
   * @return The coordinates of the node as std::pair<int, int>
   */
  std::pair<int, int> GetLocation() const;

 private:
  NodeType type_;
  std::pair<int, int> location_;
  std::vector<std::pair<Node*, int>> connections_;
};

#endif
