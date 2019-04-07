#include "paintblock.h"
#include "sha256.h"

//SmartContract::SmartContract()
//{

//}

Pixel::Pixel(){

}

PixelGrid::PixelGrid(){

}


PaintBlock:: PaintBlock(){

}

PaintBlock::PaintBlock(uint32_t index_in, const PixelGrid &pixel_grid){
    _nonce = -1;
    _time = time(nullptr);
}

string PaintBlock::get_hash(){
    return _hash;
}
