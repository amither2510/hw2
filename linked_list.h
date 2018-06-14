
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "clan.h"

//Results value:
typedef enum list_result{
    LIST_ALLOCATION_ERROR,
    LIST_CLAN_ADDED,
    LIST_CLAN_DOES_NOT_EXISTS,
    LIST_PLAYER_ALREADY_EXISTS,
    LIST_PLAYER_ADDED,
    LIST_CLAN_ALREADY_EXISTS,
}LIST_RESULT;


class ListNode {
private:
    Clan* clan;
    ListNode* next;
public:
    // Constructor
    ListNode(int clan_id,ArrayHeap* heap_clan);

    // Constructor
    ListNode(Clan* clan);

    //Destructor
    ~ListNode();

    //GetClanid
    int GetClanId();

    //getNextNode of the current list
    ListNode* GetNextNode();

    //Setnext node
    void SetNextNode(ListNode* node);

    // get Clan id
    Clan* GetClan();
};

//One way linked list:
class List {
private:
    ListNode* head;
public:

    //Constructor
    List();

    //Destructor
    ~List();

    //Constructor
    List(const List& lst);

    //setNull
    void setNull();

    //List insert for copy clan to hash
    LIST_RESULT ListInsertClan1(int clan_id,ArrayHeap* heap_clan,Clan* clan);

    //insert for new clan
    LIST_RESULT ListInsertClan(int clan_id,ArrayHeap* heap_clan);

    //insert player to list
    LIST_RESULT ListInsertPlayer(int clan_id,int player_id,int score);

    // check if is contain
    bool DoesContain(int clan_id);

    // get next node
    ListNode* GetNextNode(ListNode* node);

    //get head
    ListNode* GetHead();

    //return node
    ListNode* ReturnClanNode(int clan_id);
};




#endif /* LINKED_LIST_H_ */
