#pragma once


template <typename E, typename P>
class MaxPriorityList: public SLinkedList<E, P> 
{
    public:
    //usunięcie i zwrócenie elementu o największym priorytecie
    //podgladmay element o najwyzszym priorytecie
    int peekVal()const {return SLinkedList<E, P>::getHead()->value;}        //zwraca wartosc max elementu
    int peekPrio()const {return SLinkedList<E, P>::getHead()->priority;}    //zwraca max priorytet
    int return_size()const {return SLinkedList<E, P>::ile();}               //zwrócenie rozmiaru
    //wypisuje parami (value, priority) od max
    void wypisz() const
    {
        SingleNode<E, P>* current = SLinkedList<E, P>::getHead();
        while(current!=NULL){std::cout <<"(" <<current->value <<", "<<current->priority<<")"<<std::endl; current = current->next;} //dopoki nie natrafimy na ostatni element wypisuj
    }

    void insert(const E& val, const P& key);         //dodanie elementu e o priorytecie key, na zasadzie fifo
    void modify(int where, const P& key);            //zmiana priorytetu elementu e na p
    void increase(SingleNode<E, P>* temp, P key);    //do funkcji modify, gdy zwiekszamy klucz
    void decrease(SingleNode<E, P>* temp, P key);    //gdy zmniejszamy klucz

    std::pair<E, P> peek() const
    {
        std::pair<E, P> result;
        result.first = peekVal();
        result.second = peekPrio();
        return result;
        //std::pair<int, int> extracted = g1.peek(); std::cout <<"(" <<extracted.first <<", "<<extracted.second<<")"<<std::endl;
    }
    
    std::pair<E, P> extract_max()                              
    {
        std::pair<E, P> result = peek();
        SLinkedList<E, P>::removeFront();
        return result;
        //wypisanie
        //std::pair<int, int> extracted = g1.extract_max(); std::cout <<"(" <<extracted.first <<", "<<extracted.second<<")"<<std::endl;
    }
 
};

template <typename E, typename P>
void MaxPriorityList<E,P>::insert(const E& val, const P& key)         
{       
    //jezeli priorytet dodawanego ele jest wiekszy od obecnego max lub lista jest pusta, doodaj na poczatek
    if(SLinkedList<E, P>::empty()) {SLinkedList<E, P>::addFront(val, key);}    
    else if((SLinkedList<E, P>::getHead()->priority) < key)  {SLinkedList<E, P>::addFront(val, key);}

        else    //szukamy odpowiedniego miejsca i potem addMid
        {
            int location=1;                                                 //zerowy indeks
            SingleNode<E, P>* temp1 = SLinkedList<E, P>::getHead();         //iterator
            for(int i=0; i<return_size(); i++)
            {
                if(temp1->next==NULL){break;}
                if(temp1->next->priority<key){break;}
                temp1=temp1->next;
                location++;
                //sprawdzamy czy nastepny element tez nie ma tego samego priorytetu, jezeli tak to przesuwamy sie az do konca tego prioryteu, aka fifo
            }

            if(location==return_size()){SLinkedList<E, P>::addEnd(val, key);} 
            else
            {
                SLinkedList<E, P>::addMid(val, location, key);  //dodajemy w odpowienide meijsce 
            }
        }
}

template <typename E, typename P>
void MaxPriorityList<E,P>::modify(int where, const P& key)       
{
        if(where<0 || where>=return_size()){return;}    //element musi miescic sie w zakresie inczaej go nie dodajemy

        SingleNode<E, P>* temp1=SLinkedList<E, P>::getHead();   //element w ktorym zmeiniamy klucz
        SingleNode<E, P>* temp2=SLinkedList<E, P>::getHead();   //element przed nim
        //dostanmy sie do elementu ktory chcemy zmodyfikowac
        for(int i=0; i<where; i++)
        {
            temp2=temp1;
            temp1=temp1->next;
        }

        P old_pro=temp1->priority;
        temp1->priority=key;    //zamieniamy priorytet

        if(old_pro==key) {return;}                     //jezeli klucz jest taki sam nic nie zmieniamy
        
        //zmiana wskaznika next elementu przed modyfikowanym
        if(where==0){SLinkedList<E, P>::setHead(temp1->next);}  //ustawianie odpowienio glowy jezeli indeks 0
        else if(temp1->next==NULL && old_pro>key){return;}      //jezeli to byl ostatni element (najmniejszy priorytet) to tylko zmien klcuz
        else {temp2->next=temp1->next;}

        if(old_pro > key) {increase(temp1, key);}           //klucz mnijszy od zmiany wiec swap jest od tymczaswoego
        else if(old_pro < key) {decrease(temp1, key);}      //klucz wiekszy od zminay wiec swap jest od head
}

template <typename E, typename P>
void MaxPriorityList<E,P>::increase(SingleNode<E, P>* temp, P key)
{
        SingleNode<E, P>* temp2=SLinkedList<E, P>::getHead();
        SingleNode<E, P>* temp3=SLinkedList<E, P>::getHead();   //poprzedni

        for(int i=0; i<return_size(); i++)
        {
            if(temp2==NULL){break;}
            if(temp->priority > temp2->priority)  //jezeli klucz jest wiekszy od klucza obencego elementu to wrzucamy 
            {break;}
            
            temp3=temp2;
            temp2=temp2->next;
        }
        //nastawiamy head
        if(temp3==temp2)
        {   temp->next=temp3;
            SLinkedList<E, P>::setHead(temp);
            return;
        }
    
        temp3->next=temp;
        temp->next=temp2;

}

template <typename E, typename P>
void MaxPriorityList<E,P>::decrease(SingleNode<E, P>* temp, P key)
{
        SingleNode<E, P>* temp2=temp->next;
        SingleNode<E, P>* temp3=temp;      //poprzedni
  

        for(int i=0; i<return_size(); i++)
        {
            if(temp3->next==NULL){break;}
            //trzeba przepisac odpowiendio 2 wskazniki, tego przed i naszego temp
            if(temp->priority > temp2->priority)  //jezeli klucz jest wiekszy od klucza obencego elementu to wrzucamy 
            {
                break;
            }
            temp3=temp2;
            temp2=temp2->next;
        }

        temp3->next=temp;
        temp->next=temp2;

}



