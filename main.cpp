#include <iostream>

void tableFill(int table[],int size){   //fills the table with orandom numbers from min to max. wanted to test it with random numb but then realized it would not yield consistent testing env
    int max=25;
    int min=1;
    for(int i = 0;i<size;++i){
        table[i]=rand()%(max-min+1)+min;
    }
}

void tableFill(int table[],int size, bool type){    //fills the table with NULLs
    for(int i = 0;i<size;++i){
        table[i]=NULL;
    }
}


void tablePrint(int table[],int size){  //prints the content to the stdo
    for(int i = 0;i<size;++i){
        std::cout<<table[i]<<", ";
    }
    std::cout<<"\n";
}

int heapAddLeaf(int heap[], int size, int leaf){    //adds a new leaf to the heap
    for(int i =1; i<size; ++i){
        if(heap[i]==NULL){
            heap[i]=leaf;
            return 0;
        }
    }
    return -1;
}

int heapRestore(int heap[],int size, int index){    //restores the heap after adding a new leaf. To make it faster it omits non impacted branch. returns 0 if restoration was successful
    while(index!=1){
        if(heap[index]>heap[index/2]) {
            int swap = heap[index/2];
            heap[index/2]=heap[index];
            heap[index]=swap;
        }else return 0;
        index=index/2;
    }
    return 0;
}

int heapFullRestore(int heap[], int size, int index=1){     //Fully restores the heap. If the branch looks good from the root it is omitted. returns 0 if restoration was successful
    if(heap[index]<heap[2*index+1]&&2*index+1<=size){
        int swap=heap[index];
        heap[index]=heap[2*index+1];
        heap[2*index+1]=swap;
        heapFullRestore(heap, size, 2*index+1);
    }
    if(heap[index]<heap[2*index]&&2*index<=size){
        int swap=heap[index];
        heap[index]=heap[2*index];
        heap[2*index]=swap;
        heapFullRestore(heap, size, 2*index);
    }
    return 0;
}

int main() {
    int dane_size = 8; //should be 20 but i was working with a smaller sample to speed the dev time up. It should work with a bigger sample
    int heap_size = dane_size;
    int dane[8]={NULL,7,5,9,6,7,8,10}; //feeding in the data to eliminate the differences in typing it in time. I should take care of that null in front to make it more compatible with external codes
    //tablePrint(dane, dane_size); //prints the content of the table to see how it looks before turning it into a heap

    //Budowa kopca
    int heap[20];
    tableFill(heap,heap_size, false);   //fills table with NULLS
    heap[1]=dane[1];
    for(int i = 2; i <dane_size; ++i){
        heapAddLeaf(heap,heap_size, dane[i]);
        heapRestore(heap, heap_size, i);
    }
    tablePrint(heap, heap_size);

    //Zdejmowanie liczb w odpowiej kolejnosci
    for(int i = 0; i<dane_size; ++i){
        dane[i]=heap[1];
        heap[1]=heap[heap_size-i-1];
        heap[heap_size-i-1]=NULL;
        heapFullRestore(heap,heap_size);
    }
    //tablePrint(heap, heap_size);// making sure that my heap is empty
    tablePrint(dane, dane_size);

    return 0;
}
