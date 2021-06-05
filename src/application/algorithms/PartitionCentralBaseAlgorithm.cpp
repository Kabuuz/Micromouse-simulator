#include <QDebug>
#include <application/algorithms/PartitionCentralBaseAlgorithm.hpp>
#include <map>
#include <vector>

namespace application
{
namespace algorithms
{
    PartitionCentralBaseAlgorithm::PartitionCentralBaseAlgorithm(std::string name,
                                                                 std::string parametersString) :
        Algorithm(name, parametersString),
        centerLeftAlgorithmPtr_(
            std::make_shared<CenterLeftAlgorithm>("CenterLeftAlgorithm", parametersString)),
        centerRightAlgorithmPtr_(
            std::make_shared<CenterRightAlgorithm>("CenterRightAlgorithm", parametersString)),
        leftWallAlgorithmPtr_(
            std::make_shared<LeftWallAlgorithm>("LeftWallAlgorithm", parametersString)),
        rightWallAlgorithmPtr_(
            std::make_shared<RightWallAlgorithm>("RightWallAlgorithm", parametersString)),
        partitions_(createPartitions())
    {}

    void
    PartitionCentralBaseAlgorithm::setMicromouse(std::shared_ptr<simulation::Micromouse> micromouse)
    {
        Algorithm::setMicromouse(micromouse);
        centerLeftAlgorithmPtr_->setMicromouse(micromouse);
        centerRightAlgorithmPtr_->setMicromouse(micromouse);
        leftWallAlgorithmPtr_->setMicromouse(micromouse);
        rightWallAlgorithmPtr_->setMicromouse(micromouse);
    }

    std::vector<Partition> PartitionCentralBaseAlgorithm::createPartitions()
    {
        return {{// 1
                 {simulation::Coordinates(0, 0)},
                 {simulation::Coordinates(6, 6)},
                 {{simulation::Direction::North, RightWallFollower},
                  {simulation::Direction::East, CenterRight},
                  {simulation::Direction::South, CenterLeft},
                  {simulation::Direction::West, LeftWallFollower}}},
                {// 2
                 simulation::Coordinates(7, 0),
                 simulation::Coordinates(7, 6),
                 {{simulation::Direction::North, RightWallFollower},
                  {simulation::Direction::East, RightWallFollower},
                  {simulation::Direction::South, CenterLeft},
                  {simulation::Direction::West, LeftWallFollower}}},
                {// 3
                 simulation::Coordinates(8, 0),
                 simulation::Coordinates(8, 6),
                 {{simulation::Direction::North, LeftWallFollower},
                  {simulation::Direction::East, RightWallFollower},
                  {simulation::Direction::South, CenterRight},
                  {simulation::Direction::West, LeftWallFollower}}},
                {// 4
                 simulation::Coordinates(9, 0),
                 simulation::Coordinates(15, 6),
                 {{simulation::Direction::North, LeftWallFollower},
                  {simulation::Direction::East, RightWallFollower},
                  {simulation::Direction::South, CenterRight},
                  {simulation::Direction::West, CenterLeft}}},
                {// 5
                 simulation::Coordinates(0, 7),
                 simulation::Coordinates(6, 7),
                 {{simulation::Direction::North, RightWallFollower},
                  {simulation::Direction::East, CenterRight},
                  {simulation::Direction::South, LeftWallFollower},
                  {simulation::Direction::West, LeftWallFollower}}},
                {// 6
                 simulation::Coordinates(9, 7),
                 simulation::Coordinates(15, 7),
                 {{simulation::Direction::North, LeftWallFollower},
                  {simulation::Direction::East, RightWallFollower},
                  {simulation::Direction::South, RightWallFollower},
                  {simulation::Direction::West, CenterLeft}}},
                {// 7
                 simulation::Coordinates(0, 8),
                 simulation::Coordinates(6, 8),
                 {{simulation::Direction::North, RightWallFollower},
                  {simulation::Direction::East, CenterLeft},
                  {simulation::Direction::South, LeftWallFollower},
                  {simulation::Direction::West, RightWallFollower}}},
                {// 8
                 simulation::Coordinates(9, 8),
                 simulation::Coordinates(15, 8),
                 {{simulation::Direction::North, LeftWallFollower},
                  {simulation::Direction::East, LeftWallFollower},
                  {simulation::Direction::South, RightWallFollower},
                  {simulation::Direction::West, CenterRight}}},
                {// 9
                 simulation::Coordinates(0, 9),
                 simulation::Coordinates(6, 15),
                 {{simulation::Direction::North, CenterRight},
                  {simulation::Direction::East, CenterLeft},
                  {simulation::Direction::South, LeftWallFollower},
                  {simulation::Direction::West, RightWallFollower}}},
                {// 10
                 simulation::Coordinates(7, 9),
                 simulation::Coordinates(7, 15),
                 {{simulation::Direction::North, CenterRight},
                  {simulation::Direction::East, LeftWallFollower},
                  {simulation::Direction::South, LeftWallFollower},
                  {simulation::Direction::West, RightWallFollower}}},
                {// 11
                 simulation::Coordinates(8, 9),
                 simulation::Coordinates(8, 15),
                 {{simulation::Direction::North, CenterLeft},
                  {simulation::Direction::East, LeftWallFollower},
                  {simulation::Direction::South, RightWallFollower},
                  {simulation::Direction::West, RightWallFollower}}},
                {// 12
                 simulation::Coordinates(9, 9),
                 simulation::Coordinates(15, 15),
                 {{simulation::Direction::North, LeftWallFollower},
                  {simulation::Direction::East, LeftWallFollower},
                  {simulation::Direction::South, RightWallFollower},
                  {simulation::Direction::West, CenterRight}}}};
    }

