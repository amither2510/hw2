#include "Min_heap.h"
#include <iostream>
using namespace std;


/**
 * constructor of the Arrayheap
 */
ArrayHeap:: ArrayHeap():clan_id(0),index(0){}

/**
 * constructor of the Arrayheap
 */
ArrayHeap::ArrayHeap(int id): clan_id(id),index(0){}

/**
 * destructor of the Arrayheap
 */
ArrayHeap::~ArrayHeap(){}

/**
 * Destroy the heap
 */
void Heap::DestroyHeap(){

    if(arr) {
        for (int i = 1; i < valid_size+1; i++) {
            delete arr[i];
        }
        delete [] arr;
    }
}

/**
 * destructor the heap
 */
Heap::~Heap(){
    DestroyHeap();
}

/**
 *  Create heap node
 * @param clan_id  the number of id of the clan to insert
 * @return the node to insert
 */
ArrayHeap* Heap::CreateTempHeapClan(int clan_id) {
    return (new ArrayHeap(clan_id));
}
/**
 *   Add Clan to the heap
 * @param temp_heap_clan  - the node that is inside of the info of the clan
 * fix the tree and add clan
 */
void Heap::AddClan(ArrayHeap* temp_heap_clan) {
    if(valid_size==size){
        increment_array();
    }
    arr[valid_size+1]=temp_heap_clan;
    temp_heap_clan->index=valid_size+1;
    valid_size++;
    for(int temp=valid_size;temp>0;temp--){
        sift_down_array(temp);
    }
}

/**
 *  delete node from heap from a given pointer
 * @param node - the node that need to delete
 * 1) decress clan id to -1
 * 2) then sift up to the root
 * 3) delete min
 */
void Heap::deleteHeap(ArrayHeap* node){
    if(!node) return;
    node->clan_id=-1;
    for(int temp=node->index;temp>0;temp--){
            sift_down_array(temp);
    }
    Delete_min();

}
/**
 * constructor of heap
 */
Heap::Heap() :arr(NULL),size(0),valid_size(0){}

/**
 *  return the min in the heap-
 * @return  the min in the heap
 */
int Heap::GetMinClanId(){
    if(!arr) return -1;
    return arr[1]->clan_id;
}

/**
 *  swap to element in the array
 * @param index1 the index of the elemenet1 in the array
 * @param index2 the index of the elemenet2 in the array
 * swap also the index
 */
void Heap::swap(int index1,int index2) {
    ArrayHeap *elem1 = arr[index1];
    ArrayHeap *elem2 = arr[index2];

    elem1->index = index2;
    elem2->index = index1;

    arr[index1] = elem2;
    arr[index2] = elem1;
}

/**
 *  constructor that get size amd init array in the size
 * @param size
 */
Heap::Heap(int size):size(size){
    arr=new ArrayHeap*[size+1];
    valid_size=0;
    for (int i=0;i<size+1;i++){
        arr[i]=NULL;
    }
}

/**
 *  sift down fix the tree that will be valid in the tree
 * @param key the strating index that need to fix
 */
void Heap::sift_down_array(int key) {

    int left_son = 2 * key;
    int right_son = 2 * key + 1;
    int smallest = key;
    if ((left_son <= valid_size )) {
        if (left_son < this->size && arr[left_son]->clan_id < arr[key]->clan_id) {
            smallest = left_son;
        }
    }  if ((right_son <= valid_size)) {
        if (right_son < this->size && arr[right_son]->clan_id < arr[smallest]->clan_id){
            smallest = right_son;}
    }

        if (smallest != key) {
            swap(key, smallest);
            sift_down_array(smallest);
        }

}

/**
 *  sift up fix the tree that will be valid in the tree
 * @param key the strating index that need to fix
 */
void Heap::sift_up_array(int key) {

    int left_son = 2 * key;
    int right_son = 2 * key + 1;
    int smallest = key;

    if (right_son >= valid_size) {

        if (left_son >= valid_size)

            return;

        else

            smallest = left_son;

    } else {

        if (arr[left_son]->clan_id <= arr[right_son]->clan_id)

            smallest = left_son;

        else

            smallest = right_son;

    }

    if (arr[key]->clan_id > arr[smallest]->clan_id) {
        swap(key, smallest);
        sift_up_array(smallest);

    }

}


/**
 * Delete the Min
 *  helper function for delete node
 */
void Heap::Delete_min(){
    if(valid_size == 0) return;
    delete(arr[1]);
    arr[1] = arr[valid_size];
    valid_size--;
    if (valid_size > 0)
        for(int temp=1;temp<valid_size;temp++){
            sift_down_array(temp);
        }
}

/**
 * Print the heap
 */
void Heap::PrintHeap() {
    cout << "--------------------------" << endl;
    cout << "size = " << size << endl;
    cout << "valid size= = " << valid_size << endl;
    cout << "--------------------------" << endl;
    for (int i=1;i<valid_size+1;i++){
        cout << "clan["<<i<<"] ="<<arr[i]->clan_id<<endl;
    }
}

/**
 * increment the array for dynmic array
 */
void Heap::increment_array(){
    ArrayHeap** temp = NULL;
    int size=this->size;
    temp=new ArrayHeap*[2*size+1];
    for(int i=1;i<size+1;i++){
        temp[i]=arr[i];
        arr[i]=NULL;
    }
    temp[0]=NULL;
    arr[0]=NULL;

    delete [] arr;
    arr=temp;
    this->size=2*this->size;
}

