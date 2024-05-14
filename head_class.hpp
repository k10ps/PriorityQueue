#pragma once


template <typename E, typename P>
class SLinkedList;

template <typename E, typename P>
class MaxPriorityList;

//tworzymy wezel zawierajacy informacje o priorytet, wartosci i wskaznik na nasteony element
template <typename E, typename P>
class SingleNode 
{
    public:
    E value;                    //wartsoc elementu
    P priority;                 //priorytet
    SingleNode<E, P>* next;     //wskaznik na nastepny wezel/element
    friend class SLinkedList<E, P>;
};

//glowna klasa
template <typename E, typename P>
class SLinkedList 
{
    private:
    int size;
    SingleNode<E, P>* head; //wskaznik na 1 element

    public:
    SLinkedList();          //konstruktor
    ~SLinkedList();         //destruktor
    bool empty() const;             //true jezeli pusta
    int ile() const;                //zwraca ilosc elementow
    const E& front() const;         //zwraca wartosc elementu o najwiekszym priorytecie
    void whatSize()const;                //wypisuje size i capacity
    void addFront(const E& val, const P& key);                      //dodaj na poczatek
    void addEnd(const E& val, const P& key);                         //dodaj na koniec
    void addMid(const E& val, int where, const P& key);             //dodaj do srodka
    void removeFront();             //usun z poczatku
    void removeEnd();               //usun z konca
    void removeMid(int where);      //usun z wybranego miejsca
    void wypisz() const;            //wypisz wszystkie elementy
    void lookV(int co) const;              //wyszukiwanie po wartosci

    //nowe
    SingleNode<E, P>* getHead() const { return head; }          //zwraca wskaznik na head
    void setHead(SingleNode<E, P>* newHead) {head = newHead;}
    
};



template <typename E, typename P>
SLinkedList<E, P>::SLinkedList(): head(NULL), size(0) { } //konstruktor

template <typename E, typename P>
SLinkedList<E, P>::~SLinkedList() { while (!empty()) removeFront(); delete head;} // destructor usuwa pierwszy element dopoki lista nie jest pusta

template <typename E, typename P>
bool SLinkedList<E, P>::empty() const {return head == NULL;} //lista pusta zwraca 1

template <typename E, typename P>
const E& SLinkedList<E, P>::front() const { return (head -> value); } //wskazujemy na pierwszy element i zwracamy jego wartosc

template <typename E, typename P>
int SLinkedList<E, P>::ile() const {return size;}

template <typename E, typename P>
void SLinkedList<E, P>::wypisz() const{
    SingleNode<E, P>* current = head;
    while(current!=NULL){std::cout << current->value <<std::endl; current = current->next;} //dopoki nie natrafimy na ostatni element wypisuj
}

template <typename E, typename P>
void SLinkedList<E, P>::whatSize()const{ std::cout<<"Ilosc elementow: "<<size<<std::endl;}
    
template <typename E, typename P>
void SLinkedList<E, P>::addFront(const E& val, const P& key) 
{ 
    SingleNode<E, P>* point = new SingleNode<E, P>;
    point->value = val;
    point->priority=key;
    point->next = head;
    head = point;
    size++;
}

template <typename E, typename P>
void SLinkedList<E, P>::removeFront() 
{
    if(empty()){return;}
    SingleNode<E, P>* temp = head;     //tymczasowy wskaznik wskazujacy na 1 element listy
    head = head->next;              //do head przypisujemy wskaznik na kolejny element z listy
    delete temp;                     //usuwamy poprzedni head czyli pierwszy element
    size--;
}

template <typename E, typename P>
void SLinkedList<E, P>::addEnd(const E& val, const P& key)
{   
    SingleNode<E, P>* nowy = new SingleNode<E, P>; //tworzymy nowy wskaznik
    nowy->value = val;
    nowy->priority= key;
    nowy->next = NULL;
    if(empty()){head=nowy;}
    else{
    //temp1 biegnie przed temp2, jezeli temp1 napotka ostatni element temp2 bedzie na przedostatnim i go zwroci
    SingleNode<E, P>* temp1 = head;
    SingleNode<E, P>* temp2 = head;
    while(1)
    {
        temp1=temp1->next;
        if(temp1==NULL){break;}
        temp2=temp2->next;
    }
    temp2->next=nowy;
    size++;
    }
}

template <typename E, typename P>
void SLinkedList<E, P>::addMid(const E& val, int where, const P& key){
    SingleNode<E, P>* nowy = new SingleNode<E, P>;
    nowy->priority=key;
    nowy->value = val;
    if(empty()){head=nowy;}
    else if(where<0 || where>=ile()){std::cout<<"Lokalizacja poza zakresem"<<std::endl; return;}
    else if(where==0){addFront(val, key); return;}
    else
    {
    SingleNode<E, P>* temp1 = head;    //element przed wybranym miejscem
    SingleNode<E, P>* temp2 = head;    //element po wybranym miejscu  
    for(int i=0; i<where-1; i++)
    {
        temp1=temp1->next;
        if(temp1==NULL)
        {
            addEnd(val, key);
            return;
        }
    }
    if(temp1->next==NULL){addEnd(val, key);return;}

    temp2=temp1->next;
    temp1->next=nowy;
    nowy->next=temp2;
    size++;
    }
}

template <typename E, typename P>
void SLinkedList<E, P>::removeEnd(){
    if(empty()){std::cout<<"Brak elementow"<<std::endl;}
    else{
    SingleNode<E, P>* temp1 = head;
    SingleNode<E, P>* temp2 = head;
    while(1)
    {
        temp1=temp1->next;
        if(temp1->next==NULL){break;}
        temp2=temp2->next;
    }
    //std::cout<<"Usunieto wartosc: "<<temp1->value<<std::endl;
    temp2->next=NULL;
    delete temp1;
    size--;
    }
}

template <typename E, typename P>
void SLinkedList<E, P>::removeMid(int where){
    if(empty()){std::cout<<"Brak elementow"<<std::endl; return;}
    else if(where<0 || where>ile()){std::cout<<"Lokalizacja poza zakresem"<<std::endl; return;}
    else if(where==0){removeFront(); return;}
    else if(where == ile() - 1) {removeEnd();return;}
    else
    {
    SingleNode<E, P>* temp1 = head;    //element przed wybranym miejscu  
    SingleNode<E, P>* temp2 = head;    //element usuwany wybranym miejscu
    SingleNode<E, P>* temp3 = head;    //element po wybranym miejscu  
    for(int i=0; i<where-1; i++)
    {
        temp1=temp1->next;
        if(temp1==NULL)
        {
            removeEnd();
            return;
        }
    }
    temp2=temp1->next;
    temp3=temp2->next;
    temp1->next=temp3;
    std::cout<<"Usunieto wartosc: "<<temp2->value<<std::endl;
    delete temp2;
    size--;
    }

}


template <typename E, typename P>
void SLinkedList<E, P>::lookV(int co) const{
    SingleNode<E, P>* temp1 = head; 
    int where=0;
    while(temp1!=NULL)
    {
        where++;
        if(temp1->value==co){
            std::cout<<"Znaleziono: "<<temp1->value<<", na pozycji: "<<where-1<<std::endl;  //where-1 bo zakladamy indexowanie od 0
            return;
        }
        temp1=temp1->next;
    }
    std::cout << "Nie mozna znalezc wartosci: " << co << std::endl;
}






