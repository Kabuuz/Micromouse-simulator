#include <QDebug>
#include <application/algorithms/DepthFirstSearchAlgorithm.hpp>
#include <random>
#include <simulation/maze/MazeSettings.hpp>

namespace application
{
namespace algorithms
{
    namespace
    {
        constexpr int TURN_LEFT {0};
        constexpr int TURN_RIGHT {1};
    }   // namespace

    DepthFirstSearchAlgorithm::DepthFirstSearchAlgorithm(std::string name,
                                                         std::string parametersString) :
        Algorithm(name, parametersString)
    {}

    void
    DepthFirstSearchAlgorithm::setMicromouse(std::shared_ptr<simulation::Micromouse> micromouse)
    {
        Algorithm::setMicromouse(micromouse);
    }

    void DepthFirstSearchAlgorithm::runStep()
    {
        if (root_ == nullptr)
        {
            root_ = std::make_unique<Node>(micromouse_->getCoordinates());
            currentNode_ = root_.get();
        }

        if (currentNode_->getChildren().empty())
        {
            scanForChildren(currentNode_);
        }

        Node* child = drawAvailableChildFromNode(currentNode_);

        if (child == nullptr)
        {
            goToNode(currentNode_, currentNode_->getParent());
        }
        else
        {
            goToNode(currentNode_, child);
        }
    }

    void DepthFirstSearchAlgorithm::reset()
    {
        root_.release();
        currentNode_ = nullptr;
    }

    void DepthFirstSearchAlgorithm::scanForChildren(Node* node)
    {
        simulation::Coordinates& micromouseCoordinates = micromouse_->getCoordinates();
        simulation::Direction micromouseDirection = micromouse_->getDirection();

        std::map<simulation::Direction, simulation::Coordinates> neighbourCellsMap;
        std::vector directions {simulation::Direction::North,
                                simulation::Direction::East,
                                simulation::Direction::South,
                                simulation::Direction::West};

        int xMicromouseCoordinate = micromouseCoordinates.getX();
        int yMicromouseCoordinate = micromouseCoordinates.getY();

        for (auto direction : directions)
        {
            if (micromouse_->getMaze()
                    .getCell(micromouseCoordinates)
                    .getWall(direction)
                    .getWallState()
                == simulation::WallState::NotPresent)
            {
                if (direction == simulation::Direction::North)
                {
                    neighbourCellsMap[direction]
                        = simulation::Coordinates(xMicromouseCoordinate, yMicromouseCoordinate - 1);
                }
                else if (direction == simulation::Direction::East)
                {
                    neighbourCellsMap[direction]
                        = simulation::Coordinates(xMicromouseCoordinate + 1, yMicromouseCoordinate);
                }
                else if (direction == simulation::Direction::South)
                {
                    neighbourCellsMap[direction]
                        = simulation::Coordinates(xMicromouseCoordinate, yMicromouseCoordinate + 1);
                }
                else if (direction == simulation::Direction::West)
                {
                    neighbourCellsMap[direction]
                        = simulation::Coordinates(xMicromouseCoordinate - 1, yMicromouseCoordinate);
                }
            }
        }

        auto isCellBehindRobot = [&micromouseDirection](const auto& key) {
            return ((micromouseDirection == simulation::Direction::North
                     && key == simulation::Direction::South)
                    || (micromouseDirection == simulation::Direction::East
                        && key == simulation::Direction::West)
                    || (micromouseDirection == simulation::Direction::South
                        && key == simulation::Direction::North)
                    || (micromouseDirection == simulation::Direction::West
                        && key == simulation::Direction::East));
        };

        for (auto& [key, value] : neighbourCellsMap)
        {
            if (!isCellBehindRobot(key))   // ignore cell behind
            {
                node->addChild(value);
            }
        }
    }

    Node* DepthFirstSearchAlgorithm::drawAvailableChildFromNode(Node* node)
    {
        Node* availableChild = nullptr;
        std::vector<Node*> availableChildren;
        auto& children = node->getChildren();

        for (auto& child : children)
        {
            if (!wallBetweenNodesExist(node, child.get())
                && micromouse_->getVisitedArray()
                        .at(child->getCoordinates().getY())
                        .at(child->getCoordinates().getX())
                    == false)
            {
                availableChildren.push_back(child.get());
            }
        }

        if (!availableChildren.empty())
        {
            // choose random child from availableChildren
            std::random_device rd;
            std::mt19937 generator {rd()};
            std::uniform_int_distribution<int> range(0, availableChildren.size() - 1);
            availableChild = availableChildren.at(range(generator));
        }

        return availableChild;
    }

    bool DepthFirstSearchAlgorithm::wallBetweenNodesExist(Node* node1, Node* node2)
    {
        auto& maze = micromouse_->getMaze();
        simulation::Coordinates coordinatesOfFirstNode = node1->getCoordinates();
        int x1 = coordinatesOfFirstNode.getX();
        int y1 = coordinatesOfFirstNode.getY();
        simulation::Coordinates coordinatesOfSecondNode = node2->getCoordinates();
        int x2 = coordinatesOfSecondNode.getX();
        int y2 = coordinatesOfSecondNode.getY();

        simulation::Direction direction;

        if (y1 < y2)
        {
            direction = simulation::Direction::South;
        }
        else if (y1 > y2)
        {
            direction = simulation::Direction::North;
        }
        else if (x1 < x2)
        {
            direction = simulation::Direction::East;
        }
        else if (x1 > x2)
        {
            direction = simulation::Direction::West;
        }

        return (maze.getCell(y1, x1).getWall(direction).getWallState()
                == simulation::WallState::Present);
    }

