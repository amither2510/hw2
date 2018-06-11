#ifndef Heap_tt
#define Heap_tt

#include <clocale>

class ArrayHeap{
public:
    int clan_id;
    int index;

    // constructor + destructor
    ArrayHeap();
    ~ArrayHeap();
    explicit ArrayHeap(int id);
};

class Heap{
public:
    ArrayHeap** arr;
    int size;
    int valid_size;



    // Create heap
    explicit Heap(int size);

    ~Heap();

    Heap();

    // create HeapNode
    ArrayHeap* CreateTempHeapClan(int clan_id);

    // return the min in the heap
    int GetMinClanId();

    // Delete a node from the heap
    void Delete_min();

    // Destroy the heap
    void DestroyHeap();

    // inesrt clan to heap
    void AddClan(ArrayHeap* temp_heap_clan);

    //delete clan from heap
    void deleteHeap(ArrayHeap* node);

    //swap to index
    void swap(int index1,int index2) ;

    //fix the tree that the heap will maintain complete
    void sift_down_array(int key);

    //fix the tree that the heap will maintain complete
    void sift_up_array(int key);

    // print the heapp
    void PrintHeap();

    //enlarge the size of the heap
    void increment_array();

};



#endif //Heap
