
#include "dynmic_hash.h"

#include <iostream>
using namespace std;

/*----------------------------------------------------------------------------*/
DynamicHash::DynamicHash(int initial_size):table_size(initial_size),number_elements(0){
    array=new List*[initial_size];
    for (int i=0;i<initial_size;i++){
        array[i]=NULL;
    }
}
/*----------------------------------------------------------------------------*/
DynamicHash::~DynamicHash(){
    for (int i=0;i<table_size;i++){
        if (array[i]){
            delete (array[i]);
        }
    }
    delete[] array;
}
/*----------------------------------------------------------------------------*/
HASH_RESULT DynamicHash::HashInsertClan(int clan_id,ArrayHeap* heap_clan){
    cout<<"adding clan_id--------------------------------------------"<<clan_id<<endl;
    PrintHash();
    if (clan_id<0){
        return HASH_INVALID_INPUT;
    }
    if (DoesContain(clan_id)){
        return HASH_CLAN_ALREADY_EXISTS;
    }
    int index=clan_id%table_size;
    if (!array[index]){
        array[index]=new List;
    }
    if (array[index]->ListInsertClan(clan_id,heap_clan)==LIST_ALLOCATION_ERROR){
        return HASH_ALLOCATION_ERROR;
    }

    number_elements++;
    if (number_elements==table_size){
        if (HashExtend(array,table_size)==HASH_ALLOCATION_ERROR){
            return HASH_ALLOCATION_ERROR;
        }

    }
    PrintHash();
   /* if (number_elements==table_size/4){
        if (HashReduce(array,table_size)==HASH_ALLOCATION_ERROR){
            return HASH_ALLOCATION_ERROR;
        }
    }
    */
    return HASH_CLAN_ADDED;
}
/*----------------------------------------------------------------------------*/
//if clan does not exist returns NULL;
Clan* DynamicHash::ReturnClan(int clan_id) {
    if (table_size==0){
        return NULL;
    }
    int index = clan_id % table_size;
    if (index>(table_size-1)){
        return NULL;
    }
    if (!array[index]){
        return NULL;
    }
    ListNode* current_node = array[index]->GetHead();
    if (!current_node) {
        return NULL;
    }
    while (current_node) {
        if (current_node->GetClanId() == clan_id) {
            return current_node->GetClan();
        }
        current_node = current_node->GetNextNode();
    }
    return NULL;
}
/*----------------------------------------------------------------------------*/
HASH_RESULT DynamicHash::DynamicHashInsertClan(int clan_id,ArrayHeap* heap_clan){
    if (clan_id<0){
        return HASH_INVALID_INPUT;
    }
    int index=clan_id%table_size;
    if (!array[index]){
        array[index]=new List;
    }
    if (array[index]->ListInsertClan(clan_id,heap_clan)==LIST_ALLOCATION_ERROR){
        return HASH_ALLOCATION_ERROR;
    }

    return HASH_CLAN_ADDED;
}
/*----------------------------------------------------------------------------*/
bool DynamicHash::DoesContain(int clan_id){
    if (ReturnClan(clan_id)==NULL){
        return false;
    } else {
        return true;
    }
}
/*----------------------------------------------------------------------------*/
HASH_RESULT DynamicHash::HashExtend(List** old_array,int old_size){
    int new_size=old_size*2;
    int old_num_elements=number_elements;
    List** new_array=NULL;
    try {
        new_array=new List*[new_size];
        for (int i=0;i<new_size;i++){
            new_array[i]=NULL;
        }
    } catch (std::bad_alloc &) {
        return HASH_ALLOCATION_ERROR;
    }

    array=new_array;
    table_size=new_size;

    for (int i=0;i<old_size;i++){
        if (old_array[i]) {
            ListNode* current_node = old_array[i]->GetHead();
            if (!current_node){
                continue;
            }
            //array[i]=new List;
            while (current_node) {
                DynamicHashInsertClan(current_node->GetClanId(),current_node->GetClan()->GetHeapClan());
                current_node = current_node->GetNextNode();
            }
            delete old_array[i];
        }
    }
    delete[] old_array;
    number_elements=old_num_elements;
    return HASH_EXTENDED;
}
/*----------------------------------------------------------------------------*/
HASH_RESULT DynamicHash::HashReduce(List** old_array,int old_size){
    int new_size=old_size/2;
    int old_num_elements=number_elements;
    List** new_array=NULL;
    try {
        new_array=new List*[new_size];
        for (int i=0;i<new_size;i++){
            new_array[i]=NULL;
        }
    } catch (std::bad_alloc &) {
        return HASH_ALLOCATION_ERROR;
    }

    array=new_array;
    table_size=new_size;

    for (int i = 0; i < old_size; i++) {
        if (old_array[i]) {
            ListNode* current_node = old_array[i]->GetHead();
            if (!current_node) {
                continue;
            }
            //array[i]=new List;
            while (current_node) {
                DynamicHashInsertClan(current_node->GetClanId(),current_node->GetClan()->GetHeapClan());
                current_node = current_node->GetNextNode();
            }
            delete old_array[i];
        }
    }
    delete[] old_array;
    number_elements=old_num_elements;
    return HASH_REDUCED;
}
/*----------------------------------------------------------------------------*/
HASH_RESULT DynamicHash::HashInsertPlayer(int clan_id, int player_id,
                                          int score) {
    if ((clan_id < 0) || (player_id < 0) || (score < 0)) {
        return HASH_INVALID_INPUT;
    }

    int clan_index = clan_id % table_size;
    if (clan_index>(table_size-1)){
        return HASH_CLAN_DOES_NOT_EXISTS;
    }
    List* clan_list = array[clan_index];
    if (!array[clan_index]){
        return HASH_CLAN_DOES_NOT_EXISTS;
    }
    LIST_RESULT res = clan_list->ListInsertPlayer(clan_id, player_id, score);

    if (res==LIST_CLAN_DOES_NOT_EXISTS){
        return HASH_CLAN_DOES_NOT_EXISTS;
    } else if (res==LIST_PLAYER_ALREADY_EXISTS){
        return HASH_PLAYER_ALREADY_EXISTS;
    } else if (res==LIST_ALLOCATION_ERROR){
        return HASH_ALLOCATION_ERROR;
    } else if (res==LIST_PLAYER_ADDED){
        return HASH_PLAYER_ADDED;
    }

    return HASH_PLAYER_ADDED;
}
/*----------------------------------------------------------------------------*/
//Debbug:
void DynamicHash::PrintHash(){
    cout << "--------------------------"<<endl;
    cout << "Table size = " <<table_size<< endl;
    cout << "Table Elements = " <<number_elements<< endl;
    cout << "--------------------------"<<endl;
    for (int i=0;i<table_size;i++){
        if (array[i]){
            ListNode* current_node = array[i]->GetHead();
            if (!current_node){
                continue;
            }
            int j=0;
            cout << "Clans in Table[" <<i<<"] are:"<< endl;
            while (current_node) {
                cout << "**************************Clan[" <<j<<"] = "<<current_node->GetClanId()<<endl;
                cout << "Validity = " <<current_node->GetClan()->GetValidity()<<endl;
                cout << "Its Players:" <<endl;
                Avl_tree<int, int>* clan_players=current_node->GetClan()->GetPlayers();
                clan_players->inorder(clan_players->getRoot());

                current_node = current_node->GetNextNode();
                j++;
            }
            cout << "-------"<< endl;
        }
    }
    cout<<endl;
}
/*----------------------------------------------------------------------------*/
//Debbug:
void DynamicHash::PrintHashResult(HASH_RESULT res){
    if (res==INITIAL){
        cout << "INITIAL" << endl;
    } else if (res==HASH_ALLOCATION_ERROR){
        cout << "HASH_ALLOCATION_ERROR" << endl;
    } else if (res==HASH_CREATED){
        cout << "HASH_CREATED" << endl;
    } else if (res==HASH_CLAN_ADDED){
        cout << "HASH_CLAN_ADDED" << endl;
    } else if (res==HASH_CLAN_ALREADY_EXISTS){
        cout << "HASH_CLAN_ALREADY_EXISTS" << endl;
    }else if (res==HASH_INVALID_INPUT){
        cout << "HASH_INVALID_INPUT" << endl;
    }else if (res==HASH_PLAYER_ALREADY_EXISTS){
        cout << "HASH_PLAYER_ALREADY_EXISTS" << endl;
    }else if (res==HASH_CLAN_DOES_NOT_EXISTS){
        cout << "HASH_CLAN_DOES_NOT_EXISTS" << endl;
    }else if (res==HASH_PLAYER_ADDED){
        cout << "HASH_PLAYER_ADDED" << endl;
    }else if (res==HASH_EXTENDED){
        cout << "HASH_EXTENDED" << endl;
    }else if (res==HASH_REDUCED){
        cout << "HASH_REDUCED" << endl;
    }
}
/*----------------------------------------------------------------------------*/
//need to test this function:
void DynamicHash::HashGetClanData(int clan_id, int num_players_to_sum,
                                  bool& validity, int& players_sum, int& num_of_clans_players) {
    if ((table_size == 0) || (DoesContain(clan_id) == false)) {
        validity = false;
        players_sum = 0;
        num_of_clans_players = 0;
        return;
    }
    Clan* actuall_clan = ReturnClan(clan_id);
    validity = actuall_clan->GetValidity();
    num_of_clans_players = actuall_clan->GetNumOfPlayers();
    //return players sum:
    if (num_players_to_sum == 0) {
        players_sum = 0;
    } else {
        players_sum = actuall_clan->GetSumOfBestPlayers(
                num_players_to_sum);
    }
}
/*----------------------------------------------------------------------------*/
HASH_RESULT DynamicHash::HashFight(int clan1, int clan2, int k1, int k2,ArrayHeap** clan_heap){
    if (clan1==clan2){
        return HASH_FIGHT_FAILURE;
    }
    if ((!DoesContain(clan1))||(!DoesContain(clan2))){
        cout<<"failed does not contain"<<endl;
        return HASH_FIGHT_FAILURE;
    }

    bool clan1_validity=false;
    bool clan2_validity=false;
    int clan1_players=0;
    int clan2_players=0;
    int clan1_players_sum=0;
    int clan2_players_sum=0;

    HashGetClanData(clan1, k1, clan1_validity, clan1_players_sum, clan1_players);
    HashGetClanData(clan2, k2, clan2_validity, clan2_players_sum, clan2_players);

    if ((clan1_validity==false)||(clan2_validity==false)){
        cout<<"failed validity"<<endl;
        return HASH_FIGHT_FAILURE;
    }
    if ((clan1_players<k1)||(clan2_players<k2)){
     //   cout<<"number of players 1---"<<clan1_players<<"number of players 2---"<<clan2_players<<endl;
        cout<<"failed num of players"<<endl;
        return HASH_FIGHT_FAILURE;
    }

    if (clan1_players_sum>clan2_players_sum){
        *clan_heap=ClanLost(clan2);
    } else if (clan2_players_sum>clan1_players_sum){
        *clan_heap=ClanLost(clan1);
    } else {
        if (clan1<clan2){
            *clan_heap=ClanLost(clan2);
        } else if (clan2<clan1){
            *clan_heap=ClanLost(clan1);
        }
    }

    return HASH_FIGHT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
//Unvalides a clan, if clan does not exist do nothing.
ArrayHeap* DynamicHash::ClanLost(int clan_id){
    Clan* actuall_clan = ReturnClan(clan_id);

    if (actuall_clan==NULL){
    } else {
        return actuall_clan->SetValidityToFalse();
    }
    return NULL;
}
/*----------------------------------------------------------------------------*/
int DynamicHash::GetNumClans(){
    return number_elements;
}
/*----------------------------------------------------------------------------*/



