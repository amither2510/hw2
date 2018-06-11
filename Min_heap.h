#ifndef Heap_tt
#define Heap_tt

#include <clocale>

class ArrayHeap{
public:
    int clan_id;
    int index;
    ArrayHeap();
    ~ArrayHeap();
    explicit ArrayHeap(int id);
    void SetClanIdToNil();
};

class Heap{
public:
    ArrayHeap** arr;
    int size;
    int valid_size;
    Heap();
    int GetMinClanId();
    // Create heap
    explicit Heap(int size);

    ~Heap();

    void Delete_min();

    void sift_up_array(int key);

    void DestroyHeap();

        ArrayHeap* CreateTempHeapClan(int clan_id);
    void AddClan(ArrayHeap* temp_heap_clan);

    //delete node
    void deleteHeap(ArrayHeap* node);

    void swap(int index1,int index2) ;

    // helper function to fix the tree
    void sift_down_array(int key);
    void PrintHeap();
    void increment_array();

};



#endif //Heap
