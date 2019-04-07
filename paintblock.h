#ifndef SMARTCONTRACT_H
#define SMARTCONTRACT_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#define GRID_SIZE 512

using namespace std;

//class SmartContract
//{
//public:
//    SmartContract();
//};

class Pixel{
public:
    uint x_loc;
    uint y_loc;
    uint color;

    Pixel();
};

class PixelGrid{
public:
    uint grid_size;
    vector<vector<Pixel>> grid;

    PixelGrid();
    PixelGrid(vector<vector<Pixel>> pixel_grid);
};

class PaintBlock {
public:
    string s_prev_hash;
    PaintBlock();
    PaintBlock(uint32_t index_in, const PixelGrid &pixel_grid);
    //PixelGrid pixel_grid;
    string get_hash();
    void mine_block(uint32_t n_difficulty);
    void init_pixel_grid(PixelGrid pixel_grid);

private:
    uint32_t _index;
    int64_t _nonce;
    string _data;
    PixelGrid _pixel_grid;
    string _hash;
    time_t _time;

    string _calculate_hash() const;
};

#endif // SMARTCONTRACT_H
