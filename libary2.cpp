
#include "libary2.h"
#include "Oasis.h"


/* Implemintation for Interface for the Data Structure */

/*----------------------------------------------------------------------------*/
// init the sys
void* init(int n, int* clansIDs) {
    if ((n<2)||(clansIDs==NULL)){
        return NULL;
    }
    for (int i=0;i<n;i++){
        if (clansIDs[i]<0){
            return NULL;
        }
    }
    StatusType res=FAILURE;
    Oasis* DS = new Oasis(n, clansIDs,res);
    if (res==FAILURE){
        return NULL;
    }
    return (void*) DS;
}
/*----------------------------------------------------------------------------*/
// add clan to the system
StatusType addClan(void *DS, int clanID){
    if ((DS==NULL)||(clanID<0)){
        return INVALID_INPUT;
    }
    return ((Oasis*)DS)->OasisAddClan(clanID);
}
/*----------------------------------------------------------------------------*/
// addplayer to the system
StatusType addPlayer(void *DS, int playerID, int score, int clan){
    if ((DS==NULL)||(clan<0)||(playerID<0)||(score<0)){
        return INVALID_INPUT;
    }
    return ((Oasis*)DS)->OasisAddPlayer(playerID, score, clan);
}
/*----------------------------------------------------------------------------*/
// clanfight
StatusType clanFight(void *DS, int clan1, int clan2, int k1, int k2){
    if ((DS==NULL)||(k1<=0)||(k2<=0)||(clan1<0)||(clan2<0)){
        return INVALID_INPUT;
    }
    return ((Oasis*) DS)->OasisClanFight(clan1,clan2,k1,k2);
}
/*----------------------------------------------------------------------------*/
//getMinClan
StatusType getMinClan(void* DS, int* clan) {
    if ((DS==NULL)||(clan==NULL)){
        return INVALID_INPUT;
    }
    return ((Oasis*)DS)-> OasisGetMinClan(clan);
}

/*----------------------------------------------------------------------------*/
//quit
void quit(void** DS) {
    if (!DS)
        return;
    if (!(*DS))
        return;
    Oasis* ds = ((Oasis*) *DS);
    delete (ds);
    *DS = NULL;
}
/*----------------------------------------------------------------------------*/
//print system
void PrintSystem(void* DS){
    ((Oasis*)DS)->OasisPrint();
}
/*----------------------------------------------------------------------------*/
void PrintActionResult(void* DS,StatusType result){
    ((Oasis*)DS)->OasisPrintActionResult(result);
}
/*----------------------------------------------------------------------------*/



