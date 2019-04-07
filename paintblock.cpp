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

PaintBlock::PaintBlock(uint32_t index_in, const PixelGrid &pixel_grid, string data){
    _index = index_in;
    _pixel_grid = pixel_grid;
    _data = data;
    _nonce = -1;
    _time = time(nullptr);

}

/*
 * This "mines a block" which effectively creates a new block to put onoto the block chain
 * To create a valid block, first count the number of zeros at beginning of private variable _hash,
 * if the number of zeros in the hash is equal to or greater than the difficulty level
 * set by the network the paint chain will run on, then the block is valid. If the hash is not valid
 * the internal variable called nonce is incremented and a new hash is created and tested for validity.
 * This is a Proof of Work (POW) algorithm and is repeated until a hash is produced that is valid.
 */
void PaintBlock::mine_block(uint32_t n_difficulty){
    //create char array of size n_difficulty + 1
    stringstream ss;
    for(uint32_t i = 0; i < n_difficulty; i++){
        ss << "0";
    }
    //char cstr[n_difficulty];
    //zero at char array
    //for(uint32_t i = 0; i < n_difficulty; i++){
    //    cstr[i] = '0';
    // }
    //create string from char array
    string hash_substr = "";
    //string str(cstr);
    string str = ss.str();
    do {
        cout << "Calculating Hash nonce " << _nonce << endl;
        //increment _nonce and calculate new hash
        _nonce ++;
        _hash = _calculate_hash();
        cout << "Hash: " << _hash << endl;
        hash_substr = _hash.substr(0, n_difficulty);
    //check if
    //if the hash string from indexes 0 to n_difficulty are not all zeros
    //a new hash must be calculated otherwise a valid hash has been created
    }while( hash_substr != str);

    cout << "New Paint Block has been mined: " << _hash << endl;
}

string PaintBlock::get_hash(){
    return _hash;
}

inline string PaintBlock::_calculate_hash() const{
    stringstream ss;
    ss << _index << _time << _nonce << _data << prev_hash;
    return sha256(ss.str());
}
