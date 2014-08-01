#include "iostream"
#include "math.h"


class ArrayHeap
{
    private:
    
        int left(int i) 
        {
            return (2*i + 1);
        }

        int right(int i)
        {
            return (2*i + 2);
        }

        int parent(int i)
        {
            return (int)floor((float)(i-1)/2.0);
        }

    public:

        template <class X> void swap(X&, X&);
        template <class X> void maxHeapify(X* arr, int index, int size);
        template <class X> void minHeapify(X* arr, int index, int size);
        template <class X> void buildHeap(X* arr, int size, bool maxHeap=true);
};


class HeapSort
{
    public:
        template <class X> void sort(X *arr, int size, bool ascending=true);
};

template <class X> void 
HeapSort::sort(X *arr, int size, bool ascending)
{
    ArrayHeap heap;
    if(ascending)
        heap.buildHeap(arr,size);
    else
        heap.buildHeap(arr,size,false);

    int temp = size;
    for(int i= size-1; i>=1; i--)
    {
        if(ascending)
        {
            heap.swap(arr[0], arr[i]);
            temp = temp-1;
            heap.maxHeapify(arr, 0, temp);
        }
        else
        {
            heap.swap(arr[0], arr[i]);
            temp = temp-1;
            heap.minHeapify(arr, 0, temp);
        }
    }
}

template <class X> 
void ArrayHeap::buildHeap(X *arr, int size, bool maxHeap)
{
    for(int i= size/2; i>=0; i--)
    {
        if(maxHeap)
            maxHeapify(arr, i, size);
        else
            minHeapify(arr, i, size);
    }
}

template <class X> 
void ArrayHeap::maxHeapify(X* arr, int index, int size)
{
    int l = left(index);
    int r = right(index);
    int largest =index;
    
    if (l<size && arr[l] > arr[index]) //checking if left children is larger in value
        largest = l;
    
    if (r<size && arr[r] > arr[largest]) //checking if right children is larger
        largest = r;

    if (largest != index)
    {
        swap(arr[index],arr[largest]);
        maxHeapify(arr,largest,size); //recursively see if this node is at its right position
    }
}

template <class X> 
void ArrayHeap::minHeapify(X* arr, int index, int size)
{
    int l = left(index);
    int r = right(index);
    int smallest = index;

    if (l < size && arr[l] < arr[index]) //checking if left child is smaller in value
        smallest = l;

    if(r < size && arr[r] < arr[smallest]) //checking if right child is smaller in value
        smallest = r;

    if(smallest != index)
    {
        swap(arr[smallest], arr[index]);
        minHeapify(arr, smallest, size);
    }
}

template <class X> 
void ArrayHeap::swap(X &x, X &y)
{
    X temp;
    temp=x;
    x=y;
    y=temp;
}

int main()
{
    int testArr1[10]={14,87,64,5,4,675,3,98,68,5603};
    double testArr2[10]={3.45,64.5,6.74,5.67,.34,.56,.7,.34,56.79,3.4};
    char testArr3[10]={'f','g','d','j','s','y','r','e','i','o'};
    int testArr4[15]={3,74,85,320,-14,45,80,43,27,45,923,48,595,-445,57};

    //ArrayHeap heap;
    //heap.buildHeap(testArr1,10,false);
    //heap.buildHeap(testArr2,10,false);
    //heap.buildHeap(testArr3,10,false);
    //heap.buildHeap(testArr4,15,false);

    HeapSort hSort;

    hSort.sort(testArr1, 10, false);
    hSort.sort(testArr2, 10, false);
    hSort.sort(testArr3, 10, false);
    hSort.sort(testArr4, 15, false);

    int i =0;
    while(i<15)
    {
        if(i<10)
        {
            std::cout<<testArr1[i]<<" \t";
            std::cout<<testArr2[i]<<" \t";
        }
        std::cout<<testArr4[i]<<" \t";
        if (i<10)
            std::cout<<testArr3[i]<<" \t";

        std::cout << std::endl;
        i++;
    }

    return 0;
}