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
    Oasis(int n, int *clanIDs,StatusType& status);
    ~Oasis();
    StatusType OasisAddClan(int clanID);
    StatusType OasisAddPlayer(int playerID, int score, int clan);
    StatusType OasisClanFight(int clan1, int clan2, int k1, int k2);
    StatusType OasisGetMinClan(int *clan);
    void OasisPrint();
    void OasisPrintActionResult(StatusType result);
};

#endif //DATA_STRCTURE2

