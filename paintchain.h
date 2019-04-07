#ifndef PAINTCHAIN_H
#define PAINTCHAIN_H
#include <cstdint>
#include <vector>
#include "paintblock.h"

using namespace std;

class PaintChain
{
public:
    PaintChain();
    int AddBlock(PaintBlock new_block);

private:
    uint32_t _nDifficulty;
    vector<PaintBlock> _chain;
    PaintBlock _get_last_block() const;
};

#endif // PAINTCHAIN_H