    void PartitionCentralBaseAlgorithm::runStep()
    {
        auto PartitionIt = getCurrentPartition(micromouse_->getCoordinates());

        if (PartitionIt == partitions_.end())
        {
            qCritical() << QString::fromStdString(name_) << "No partition found";
        }
        else
        {
            std::shared_ptr<Algorithm> algorithm
                = getAlgorithm(*PartitionIt, micromouse_->getDirection());

            if (algorithm != nullptr)
            {
                algorithm->runStep();
            }
            else
            {
                qCritical() << QString::fromStdString(name_) << "No algorithm found";
            }
        }
    }

    std::vector<Partition>::iterator
    PartitionCentralBaseAlgorithm::getCurrentPartition(simulation::Coordinates& coordinates)
    {
        auto partitionIt
            = std::find_if(partitions_.begin(), partitions_.end(), [&coordinates](auto& partition) {
                  return (coordinates.getX() >= partition.leftUpPosition.getX()
                          && coordinates.getX() <= partition.rightDownPosition.getX()
                          && coordinates.getY() >= partition.leftUpPosition.getY()
                          && coordinates.getY() <= partition.rightDownPosition.getY());
              });

        return partitionIt;
    }

    std::shared_ptr<Algorithm>
    PartitionCentralBaseAlgorithm::getAlgorithm(Partition& partition,
                                                simulation::Direction& direction)
    {
        auto directionAndAlgorithmTypeIt = partition.algorithmMap.find(direction);

        if (directionAndAlgorithmTypeIt == partition.algorithmMap.end())
        {
            return nullptr;
        }

        AlgorithmEnum algorithmType = directionAndAlgorithmTypeIt->second;

        if (algorithmType == CenterLeft)
        {
            return centerLeftAlgorithmPtr_;
        }
        else if (algorithmType == CenterRight)
        {
            return centerRightAlgorithmPtr_;
        }
        else if (algorithmType == LeftWallFollower)
        {
            return leftWallAlgorithmPtr_;
        }
        else
        {
            return rightWallAlgorithmPtr_;
        }
    }

}   // namespace algorithms
}   // namespace application
