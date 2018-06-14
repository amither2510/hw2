
#include "dynmic_hash.h"

#include <iostream>
using namespace std;

/*----------------------------------------------------------------------------*/
/**
 * Construtor
 * @param initial_size  - size to init the array
 */
DynamicHash::DynamicHash(int initial_size):table_size(initial_size),number_elements(0){
    array=new List*[initial_size];
    for (int i=0;i<initial_size;i++){
        array[i]=NULL;
    }
}

/*----------------------------------------------------------------------------*/
/**
 * Destructor
 */
DynamicHash::~DynamicHash(){
    for (int i=0;i<table_size;i++){
        if (array[i]){
            delete (array[i]);
        }
    }
    delete[] array;
}
/*----------------------------------------------------------------------------*/
/**
 * Inesrt a new Clan to the Hash
 * @param clan_id
 * @param heap_clan
 * @return HASH_INVALID_INPUT
 * @return HASH_CLAN_ALREADY_EXISTS
 * @return HASH_ALLOCATION_ERROR
 * @return HASH_CLAN_ADDED
 */

HASH_RESULT DynamicHash::HashInsertClan(int clan_id,ArrayHeap* heap_clan){
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
        enlargeArray();
    }
    return HASH_CLAN_ADDED;
}

/*----------------------------------------------------------------------------*/
/**
 *  Check if clan is in
 * @param clan_id
 * @return  return the clan or NUll if is not inside
 */
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
/**
 * Insert a old clan / copy the clan to new aray
 * @param clan_id
 * @param heap_clan
 * @param clan
 * @return HASH_INVALID_INPUT
 * @return HASH_ALLOCATION_ERROR
 * @return HASH_CLAN_ADDED
 */
HASH_RESULT DynamicHash::DynamicHashInsertClan(int clan_id,ArrayHeap* heap_clan,Clan* clan){
    if (clan_id<0){
        return HASH_INVALID_INPUT;
    }
    int index=clan_id%table_size;
    if (!array[index]){
        array[index]=new List;
    }
    if (array[index]->ListInsertClan1(clan_id,heap_clan,clan)==LIST_ALLOCATION_ERROR){
        return HASH_ALLOCATION_ERROR;
    }

    return HASH_CLAN_ADDED;
}

/*----------------------------------------------------------------------------*/
/**
 * check if is contain
 * @param clan_id
 * @return  true if inside // false else
 */
bool DynamicHash::DoesContain(int clan_id){
    if (ReturnClan(clan_id)==NULL){
        return false;
    } else {
        return true;
    }
}


/*----------------------------------------------------------------------------*/
/**
 * Inesrt Player to clan
 * @param clan_id
 * @param player_id
 * @param score
 * @return HASH_PLAYER_ADDED
 * @return HASH_INVALID_INPUT
 * @return HASH_CLAN_DOES_NOT_EXISTS
 * @return HASH_PLAYER_ALREADY_EXISTS
 */
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

/**
 * Print The Hash
 */
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
/**
 * Print The Hash
 */
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
/**
 * Get all data that need for makeing the battle
 * @param clan_id
 * @param num_players_to_sum
 * @param validity - if is validty
 * @param players_sum - player sum of all bigger players in clan
 * @param num_of_clans_players  - sum of all players
 */
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
    if (num_players_to_sum == 0) {
        players_sum = 0;
    } else {
        players_sum = actuall_clan->GetSumOfBestPlayers(
                num_players_to_sum);
    }
}

/*----------------------------------------------------------------------------*/
/**
 * Hash fight ; make figt betwain to clan
 * @param clan1  - id of clan 1
 * @param clan2  - id of clan 2
 * @param k1  - number of player that is suppouse to be bigger clan1
 * @param k2   number of player that is suppouse to be bigger clan2
 * @param clan_heap  - pointer to the heap
 * @return HASH_FIGHT_FAILURE
 * @return  HASH_FIGHT_SUCCESS
 */
HASH_RESULT DynamicHash::HashFight(int clan1, int clan2, int k1, int k2,ArrayHeap** clan_heap){
    if (clan1==clan2){
        return HASH_FIGHT_FAILURE;
    }
    if ((!DoesContain(clan1))||(!DoesContain(clan2))){
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
        return HASH_FIGHT_FAILURE;
    }
    if ((clan1_players<k1)||(clan2_players<k2)){
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
/**
 *  remove the lossing clan out of the heap
 * @param clan_id
 * @return the Clan if is not exsist NUll
 */
ArrayHeap* DynamicHash::ClanLost(int clan_id){
    Clan* actuall_clan = ReturnClan(clan_id);

    if (actuall_clan==NULL){
    } else {
        return actuall_clan->SetValidityToFalse();
    }
    return NULL;
}

/**
 * get clan Number of clan
 * @return
 */
int DynamicHash::GetNumClans(){
    return number_elements;
}
/*----------------------------------------------------------------------------*/
/**
 * Enlarge the clan for size*2  if the number of clan is in the size of the array
 * multiply the size of the array
 */
void DynamicHash::enlargeArray(){
    int new_size=table_size*2;
    List** new_array=NULL;
    try {
        new_array=new List*[new_size];
        for (int i=0;i<new_size;i++){
            new_array[i]=NULL;
        }
    } catch (std::bad_alloc &){
        return;
    }
    for(int i=0;i<table_size;i++){
        new_array[i]=array[i];
        array[i]=NULL;
    }
    delete[] array;
    array=new_array;


}


