#ifndef DATA_STRCTURE2
#define DATA_STRCTURE2

#include "dynmic_hash.h"
#include "Min_heap.h"
#include "libary2.h"

class Oasis {
private:
    DynamicHash* hash_table;
    Heap* heap;
    Avl_tree<int, int>* oasis_players; //tree by player id;
public:

    //Construtor
    Oasis(int n, int *clanIDs,StatusType& status);

    //Destrutor
    ~Oasis();

    //Addclan to sys
    StatusType OasisAddClan(int clanID);

    //Add Player to sys
    StatusType OasisAddPlayer(int playerID, int score, int clan);

    //Make 2 clan fight
    StatusType OasisClanFight(int clan1, int clan2, int k1, int k2);

    //get the valid of mim clan in sys
    StatusType OasisGetMinClan(int *clan);

    //print Oasis
    void OasisPrint();

    //print Oassis Print actionRes
    void OasisPrintActionResult(StatusType result);
};

#endif //DATA_STRCTURE2

