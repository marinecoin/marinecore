#ifndef MARINECORE_CHECKPOINT_H
#define  MARINECORE_CHECKPOINT_H

#include <map>

class uint256;
class CBlockIndex;

namespace Checkpoints
{
    bool CheckBlock(int nHeight, const uint256& hash);

    int GetTotalBlocksEstimate();

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex);
}

#endif
