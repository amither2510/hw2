
#ifndef DYNAMIC_HASH_H_
#define DYNAMIC_HASH_H_

#include "linked_list.h"

//Results value:
typedef enum hash_result{
    INITIAL,
    HASH_ALLOCATION_ERROR,
    HASH_CREATED,
    HASH_CLAN_ADDED,
    HASH_CLAN_ALREADY_EXISTS,
    HASH_INVALID_INPUT,
    HASH_PLAYER_ALREADY_EXISTS,
    HASH_CLAN_DOES_NOT_EXISTS,
    HASH_PLAYER_ADDED,
    HASH_EXTENDED,
    HASH_REDUCED,
    HASH_FIGHT_FAILURE,
    HASH_FIGHT_SUCCESS
} HASH_RESULT;


//Dynamic Chained Hash table by clan ID:
class DynamicHash {
private:
    int table_size;
    int number_elements;
    List** array;
public:

    //Construtor
    DynamicHash(int initial_size);

    //Destrcutor
    ~DynamicHash();

    //InesrtClan
    HASH_RESULT HashInsertClan(int clan_id,ArrayHeap* heap_clan);

    //Inesrt Copy of the elem
    HASH_RESULT DynamicHashInsertClan(int clan_id,ArrayHeap* heap_clan,Clan* clan);

    //Inesrt Player
    HASH_RESULT HashInsertPlayer(int clan_id,int player_id,int score);

    //Iscontain
    bool DoesContain(int clan_id);

    //printHash
    void PrintHash();

    //print result of the hash
    void PrintHashResult(HASH_RESULT res);

    //GetClanData
    void HashGetClanData(int clan_id,int num_players_to_sum,bool& validity,int& players_sum,int& num_of_clans_players);

    //hashfight
    HASH_RESULT HashFight(int clan1, int clan2, int k1, int k2,ArrayHeap** clan_heap);

    //Check for lossing clan
    ArrayHeap* ClanLost(int clan_id);

    //get clan
    Clan* ReturnClan(int clan_id);

    //get num of clans
    int GetNumClans();

    //enlarge the array
    void enlargeArray();
};




#endif /* DYNAMIC_HASH_H_ */