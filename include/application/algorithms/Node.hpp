#ifndef APPLICATION_ALGORITHM_NODE_HPP
#define APPLICATION_ALGORITHM_NODE_HPP

#include <memory>
#include <simulation/Coordinates.hpp>
#include <vector>

namespace application
{
namespace algorithms
{
    class Node
    {
      public:
        Node(simulation::Coordinates coordinates, Node* parent = nullptr);
        void addChild(simulation::Coordinates coordinates);
        std::vector<std::unique_ptr<Node>>& getChildren();
        simulation::Coordinates& getCoordinates();
        Node* getParent();

      private:
        simulation::Coordinates coordinates_;
        Node* parent_;
        std::vector<std::unique_ptr<Node>> children_;
    };

}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_NODE_HPP
