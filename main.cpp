/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: MSCS
 *
 * Created on 12 March 2020, 8:38 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include "board.h"
#include "agent.h"
#include "board.cpp"
#include "agent.cpp"
#include "cell.cpp"
#include "cell.h"


using namespace std;

int main(int argc, char** argv) {
        time_t now = time(NULL);
        srand(now);
        cout<<"Seed: "<<now<<endl;
        board abalone;
        string state(abalone);
        cout<<"Initial State:"<<endl<<state;
        agent* w = new randAgent('O');
        agent* b = new distAgent('@');
        movement* pom=nullptr;//previous opponent's move
        movement* mym=nullptr;//player's chosen move
        char c='O';
        int i =1;
        cout<< "choose the game mode (A) for Automatic AND (S) for pre-stored moves:"<<endl;
        char mode ;
        cin >> mode;
        if(mode == 'a'|| mode == 'A'){ 
         while(abalone.inPlay()){ //******terminate the game when either black or white marbles are removed out from the board***********
             try{
                    if(c=='O'){
                     movement mm = w->move(pom,abalone);
                     mym = new movement(mm);
                        if(pom)
                            delete pom;
                     pom = new movement(mm);
                }
                else{
                    movement mm = b->move(pom,abalone);
                    mym = new movement(mm);
                    if(pom)
                        delete pom;
                    pom = new movement(mm);
                }
            }
            catch(const string& s){
                cout<<s;
                return 1;
            }        
            bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);
            cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
            if(valid){
                string state(abalone);         
                cout<<"Next State:"<<endl<<state; 
            }
            else{
                cout<<"Invalid move!!"<<endl;
            }
            if(c=='O') 
                c='@';
            else
                c='O'; 
            delete mym;
            SLP(1);
            //system(CL);
            i++;               //*****it incrementing the number of moves by 1 until the game is terminated after either black or white 6 marbles are terminated******
        }
        }
        else if(mode== 's' || mode == 'S'){
               if(argc==1){
                    ifstream log("moves.txt");//sequence of game moves
                    string l;
                    int n, fd, md;
                    while(log>>c>>l>>n>>fd>>md){
                        cout<<"Move: "<<c<<" "<<l<<" "<<n<<" "<<fd<<" "<<md <<endl;
                        bool valid = abalone.executeMove(c,l,n,fd,md);
                        if(valid){
                            string nbs(abalone);
                            cout<<" - Next Abalone board state:"<<endl;
                            cout<<nbs<<endl;
                        }
                        else{
                            cout<<" - Invalid move!"<<endl;
                        }
                    }    
                }

            }
            else{
                throw std::invalid_argument("invalid option");
            }

        if(pom)
            delete pom;
        delete w;
        delete b;
        cout<<"Traverse Diagonal:"<<endl;
        cout<<abalone.traverseDiagonal()<<endl;
        cout<<"Traverse Horizontal:"<<endl;
        cout<<abalone.traverseHorizontal()<<endl;
        return 0;
}

