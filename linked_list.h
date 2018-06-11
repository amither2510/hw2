
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
    ListNode(int clan_id,ArrayHeap* heap_clan);
    ~ListNode();
    int GetClanId();
    ListNode* GetNextNode();
    void SetNextNode(ListNode* node);
    Clan* GetClan();
};

//One way linked list:
class List {
private:
    ListNode* head;
public:
    List();
    ~List();
    LIST_RESULT ListInsertClan(int clan_id,ArrayHeap* heap_clan);
    LIST_RESULT ListInsertPlayer(int clan_id,int player_id,int score);
    bool DoesContain(int clan_id);
    ListNode* GetNextNode(ListNode* node);
    ListNode* GetHead();
    ListNode* ReturnClanNode(int clan_id);
};




#endif /* LINKED_LIST_H_ */
