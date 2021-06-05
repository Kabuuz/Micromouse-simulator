#include <application/algorithms/Node.hpp>

namespace application
{
namespace algorithms
{
    Node::Node(simulation::Coordinates coordinates, Node* parent) :
        coordinates_(coordinates), parent_(parent)
    {}

    void Node::addChild(simulation::Coordinates coordinates)
    {
        children_.push_back(std::make_unique<Node>(coordinates, this));
    }

    std::vector<std::unique_ptr<Node>>& Node::getChildren()
    {
        return children_;
    }

    simulation::Coordinates& Node::getCoordinates()
    {
        return coordinates_;
    }

    Node* Node::getParent()
    {
        return parent_;
    }

}   // namespace algorithms
}   // namespace application
