#ifndef SIMULATION_IALGORITHM_HPP
#define SIMULATION_IALGORITHM_HPP

namespace simulation
{
class IAlgorithm
{
  public:
    IAlgorithm() = default;
    virtual ~IAlgorithm() = default;
    virtual void runStep() = 0;
    virtual void reset() = 0;
};
}   // namespace simulation

#endif // SIMULATION_IALGORITHM_HPP
