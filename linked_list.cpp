#include "linked_list.h"




/**
 *  Consructor
 * @param clan_id
 * @param heap_clan
 */
ListNode::ListNode(int clan_id,ArrayHeap* heap_clan):clan(new Clan(clan_id,heap_clan)),next(NULL){}
ListNode::ListNode(Clan* clan):clan(clan),next(NULL){}

/**
 * Destructor of NodeList
 */
ListNode::~ListNode(){
    delete clan;
}

/**
 * Getter clan -id
 * @return return clan id
 */
int ListNode::GetClanId(){
    return clan->GetClanId();
}

/**
 *  getNextNode
 * @return  return the next node
 */
ListNode* ListNode::GetNextNode(){
    return next;
}

/**
 * constructor
 */
List::List():head(NULL){}

/**
 * Destructor
 */
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

/**
 * Copy Constructor
 * @param lst
 */
List::List(const List& lst){
    this->head=lst.head;
}

/**
 * SetNextNode to the parm
 * @param node - set the next
 */
void ListNode::SetNextNode(ListNode* node){
    next=node;
}

/**
 * SetNull All Field
 */
void List::setNull(){
    Clan* clan=this->head->GetClan();
    clan->setNull();
    this->head=NULL;
}

/**
 * List insert new clan
 * @param clan_id - id  of the clan to add
 * @param heap_clan - pointer to the clan
 * @return LIST_ALLOCATION_ERROR- bad alloc
 * @return  LIST_CLAN_ADDED - success
 */
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
/**
 * Insert a exist clan and copy it to new array
 * @param clan_id  - the id of the copy clan
 * @param heap_clan - the pointer to the array
 * @param clan the pointer of the old clan
 * @return LIST_ALLOCATION_ERROR -bad alloc
 * @return LIST_CLAN_ALREADY_EXISTS -alreadyy exist in sys
 * @return LIST_CLAN_ADDED -success
 *
 */
LIST_RESULT List::ListInsertClan1(int clan_id,ArrayHeap* heap_clan,Clan* clan) {
    if (!head) {
        try {
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
            head=new ListNode(clan);
            head->SetNextNode(temp_node);
        } catch (std::bad_alloc &) {
            return LIST_ALLOCATION_ERROR;
        }
    }
    return LIST_CLAN_ADDED;
}

/**
 * Check if is contain in the sys
 * @param clan_id  -the id to check
 * @return true - if is in the sys
 * @return false - is not sys
 */
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

/**
 * returnClan node
 * @param clan_id
 * @return the node of the clan in the list
 */
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

/**
 * getNextNode
 * @param node
 * @return The node if is exsist else Null
 */
ListNode* List::GetNextNode(ListNode* node){
    if (node){
        return node->GetNextNode();
    } else {
        return NULL;
    }
}

/**
 * get head of the list
 * @return  the head of list
 */
ListNode* List::GetHead(){
    return head;
}

/**
 * getter of clan
 * @return get the clan of the current node
 */
Clan* ListNode::GetClan(){
    return clan;
}

/**
 * Insert player to the Tree in the clan
 * @param clan_id
 * @param player_id
 * @param score
 * @return LIST_ALLOCATION_ERROR
 * @return LIST_PLAYER_ALREADY_EXISTS
 * @return LIST_CLAN_DOES_NOT_EXISTS
 */
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




