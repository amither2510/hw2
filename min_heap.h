
#include <clocale>


class ArrayIndex{
public:
    int id;
    int index;






    ArrayIndex() : id(0),index(-1){}
    ArrayIndex(int id,int index): id(id),index(index){}
    int& operator[] (int x) { return this->id;}
    void set_index(int ind){ this->index=ind;}

    };

int cmp(const ArrayIndex& lhs, const ArrayIndex& rhs){return lhs.id-rhs.id;}
bool operator< (const ArrayIndex& lhs, const ArrayIndex& rhs){ return cmp(lhs,rhs) <  0; }
bool operator> (const ArrayIndex& lhs, const ArrayIndex& rhs){ return cmp(lhs,rhs) >  0; }

// Data structure for Min Heap
class MinHeap
{

private:

    ArrayIndex* arr;
    int size;
    int size_of_array;
    int last_elem;


    void increment_array(int size){
        ArrayIndex* temp = new ArrayIndex[size];
        for(int i=0;i<size/2;i++){
            temp[i].id=arr[i].id;
            temp[i].index=i;

        }
        last_elem=size/2;
        size_of_array=size;
        delete [] arr;
        arr=temp;
    }

    int father(int i) { return (i - 1) / 2; }

    int left(int i) { return (2 * i + 1); }

    int right(int i) { return (2 * i + 2); }

    void swap(ArrayIndex & arg1 ,ArrayIndex& arg2){
        ArrayIndex temp_id=arg1;
        arg1.id=arg2.id;
        arg2.id=temp_id.id;
    }

    void int_swap(int & elem1,int& elem2){
        int  temp = elem1;
        elem1=elem2;
        elem2=temp;
    }

    void sift_down(int i,int* arr)
    {
        int left_son = left(i);
        int right_son = right(i);
        int smallest = i;

        if (left_son < this->size && arr[left_son] < arr[i])
            smallest = left_son;

        if (right_son < this->size && arr[right_son] < arr[smallest])
            smallest = right_son;

        if (smallest != i) {
            int_swap(arr[i], arr[smallest]);
            sift_down(smallest,arr);
        }
    }

    void heapify_up(int index)
    {

        if (index && arr[father(index)] > arr[index])
        {
            swap(arr[index], arr[father(index)]);
            heapify_up(father(index));
        }
    }

public:
    MinHeap() : arr(NULL),size(0),size_of_array(0),last_elem(0){}
    MinHeap(int size){
        this->size=0;
        arr = new ArrayIndex[size];
        size_of_array=size;
        last_elem=0;
    }

    ~MinHeap(){ delete [] arr; }

    bool empty() { return size == 0; }

    void push(int key)
    {
        if(size == size_of_array){
            increment_array(2*size_of_array);
        }
        arr[last_elem].id=key;
        arr[last_elem].index=last_elem-1;
        last_elem++;
        size++;
        int index = size - 1;
        heapify_up(index);
    }

    void delete_val( ArrayIndex* element) {
        if(!element) return;
        if(element->id == arr[last_elem].id){
            last_elem--;
            return;
        }
        element->id=arr[last_elem].id;
    }


    int top()
    {
        if(empty()) return -1;
        return arr[0].id;
    }
    void print(){
        std::cout<<"The Lowest Number is -----"<<" "<<this->arr[0].id<<" , and the Index is "<<this->arr[0].index<<std::endl;
    }

};
