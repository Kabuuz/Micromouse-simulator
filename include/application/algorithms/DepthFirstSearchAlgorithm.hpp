#ifndef APPLICATION_ALGORITHM_DEPTHFIRSTSEARCHALGORITHM_HPP
#define APPLICATION_ALGORITHM_DEPTHFIRSTSEARCHALGORITHM_HPP

#include <QString>
#include <application/algorithms/Algorithm.hpp>
#include <application/algorithms/Node.hpp>

namespace application
{
namespace algorithms
{
    class DepthFirstSearchAlgorithm : public Algorithm
    {
      public:
        DepthFirstSearchAlgorithm(std::string name, std::string parametersString);
        virtual void runStep() override;
        virtual void reset() override;
        virtual void setMicromouse(std::shared_ptr<simulation::Micromouse> micromouse) override;

      private:
        Node* drawAvailableChildFromNode(Node* node);
        void goToNode(Node* currentNode, Node* nextNode);
        void scanForChildren(Node* node);
        bool isRightNeighbourCell(simulation::Coordinates& currentCoordinates,
                                  simulation::Coordinates& neighbourCoordinates);
        bool isLeftNeighbourCell(simulation::Coordinates& currentCoordinates,
                                 simulation::Coordinates& neighbourCoordinates);
        bool isFrontNeighbourCell(simulation::Coordinates& currentCoordinates,
                                  simulation::Coordinates& neighbourCoordinates);
        bool isBackNeighbourCell(simulation::Coordinates& currentCoordinates,
                                 simulation::Coordinates& neighbourCoordinates);
        bool wallBetweenNodesExist(Node* node1, Node* node2);

        std::unique_ptr<Node> root_;
        Node* currentNode_;
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_DEPTHFIRSTSEARCHALGORITHM_HPP
