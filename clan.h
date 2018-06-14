#ifndef CLAN_H_
#define CLAN_H_

#include "avl_tree.h"
#include "Min_heap.h"

//Results value:
typedef enum clan_result{
    PLAYER_ALREADY_EXIST,
    PLAYER_ADDED,
}CLAN_RESULT;

class Clan {
private:
    int clan_id;
    bool is_valid;
    Avl_tree<int, int>* players;
    int num_of_players;
    ArrayHeap* heap_clan;

public:
    // constructor & destrcutor
    Clan(int new_clan_id,ArrayHeap* heap_node);
    ~Clan();

    // set null all field
    void setNull();

    //get Clan-id
    int GetClanId();

    // get Validty
    bool GetValidity();

    // get HeapClan
    ArrayHeap* GetHeapClan();

    //setter set heap false
    ArrayHeap* SetValidityToFalse();

    // get NunPlayers
    int GetNumOfPlayers();

    // GetSumOf best Players
    int GetSumOfBestPlayers(int num);

    // get Players in tree
    Avl_tree<int, int>* GetPlayers();

    //add Player to clan
    CLAN_RESULT AddPlayer(int player_id,int score);
};


#endif /* CLAN_H_ */