    void DepthFirstSearchAlgorithm::goToNode(Node* currentNode, Node* nextNode)
    {
        if (nextNode != nullptr)
        {
            simulation::Coordinates& currentNodeCoordinates = currentNode->getCoordinates();
            simulation::Coordinates& nextNodeCoordinates = nextNode->getCoordinates();

            if (isRightNeighbourCell(currentNodeCoordinates, nextNodeCoordinates))
            {
                micromouse_->turnRight();
                micromouse_->moveForward();
            }
            else if (isLeftNeighbourCell(currentNodeCoordinates, nextNodeCoordinates))
            {
                micromouse_->turnLeft();
                micromouse_->moveForward();
            }
            else if (isFrontNeighbourCell(currentNodeCoordinates, nextNodeCoordinates))
            {
                micromouse_->moveForward();
            }
            else if (isBackNeighbourCell(currentNodeCoordinates, nextNodeCoordinates))
            {
                std::random_device rd;
                std::mt19937 generator {rd()};
                std::uniform_int_distribution<int> range(0, 1);
                int turnDirection = range(generator);
                if (turnDirection == TURN_LEFT)
                {
                    micromouse_->turnLeft();
                    micromouse_->turnLeft();
                    micromouse_->moveForward();
                }
                else if (turnDirection == TURN_RIGHT)
                {
                    micromouse_->turnRight();
                    micromouse_->turnRight();
                    micromouse_->moveForward();
                }
            }

            currentNode_ = nextNode;
        }
    }

    bool
    DepthFirstSearchAlgorithm::isRightNeighbourCell(simulation::Coordinates& currentCoordinates,
                                                    simulation::Coordinates& neighbourCoordinates)
    {
        simulation::Direction& micromouseDirection = micromouse_->getDirection();
        simulation::Coordinates rightNeighbour;
        int xMicromouseCoordinate = currentCoordinates.getX();
        int yMicromouseCoordinate = currentCoordinates.getY();

        switch (micromouseDirection)
        {
            case simulation::Direction::North:
                rightNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate + 1, yMicromouseCoordinate);
                break;
            case simulation::Direction::East:
                rightNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate, yMicromouseCoordinate + 1);
                break;
            case simulation::Direction::South:
                rightNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate - 1, yMicromouseCoordinate);
                break;
            case simulation::Direction::West:
                rightNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate, yMicromouseCoordinate - 1);
                break;
        }

        return rightNeighbour == neighbourCoordinates;
    }

    bool
    DepthFirstSearchAlgorithm::isLeftNeighbourCell(simulation::Coordinates& currentCoordinates,
                                                   simulation::Coordinates& neighbourCoordinates)
    {
        simulation::Direction& micromouseDirection = micromouse_->getDirection();
        simulation::Coordinates leftNeighbour;
        int xMicromouseCoordinate = currentCoordinates.getX();
        int yMicromouseCoordinate = currentCoordinates.getY();

        switch (micromouseDirection)
        {
            case simulation::Direction::North:
                leftNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate - 1, yMicromouseCoordinate);
                break;
            case simulation::Direction::East:
                leftNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate, yMicromouseCoordinate - 1);
                break;
            case simulation::Direction::South:
                leftNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate + 1, yMicromouseCoordinate);
                break;
            case simulation::Direction::West:
                leftNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate, yMicromouseCoordinate + 1);
                break;
        }

        return leftNeighbour == neighbourCoordinates;
    }

    bool
    DepthFirstSearchAlgorithm::isFrontNeighbourCell(simulation::Coordinates& currentCoordinates,
                                                    simulation::Coordinates& neighbourCoordinates)
    {
        simulation::Direction& micromouseDirection = micromouse_->getDirection();
        simulation::Coordinates frontNeighbour;
        int xMicromouseCoordinate = currentCoordinates.getX();
        int yMicromouseCoordinate = currentCoordinates.getY();

        switch (micromouseDirection)
        {
            case simulation::Direction::North:
                frontNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate, yMicromouseCoordinate - 1);
                break;
            case simulation::Direction::East:
                frontNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate + 1, yMicromouseCoordinate);
                break;
            case simulation::Direction::South:
                frontNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate, yMicromouseCoordinate + 1);
                break;
            case simulation::Direction::West:
                frontNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate - 1, yMicromouseCoordinate);
                break;
        }

        return frontNeighbour == neighbourCoordinates;
    }

    bool
    DepthFirstSearchAlgorithm::isBackNeighbourCell(simulation::Coordinates& currentCoordinates,
                                                   simulation::Coordinates& neighbourCoordinates)
    {
        simulation::Direction& micromouseDirection = micromouse_->getDirection();
        simulation::Coordinates backNeighbour;
        int xMicromouseCoordinate = currentCoordinates.getX();
        int yMicromouseCoordinate = currentCoordinates.getY();

        switch (micromouseDirection)
        {
            case simulation::Direction::North:
                backNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate, yMicromouseCoordinate + 1);
                break;
            case simulation::Direction::East:
                backNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate - 1, yMicromouseCoordinate);
                break;
            case simulation::Direction::South:
                backNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate, yMicromouseCoordinate - 1);
                break;
            case simulation::Direction::West:
                backNeighbour
                    = simulation::Coordinates(xMicromouseCoordinate + 1, yMicromouseCoordinate);
                break;
        }

        return backNeighbour == neighbourCoordinates;
    }

}   // namespace algorithms
}   // namespace application
