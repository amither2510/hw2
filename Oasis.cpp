
#include "Oasis.h"
#include <iostream>
using namespace std;

typedef enum {
    ADD_CLAN = 0,
    ADD_PLAYER = 1,
    CLAN_FIGHT = 2
} CONVERT_TYPE;

/*----------------------------------------------------------------------------*/
StatusType ConvertResult(HASH_RESULT hash_result, CONVERT_TYPE convert_type) {
    if (convert_type == ADD_CLAN) {
        if (hash_result == HASH_INVALID_INPUT) {
            return INVALID_INPUT;
        } else if (hash_result == HASH_CLAN_ALREADY_EXISTS) {
            return FAILURE;
        } else if (hash_result == HASH_ALLOCATION_ERROR) {
            return ALLOCATION_ERROR;
        } else if (hash_result == HASH_CLAN_ADDED) {
            return SUCCESS;
        } else {
            return FAILURE;
        }
    } else if (convert_type == ADD_PLAYER) {
        if (hash_result == HASH_INVALID_INPUT) {
            return INVALID_INPUT;
        } else if (hash_result == HASH_CLAN_DOES_NOT_EXISTS) {
            return FAILURE;
        }else if (hash_result == HASH_PLAYER_ALREADY_EXISTS) {
            return FAILURE;
        }else if (hash_result == HASH_ALLOCATION_ERROR) {
            return ALLOCATION_ERROR;
        } else if (hash_result == HASH_PLAYER_ADDED) {
            return SUCCESS;
        } else {
            return FAILURE;
        }
    } else if (convert_type ==CLAN_FIGHT){
        if (hash_result ==HASH_FIGHT_FAILURE ) {
            return FAILURE;
        } else if (hash_result == HASH_FIGHT_SUCCESS) {
            return SUCCESS;
        }
    }
    return FAILURE;
}
/*----------------------------------------------------------------------------*/
StatusType Oasis::OasisAddClan(int clanID) {
    ArrayHeap* temp_heap_clan=heap->CreateTempHeapClan(clanID);
    if (temp_heap_clan==NULL){
        return ALLOCATION_ERROR;
    }

    HASH_RESULT res = INITIAL;
    res = hash_table->HashInsertClan(clanID,temp_heap_clan);
    if ((ConvertResult(res,ADD_CLAN))==SUCCESS){
        heap->AddClan(temp_heap_clan);
        return (ConvertResult(res,ADD_CLAN));
    }
    if (ConvertResult(res,ADD_CLAN)!=SUCCESS){
        delete temp_heap_clan;
    }
    return (ConvertResult(res,ADD_CLAN));
}
/*----------------------------------------------------------------------------*/
StatusType Oasis::OasisAddPlayer(int playerID, int score, int clan) {
    HASH_RESULT res = INITIAL;
    if(oasis_players->Is_Contain(oasis_players->getRoot(),playerID)){
        return FAILURE;
    }
    res = hash_table->HashInsertPlayer(clan, playerID, score);
    if (res!=HASH_PLAYER_ADDED){
        return (ConvertResult(res, ADD_PLAYER));
    }
    if (!oasis_players->InsertOasis(playerID,playerID)){
        return ALLOCATION_ERROR;
    }
    return (ConvertResult(res, ADD_PLAYER));
}
/*----------------------------------------------------------------------------*/
StatusType Oasis::OasisClanFight(int clan1, int clan2, int k1, int k2){
    HASH_RESULT res = INITIAL;
    ArrayHeap* clan_heap=NULL;
    res=hash_table->HashFight(clan1, clan2, k1, k2,&clan_heap);
    if( clan_heap!=NULL){
        heap->deleteHeap(clan_heap);
    }
    return (ConvertResult(res,CLAN_FIGHT));

   // return FAILURE;
}
/*----------------------------------------------------------------------------*/
Oasis::Oasis(int n, int *clanIDs,StatusType& status){
    hash_table=new DynamicHash(2*n);
    heap=new Heap(2*n);
    oasis_players=new Avl_tree<int, int>;
    for (int i=0;i<n;i++){
        if (OasisAddClan(clanIDs[i])!=SUCCESS){
            delete hash_table;
            delete heap;
            delete oasis_players;
            status= FAILURE;
            return;
        }
    }
    status= SUCCESS;
}
/*----------------------------------------------------------------------------*/
StatusType Oasis::OasisGetMinClan(int *clan){
    if (hash_table->GetNumClans()==0){
        return FAILURE;
    }
    *clan=heap->GetMinClanId();
    return SUCCESS;
}
/*----------------------------------------------------------------------------*/
Oasis::~Oasis(){
    delete hash_table;
    delete heap;
    delete oasis_players;
}
/*----------------------------------------------------------------------------*/
void Oasis::OasisPrint(){
    cout<<"Printing Hash:"<<endl;
    hash_table->PrintHash();
    cout<<"Printing Heap:"<<endl;
    heap->PrintHeap();
   // cout<<"Printing System:"<<endl;
   // heap->PrintHeap();
}
/*----------------------------------------------------------------------------*/
void Oasis::OasisPrintActionResult(StatusType result){
    if (result==0){
        cout<<"SUCCESS"<<endl;
    } else if (result==-1){
        cout<<"FAILURE"<<endl;
    } else if (result==-2){
        cout<<"ALLOCATION_ERROR"<<endl;
    } else if (result==-3){
        cout<<"INVALID_INPUT"<<endl;
    }
}
/*----------------------------------------------------------------------------*/
