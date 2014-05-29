#ifndef ROUND_ROBIN_PARTITIONER_H
#define ROUND_ROBIN_PARTITIONER_H

#include <vector>

#include "Partitioner.hpp"

namespace warped {

class SimulationObject;

class RoundRobinPartitioner : public Partitioner {
public:
    std::vector<std::vector<SimulationObject*>> partition(
             const std::vector<SimulationObject*>& objects,
             const unsigned int num_partitions) const;
};

} // namespace warped

#endif