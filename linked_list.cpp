#include "linked_list.h"


/*-------------------------------Node-----------------------------------------*/
ListNode::ListNode(int clan_id,ArrayHeap* heap_clan):clan(new Clan(clan_id,heap_clan)),next(NULL){}
ListNode::ListNode(Clan* clan):clan(clan),next(NULL){}

/*----------------------------------------------------------------------------*/
ListNode::~ListNode(){
    delete clan;
}
/*----------------------------------------------------------------------------*/
int ListNode::GetClanId(){
    return clan->GetClanId();
}
/*----------------------------------------------------------------------------*/
ListNode* ListNode::GetNextNode(){
    return next;
}
/*---------------------------List---------------------------------------------*/
List::List():head(NULL){}
/*----------------------------------------------------------------------------*/
List::~List(){
    if (head){
        ListNode* current_node=head;
        ListNode* temp_node=NULL;
        while (current_node){
            temp_node=current_node;
            current_node=current_node->GetNextNode();
            delete temp_node;
        }
    }
}
List::List(const List& lst){
    this->head=lst.head;
}

/*----------------------------------------------------------------------------*/
void ListNode::SetNextNode(ListNode* node){
    next=node;
}
/*----------------------------------------------------------------------------*/
void List::setNull(){
    Clan* clan=this->head->GetClan();
    clan->setNull();
    this->head=NULL;
}


LIST_RESULT List::ListInsertClan(int clan_id,ArrayHeap* heap_clan) {
    if (!head) {
        try {
            head=new ListNode(clan_id,heap_clan);
            head->SetNextNode(NULL);
        } catch (std::bad_alloc &) {
            return LIST_ALLOCATION_ERROR;
        }
    } else {
        try {
            if (DoesContain(clan_id)){
                return LIST_CLAN_ALREADY_EXISTS;
            }
            ListNode* temp_node = head;
            head=new ListNode(clan_id,heap_clan);
            head->SetNextNode(temp_node);
        } catch (std::bad_alloc &) {
            return LIST_ALLOCATION_ERROR;
        }
    }
    return LIST_CLAN_ADDED;
}

LIST_RESULT List::ListInsertClan1(int clan_id,ArrayHeap* heap_clan,Clan* clan) {
    if (!head) {
        try {
            // head=new ListNode(clan_id,heap_clan);
            head=new ListNode(clan);
            head->SetNextNode(NULL);
        } catch (std::bad_alloc &) {
            return LIST_ALLOCATION_ERROR;
        }
    } else {
        try {
            if (DoesContain(clan_id)){
                return LIST_CLAN_ALREADY_EXISTS;
            }
            ListNode* temp_node = head;
            // head=new ListNode(clan_id,heap_clan);
            head=new ListNode(clan);
            head->SetNextNode(temp_node);
        } catch (std::bad_alloc &) {
            return LIST_ALLOCATION_ERROR;
        }
    }
    return LIST_CLAN_ADDED;
}
/*----------------------------------------------------------------------------*/
bool List::DoesContain(int clan_id) {
    if (!head) {
        return false;
    }
    ListNode* current_node = head;
    while (current_node) {
        if (current_node->GetClanId() == clan_id) {
            return true;
        }
        current_node = current_node->GetNextNode();
    }

    return false;
}
/*----------------------------------------------------------------------------*/
ListNode* List::ReturnClanNode(int clan_id) {
    if (!head) {
        return NULL;
    }
    ListNode* current_node = head;
    while (current_node) {
        if (current_node->GetClanId() == clan_id) {
            return current_node;
        }
        current_node = current_node->GetNextNode();
    }

    return NULL;
}
/*----------------------------------------------------------------------------*/
ListNode* List::GetNextNode(ListNode* node){
    if (node){
        return node->GetNextNode();
    } else {
        return NULL;
    }
}
/*----------------------------------------------------------------------------*/
ListNode* List::GetHead(){
    return head;
}
/*----------------------------------------------------------------------------*/
Clan* ListNode::GetClan(){
    return clan;
}
/*----------------------------------------------------------------------------*/
LIST_RESULT List::ListInsertPlayer(int clan_id, int player_id, int score) {
    if (!DoesContain(clan_id)) {
        return LIST_CLAN_DOES_NOT_EXISTS;
    }

    try {
        ListNode* clan_node = ReturnClanNode(clan_id);
        if (!clan_node->GetClan()->AddPlayer(player_id, score)) {
            return LIST_PLAYER_ALREADY_EXISTS;
        }
    } catch (std::bad_alloc &) {
        return LIST_ALLOCATION_ERROR;
    }

    return LIST_PLAYER_ADDED;
}
/*----------------------------------------------------------------------------*/




