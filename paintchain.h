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
    int add_block(PaintBlock new_block);
    PaintBlock get_block(uint32_t block_index);

private:
    uint32_t _difficulty;
    vector<PaintBlock> _chain;
    PaintBlock _get_last_block() const;
};

#endif // PAINTCHAIN_H
