#include <iostream>
#include <vector>
#include "heap.h"
using namespace std;

int main(){
/*
Heap<int> h;
h.Push(71);
h.Push(41);
h.Push(31);
h.Push(10);
h.Push(11);
h.Push(16);
h.Push(46);
h.Push(51);
h.Push(21);
h.Push(13);
h.Push(8);
*/


vector<int> v{8,71,31,10,11,16,41,46,51,31,21,13};
Heap<int> h1(v);
h1.Ispisi();

cout<<"Najveci element je "<<h1.findMax()<<endl;
cout<<"Najmanji element je "<<h1.findMin()<<endl;

cout<<"Izbrisi najveci i najmanji: "<<endl;
h1.deleteMax();
h1.deleteMin();
h1.Ispisi();
cout<<"Najveci element je "<<h1.findMax()<<endl;
cout<<"Najmanji element je "<<h1.findMin()<<endl;

}
