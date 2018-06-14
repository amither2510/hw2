
#include "clan.h"
#include "Oasis.h"

#include <iostream>
using namespace std;


/**
 *  constructor
 * @param new_clan_id  - num of clan-id
 * @param heap_node   - pointer to the heap
 */
Clan::Clan(int new_clan_id, ArrayHeap* heap_node) :
        clan_id(new_clan_id), is_valid(true), players(new Avl_tree<int, int>), num_of_players(
        0), heap_clan(heap_node) {
}

/**
 * get ClanId
 * @return  id-clan
 */
int Clan::GetClanId(){
    return clan_id;
}

/**
 * Destructour
 */
Clan::~Clan(){
    delete players;
}

/**
 *  AddPlayer to tree of players
 * @param player_id  - player id to add
 * @param score  -  the score of the player
 * @return  Already Exist - if player is in clan
 * @return PlayerAdd - Success
 */
CLAN_RESULT Clan::AddPlayer(int player_id,int score){
    if (!players->Insert(player_id,score)){
        return PLAYER_ALREADY_EXIST;
    }
    num_of_players++;
    return PLAYER_ADDED;
}

/**
 * get players
 * @return  tree of players
 */
Avl_tree<int, int>* Clan::GetPlayers(){
    return players;
}

/**
 * GestnNumofPlayers in the clan
 * @return  num of player in clan
 */
int Clan::GetNumOfPlayers(){
    return num_of_players;
}

/**
 * getter of the validty
 * @return  if is valid
 */
bool Clan::GetValidity(){
    return is_valid;
}

/**
 * set the valid field to false
 * @return the clan pointer to the heap
 */
ArrayHeap* Clan::SetValidityToFalse(){
    is_valid=false;
    ArrayHeap* temp=heap_clan;
    heap_clan=NULL;
    return temp;
}

/**
 * get sum of the  score  of k players in clan
 * @param num - number of players to get
 * @return the score of all bigger players score
 */
int Clan::GetSumOfBestPlayers(int num){
    if(num==0){
        return 0;
    }
    int sum=players->selcet(num_of_players-num+1, players->getRoot(),0);
    return sum;
}

/**
 * GetheapClan
 * @return return the pointer to the clan
 */
ArrayHeap* Clan::GetHeapClan(){
    return heap_clan;
}

/**
 * set null all fied of the object
 */
void Clan::setNull(){
    this->heap_clan=NULL;
    this->players=NULL;
}






