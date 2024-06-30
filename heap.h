#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/* Min-Max Heap
 Struktura podataka koja na neki nacin predstavlja dvostruki heap, u smislu da je moguce brisanje i najmanjeg i najveceg elementa u vremenu O(log n).
 Osobina ovog heapa je da za svaki element vrijedi da ako je na parnoj dubini onda ja manji od svog roditelja a veci od roditelja svog roditelja,
 dok za elemente na neparnoj dubini vrijedi da su veci od svojih roditelja, a manji od roditelja svojih roditelja.*/

template <typename Tip>
class Heap {
  vector<Tip> elementi;
  int Roditelj(int indeks) { return (indeks-1)/2; }
  int Djed(int indeks) { return (indeks-3)/4; }
  int LijevoDijete(int indeks) { return 2*indeks + 1; }
  int DesnoDijete(int indeks) { return 2*indeks + 2; }
  int Dubina(int indeks) {return int(log2(indeks+1));}//. Dubina elementa je njegova udaljenost od korijena (npr. dubina korijena je 0).
  void PushUp(int indeks);
  void PushUpMax(int indeks);
  void PushUpMin(int indeks);
  void PushDown(int indeks);
  void PushDownMax(int indeks);
  void PushDownMin(int indeks);
  void MakeHeap();
  public:
  Heap() {}
  Heap(const vector<Tip> &niz):elementi(niz) { MakeHeap(); } //Konstruktor koji prima vektor i koristeci privatnu funkciju MakeHeap() pravi heap.
  int findMaxIndex(); //Vraca indeks najveceg elementa
  int findMinIndex(){ return 0; }//Vraca indeks najmanjeg elementa, tj. 0.
  bool Empty() { return elementi.size() == 0; } //Provjerava da li je niz prazan.
  int Size() { return elementi.size(); } //Vraca velicinu niza.
  Tip& findMin() { return elementi[0]; } //Vraca najmanji element. Najmanji element je korijen.
  Tip& findMax(){ return elementi[findMaxIndex()];}//Vraca najveci element.
  void Push(const Tip& element);//Dodaje element.
  void deleteMin();//Brise najmanji element.
  void deleteMax();//Brise najveci element.
  void Ispisi() { for(int i=0;i<elementi.size();i++) cout<<elementi[i]<<" "; cout<<endl; } //Ispisuje niz.
};



#include "heap.cpp"

#endif
