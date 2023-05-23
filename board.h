/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   board.h
 * Author: MSCS
 *
 * Created on 12 March 2020, 8:55 AM
 */

#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <map>
#include <sstream>

using namespace std;

class board{
    vector<cell*> rows;
    map<string,cell*> cells;
    int woc;//white marbles off the board count.
    int boc;//black marbles off the board count.
    void mapCells(cell* row,const char& r,const int& z);
public:
    board();//create 37 cells on the heap, and connect them.
    board(const board&);//copy constructor
    ~board();//recycle 37 cells.
    map<string,cell*> getCells() const;
    bool inPlay() const;
    operator std::string() const;//cast this object into a string.
    string traverseHorizontal() const;
    string traverseDiagonal() const;
    bool validateMove(const char& m,const string& l,const int& n, const int& fd, const int& md,int& mtype,bool& scoreMove) const;
    bool executeMove(const char& m,const string& l,const int& n, const int& fd, const int& md);
    void refreshOffboardCounts(string & winneR); // keeps track of black and white remaining  marbles
};



#endif /* BOARD_H */

