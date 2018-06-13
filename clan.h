#ifndef CLAN_H_
#define CLAN_H_

#include "avl_tree.h"
#include "Min_heap.h"

//Results value:
typedef enum clan_result{
    PLAYER_ALREADY_EXIST,
    PLAYER_ADDED,
    //CLAN_ALLOCATION_ERROR,
    //LIST_CLAN_ADDED,
    //LIST_CLAN_ALREADY_EXISTS,
}CLAN_RESULT;

class Clan {
private:
    int clan_id;
    bool is_valid;
    Avl_tree<int, int>* players;
    int num_of_players;
    ArrayHeap* heap_clan;
public:
    Clan(int new_clan_id,ArrayHeap* heap_node);
    ~Clan();
    void setNull();
    int GetClanId();
    bool GetValidity();
    ArrayHeap* GetHeapClan();
    ArrayHeap* SetValidityToFalse();
    int GetNumOfPlayers();
    int GetSumOfBestPlayers(int num);
    Avl_tree<int, int>* GetPlayers();
    CLAN_RESULT AddPlayer(int player_id,int score);
};


#endif /* CLAN_H_ */