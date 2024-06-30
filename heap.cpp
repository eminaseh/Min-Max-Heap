#ifndef HEAP_CPP
#define HEAP_CPP

#include "heap.h"

/*Najveci element je maksimum od desnog i lijevog djeteta korijena. Ukoliko postoji samo jedan elemet u nizu onda vraca indeks tog elementa.
  Ukoliko postoje dva elementa u nizu vraca indeks drugog elementa jer je prvi minimum.*/
template <typename Tip>
int Heap<Tip>::findMaxIndex() {
  if(elementi.size()==1) return 0;
  else if(elementi.size()==2) return 1;
  else{
    if(elementi[1] >= elementi[2])
    return 1;
    else return 2;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////
/*Provjerava da li element ima djeda. Ako ima i ako je on manji od djeda vrsimo njihovu zamjenu i pozivamo PushUpMin(Djed(indeks))*/

template <typename Tip>
void Heap<Tip>::PushUpMin(int indeks) {
  if(indeks > 2 && elementi[indeks] < elementi[Djed(indeks)]){
    swap(elementi[indeks],elementi[Djed(indeks)]);
    PushUpMin(Djed(indeks));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////
/*Provjerava da li element ima djeda. Ako ima i ako je on veci od djeda vrsimo njihovu zamjenu i pozivamo PushUpMaxDjed(indeks))*/

template <typename Tip>
void Heap<Tip>::PushUpMax(int indeks) {
  if(indeks > 2 && elementi[indeks] > elementi[Djed(indeks)]){
    swap(elementi[indeks],elementi[Djed(indeks)]);
    PushUpMax(Djed(indeks));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija se koristi pri dodavanju elemenata u heap, a novi element se dodaje na kraj heapa.Funkcija PushUp provjerava da li je novi element korijen heapa.
  Ako nije, provjerava na kojoj dubini se nalazi i poredi ga sa roditeljom. Ako je na parnoj dubini i veci od roditelja, mijenjamo ga sa roditeljom
  i pozivamo PushUpMax(Roditelj(indeks)) a ako je manji od roditelja onda pozivamo PushUpMin(indeks).
  Analogno ako je element na neparnoj dubini.*/

template <typename Tip>
void Heap<Tip>::PushUp(int indeks) {
    if(indeks == 0 )return;
    if(Dubina(indeks)%2==0){
        if(elementi[indeks] > elementi[Roditelj(indeks)]){
            swap(elementi[indeks],elementi[Roditelj(indeks)]);
            PushUpMax(Roditelj(indeks));
        }
        else PushUpMin(indeks);
    }
    else{
        if(elementi[indeks] < elementi[Roditelj(indeks)]){
            swap(elementi[indeks],elementi[Roditelj(indeks)]);
            PushUpMin(Roditelj(indeks));
        }
        else PushUpMax(indeks);
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija element dodaje na kraj heapa i poziva PushUp(indeks zadnjeg elementa).*/

template <typename Tip>
void Heap<Tip>::Push(const Tip& element) {
  elementi.push_back(element);
  PushUp(elementi.size()-1);
}

////////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija se poziva kada je indeks na parnoj dubini. Pronalazi najmanje dijete od djece i unucadi ako ih element sa proslijedjenim indeksom ima.
  Zatim provjerava da li je najmanje dijete elementa dijete ili unuk.
  Ako je unuk, vrsi zamjenu tog elementa i najmanjeg djeteta. Nakon toga provjerava da li je najmanje dijete vece od svog roditelja te ako jeste
  vrsi njihovu zamjenu. Zatim poziva funkciju PushDownMin(najmanje_dijete).
  Ako najmanje dijete nije unuk, provjerava da li je manje od elementa sa proslijedjenim indeksom te ako jeste vrsi zamjenu ova dva elementa.
  */

template <typename Tip>
void Heap<Tip>::PushDownMin(int indeks) {

     if(LijevoDijete(indeks) < elementi.size()){
        int najmanje_dijete = indeks;
        int lijevo_dijete = LijevoDijete(indeks);
        if(elementi[lijevo_dijete] < elementi[najmanje_dijete])
            najmanje_dijete = lijevo_dijete;
        if(DesnoDijete(indeks) < elementi.size()){
            if(elementi[lijevo_dijete +1] < elementi[najmanje_dijete])
                najmanje_dijete = lijevo_dijete +1;
            if(LijevoDijete(lijevo_dijete) < elementi.size()){
                int lijevi_unuk = LijevoDijete(lijevo_dijete);
                for(int i=0; i<4 && (lijevi_unuk + i) < elementi.size(); i++)
                    if(elementi[lijevi_unuk + i] < elementi[najmanje_dijete])
                        najmanje_dijete = lijevi_unuk + i;
            }
        }
    if(najmanje_dijete - lijevo_dijete > 1) {
        if(elementi[najmanje_dijete] < elementi[indeks]){
            swap( elementi[najmanje_dijete], elementi[indeks]);
            if(elementi[najmanje_dijete] > elementi[Roditelj(najmanje_dijete)])
                swap(elementi[najmanje_dijete], elementi[Roditelj(najmanje_dijete)]);
        }
        PushDownMin(najmanje_dijete);
    }
    else if(elementi[najmanje_dijete] < elementi[indeks])
        swap(elementi[najmanje_dijete], elementi[indeks]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija koja se poziva za elemente na neparnoj dubini. Pronalazi najvece dijete od djece i unucadi ako ih element sa proslijedjenim indeksom ima.
  Zatim provjerava da li je najvece dijete elementa dijete ili unuk.
  Ako je unuk, vrsi zamjenu tog elementa i najveceg djeteta. Nakon toga provjerava da li je najvece dijete manje od svog roditelja te ako jeste
  vrsi njihovu zamjenu. Zatim poziva funkciju PushDownMax(najvece_dijete).
  Ako najvece dijete nije unuk, provjerava da je li vece od elementa sa proslijedjenim indeksom te ako jeste vrsi zamjenu ova dva elementa. */

template <typename Tip>
void Heap<Tip>::PushDownMax(int indeks) {

    if(LijevoDijete(indeks) < elementi.size()){
        int najvece_dijete = indeks;
        int lijevo_dijete = LijevoDijete(indeks);
        if(elementi[lijevo_dijete] > elementi[najvece_dijete])
            najvece_dijete = lijevo_dijete;
        if(DesnoDijete(indeks) < elementi.size()){
            if(elementi[lijevo_dijete +1] > elementi[najvece_dijete])
                najvece_dijete = lijevo_dijete +1;
            if(LijevoDijete(lijevo_dijete) < elementi.size()){
                int lijevi_unuk = LijevoDijete(lijevo_dijete);
                for(int i=0; i<4 && (lijevi_unuk + i) < elementi.size(); i++)
                    if(elementi[lijevi_unuk + i] > elementi[najvece_dijete])
                        najvece_dijete = lijevi_unuk + i;
            }
        }
    if(najvece_dijete - lijevo_dijete > 1) {
        if(elementi[najvece_dijete] > elementi[indeks]){
            swap( elementi[najvece_dijete], elementi[indeks]);
            if(elementi[najvece_dijete] < elementi[Roditelj(najvece_dijete)])
                swap(elementi[najvece_dijete], elementi[Roditelj(najvece_dijete)]);
        }
        PushDownMax(najvece_dijete);
    }
    else if(elementi[najvece_dijete] > elementi[indeks])
        swap(elementi[najvece_dijete], elementi[indeks]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija koja se poziva pri konstrukciji heapa. Ako je proslijedjeni indeks na parnoj(neparnoj) dubini poziva PushDownMin(PushDownMax).*/
template <typename Tip>
void Heap<Tip>::PushDown(int indeks) {

    if(Dubina(indeks)%2==0){
        PushDownMin(indeks);
    }else PushDownMax(indeks);
}

////////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija koja pravi heap.*/

template <typename Tip>
void Heap<Tip>::MakeHeap() {
  for(int i = Roditelj(elementi.size()-1);i>=0;i--)
    PushDown(i);
}

////////////////////////////////////////////////////////////////////////////////////////////////
/*Brise najmanji element heapa. Korijen postaje zadnji element niza i poziva se funkcija pop_back, nakon cega se poziva PushDown na indeks korijena
  kako osobina heapa da za svaki element vrijedi ako je na parnoj dubini onda ja manji od svog roditelja a veci od roditelja svog roditelja,
  dok za elemente na neparnoj dubini vrijedi da su veci od svojih roditelja, a manji od roditelja svojih roditelja ne bi bila narušena.*/

template <typename Tip>
void Heap<Tip>::deleteMin() {
  elementi[0] = elementi[elementi.size()-1];
  elementi.pop_back();
  PushDown(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////
/*Pronalazi najveci element i na njegovo mjesto stavlja posljednji element u nizu, a posljednji element brise. Zatim poziva funkciju PushDown(najveci)*/

template <typename Tip>
void Heap<Tip>::deleteMax() {
  int najveci = findMaxIndex();
  elementi[najveci] = elementi[elementi.size()-1];
  elementi.pop_back();
  PushDown(najveci);
}

////////////////////////////////////////////////////////////////////////////////////////////////

#endif
