#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (         0, uint256("0x8d86c6905181064a6d759049f9312959cfc582b043df781a1ec93319a20562af"))
            (       100, uint256("0x00a0379e91129de4c6374b11a2a2d7cee4fb5281f3e21a0b6e1bf37b5e2e4713"))
            (       300, uint256("0xab933ec52a6c63bad062bdab1f488d623d5c17865d2488f5a88c4974d3124317"))
            (       500, uint256("0x7ac6d54233a6149f0f47f0271afa9d654dbc85211a83458a83395e18ed699b56"))
            (       700, uint256("0x16e6277ee03d255368747ba87cded281fa58fc6eab4b1a180aafa061308d80a7"))
            (       900, uint256("0x122d993dff85a9e489198bb6f351d684170ab731dfd77653bef1f6b8e253017d"))
            (      1001, uint256("0x7e7b5cf01ebf05b985853a4e2160a8e11ba91670744e83e93cc6966c5ba03b6e"))
            (      10000, uint256("0xd87bda0caf7ed807b5cf4640567e942baf48fdc6d98307f0b517d9e519e4039d"))
            (      20000, uint256("0x6a94d408f05f9b70b6a5ac4dd50f11ad82547ca3b9e6c0a49ac30cbbe9141e71"))
            (      30000, uint256("0x06b4db6973ab45e31d48d120a8e531cdb981ac9de2daab51c184b49de9df6d25"))
            (      38500, uint256("0xeccd915c91c4673d33f84929ea2a4dab18183d233f173bcc4d1827bcbf49edf1"))  
            
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true;

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
