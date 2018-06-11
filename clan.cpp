
#include "clan.h"
#include "Oasis.h"

#include <iostream>
using namespace std;

/*----------------------------------------------------------------------------*/
Clan::Clan(int new_clan_id, ArrayHeap* heap_node) :
        clan_id(new_clan_id), is_valid(true), players(new Avl_tree<int, int>), num_of_players(
        0), heap_clan(heap_node) {
}
/*----------------------------------------------------------------------------*/
int Clan::GetClanId(){
    return clan_id;
}
/*----------------------------------------------------------------------------*/
Clan::~Clan(){
    delete players;
}
/*----------------------------------------------------------------------------*/
CLAN_RESULT Clan::AddPlayer(int player_id,int score){
    if (!players->Insert(player_id,score)){
        return PLAYER_ALREADY_EXIST;
    }
    num_of_players++;
    return PLAYER_ADDED;
}
/*----------------------------------------------------------------------------*/
Avl_tree<int, int>* Clan::GetPlayers(){
    return players;
}
/*----------------------------------------------------------------------------*/
int Clan::GetNumOfPlayers(){
    return num_of_players;
}
/*----------------------------------------------------------------------------*/
bool Clan::GetValidity(){
    return is_valid;
}
/*----------------------------------------------------------------------------*/
ArrayHeap* Clan::SetValidityToFalse(){
    is_valid=false;
    ArrayHeap* temp=heap_clan;
    heap_clan=NULL;
    return temp;
}
/*----------------------------------------------------------------------------*/
int Clan::GetSumOfBestPlayers(int num){
    if(num==0){
        return 0;
    }
    int sum=players->selcet(num_of_players-num+1, players->getRoot(),0);
    //cout <<"The player is:"<<sum<<endl;

    return sum;
}
/*----------------------------------------------------------------------------*/
ArrayHeap* Clan::GetHeapClan(){
    return heap_clan;
}
/*----------------------------------------------------------------------------*/







