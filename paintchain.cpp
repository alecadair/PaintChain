#include "paintchain.h"

PaintChain::PaintChain()
{
    PixelGrid grid;
    PaintBlock block(0, grid, "genesis_block");
    _chain.emplace_back(block);
    //for testing set difficulty to 4
    _difficulty = 4;
}

int PaintChain::add_block(PaintBlock new_block){
    //new_block.prev_hash = this->_get_last_block().get_hash();
    PaintBlock prev_block = this->_get_last_block();
    string prev_hash = prev_block.get_hash();
    new_block.prev_hash = prev_hash;
    new_block.mine_block(_difficulty);
    _chain.push_back(new_block);
    return 0;
}

PaintBlock PaintChain::_get_last_block() const{
    return _chain.back();
}
