#pragma once

template <typename E, typename P>
class MaxPriorityList;


template <typename E, typename P>
class Dynamic
{
    public:
    struct Node
    {
        E value;
        P priority;
        Node() : value(), priority() {}
    };
    public:
    int size;       //liczba ele w tab
    int capacity;   //liczba miejsc
    Node *array;     //wskaznik na tablice dynamiczna
    
    public:
    Dynamic();
    ~Dynamic();
    bool notenough()const;     //jezeli nie ma jzu miejsca zwraca 1
    int what_size() const   {return size;}
    void wypisz()const;                  //wypisuje wszystkei wartosci
    bool empty()const;                 //true jesli pusta
    void whatSize()const;                //wypisuje size i capacity
    void addEnd(const Node& node);                   //dodajemy elementy na koniec, od 0 wiec na index=size
    void addFront(const Node& val);                 //dodajemy elementy na początek
    void addMid(const Node& val, int index);        //dodajemy elementy do wybranego punktu
    void relocate(int index);               //przesuwa elementy w prawo
    void resize(int opcja,const Node& val, int index);        //zwiekszamy rozmiar tablicy capacity*2
    void remove(int index);               //usuwa element i przesuwa
    void removeMid(int index);              
    void removeFront();
    void removeEnd();
    void lookP(int index)const;       //na danej pozycji wartosc, od 0!!

    //new
    int ret_value(int i)const{return array[i].value;}
    int ret_priority(int i)const{return array[i].priority;}
    void wymiana(int u, int other)                              
    {
        //std::swap(array[u], array[other]);
        Node temp=array[other];
        array[other]=array[u];
        array[u]=temp;
    }
    void zmiana(int u)                                          {array[0]=array[u];}
    void change_key(int where, const P& key)                    {array[where].priority=key;}

};


//konstruktor tworzy nam pusta tablice
template <typename E, typename P>
Dynamic<E, P>::Dynamic(): capacity(10), size(0), array(new Node[capacity]) { }
//destruktor
template <typename E, typename P>
Dynamic<E, P>::~Dynamic(){delete[] array;}

template <typename E, typename P>
bool Dynamic<E, P>::empty()const{return (size==0);}

template <typename E, typename P>
void Dynamic<E, P>::wypisz()const{ for(int i=0; i<size; i++)   { std::cout<<array[i]<<std::endl;}}

template <typename E, typename P>
void Dynamic<E, P>::lookP(int index)const{std::cout<<"Na: "<<index<<" jest wartosc: "<<array[index]<<std::endl;}

template <typename E, typename P>
void Dynamic<E, P>::whatSize()const{ std::cout<<"Ilosc elementow: "<<size<<std::endl;std::cout<<"Rozmiar: "<<capacity<<std::endl;}

template <typename E, typename P>
bool Dynamic<E, P>::notenough()const{return (size==capacity);}

template <typename E, typename P>
void Dynamic<E, P>::addEnd(const Node& node)
{
    
    if(notenough()){resize(0,node, 0);} 
    else{array[size]=node; size++;}
}

template <typename E, typename P>
void Dynamic<E, P>::addFront(const Node& val){

    if(notenough()){resize(1, val, 0);}
    else{
    if(size!=0){relocate(0);}
    array[0]=val; 
    size++;
    }
}

template <typename E, typename P>
void Dynamic<E, P>::addMid(const Node& val, int index){

    if(index>=size){addEnd(val);}
    else if(index==0){addFront(val);}
    else{
    if(notenough()){resize(2, val, index);}
    relocate(index);
    array[index]=val; 
    size++;
    }
}

template <typename E, typename P>
void Dynamic<E, P>::relocate(int index){
    for(int i=size; i>index; i--)
    {
        array[i]=array[i-1];
    }
}


template <typename E, typename P>
void Dynamic<E, P>::resize(int opcja, const Node& val, int index){
    int grow=capacity*2;
    Node *temp=new Node[grow];      //tymczasowy wskaznik
    for (int i=0; i<capacity; i++)      {temp[i]=array[i];}
    delete [] array;
    capacity=grow;
    array=temp; 
    if(opcja==0){addEnd(val);}
    else if(opcja==1){addFront(val);}
    else if(opcja==2){addMid(val, index);}
}

template <typename E, typename P>
void Dynamic<E, P>::remove(int index)
{
    int a=array[index]; //zapamietujemyw wartosc by wypisac ja na koncu
    //przesuwamy elementy w lewo
    if(size>0)
    {
    for(int i=index; i<size-1; i++)
    {
        array[i]=array[i+1];
    }
    size--;
    //std::cout << "Z " << index << " usunieto: " << a << std::endl;
    }
}

template <typename E, typename P>
void Dynamic<E, P>::removeMid(int index){
    if(size>0){remove(index);}
}

template <typename E, typename P>
void Dynamic<E, P>::removeEnd(){
    if(size>0){array[size-1]=array[size]; size--;}
}

template <typename E, typename P>
void Dynamic<E, P>::removeFront(){
    remove(0);
}





