#pragma once


template<typename E, typename P>
class PriorityQueueMax:public Dynamic<E, P>
{

public:
int return_size()const {return Dynamic<E,P>::what_size();}
int what_value(int i)const {return Dynamic<E,P>::ret_value(i);}
int what_key(int i)const{return Dynamic<E,P>::ret_priority(i);}
void insert(const E& val, const P& key);
void heapify_up(int u);                         //pomocnicza funkcja przesuwamy w gore kopca
void heapify_down(int u);                       //pomocnicza funkcja rzesuwamy w dol kopca
void modify(int where, const P& key);           //zmiana priorytetu, key
std::pair<E, P> peek() const;                   //podejrzenie, aka zwrocenie wartosci z gory, dla max key
std::pair<E, P> extract_max();                  //usuniecie i zwrocenie usunietej wartosci
void wypisz()const;

};

template<typename E, typename P>
void PriorityQueueMax<E,P>::wypisz()const
{
int i = 0;  
while (i < return_size())
{
    //wypisywanie rodzic lewe i prawe dzeicko
    /*
    std::cout << "(" << what_value(i) << ", " << what_key(i) << ")";
        
    int left = 2 * i + 1;
    int right = 2 * i + 2;
        
    if (left < return_size())
    {
        std::cout << " left (" << what_value(left) << ", " << what_key(left) << ")";
    }
        
    if (right < return_size())
    {
        std::cout << " right (" << what_value(right) << ", " << what_key(right) << ")";
    }
        
    std::cout << std::endl;   
    i++;
    
    */
   
   //wypisywanie normalnie wedlug indeksu w tablicy
    std::cout << "(" << what_value(i) << ", " << what_key(i) << ")";
    i++;
    
}
}

template<typename E, typename P>
void PriorityQueueMax<E,P>::insert(const E& val, const P& key)
{
    typename Dynamic<E, P>::Node newNode;
    newNode.value = val;
    newNode.priority = key;
    Dynamic<E,P>::addEnd(newNode);
    heapify_up(return_size() - 1); //od samego dolu maszerujemy do gory
}

template<typename E, typename P>
void PriorityQueueMax<E,P>::heapify_up(int u)
{
    while (u > 0)   //przemieszczamt dopoki nie dojdziemy do roota
    {
        P key_u=what_key(u);                    //priorytet naszego element
        P key_parent=what_key((u - 1) / 2);     //priorytet rodzica
        //jezeli key rodzica jest wiekszy od key dziecka prawidłowa pozycja w kopcu, break
        if((key_u < key_parent)){break;}  //
        //inczej zamien rodzica i dziecko miejscami
        Dynamic<E,P>::wymiana(u, ((u - 1) / 2));
        u = (u - 1) / 2;    //idzeimy w gore w drzewie
    }
}

template<typename E, typename P>
void PriorityQueueMax<E,P>::heapify_down(int u)
{

while(1)
{
    int left=2*u+1;
    int right=2*u+2;
    int newparent=u;

    //porównujemy priorytety rodzica (podanego indeksu) z jego dziecmi
    //jezeli prawe dziecko istnieje(index w zakresie romiaru) i jest wieksze od rodzica przypisz
    if (left < return_size() && (what_key(left) >= what_key(newparent)))
    {
        newparent = left;
    }
        
    //jezeli lewe istnieje i jest wieksze od rodzica przypsiz
    if (right < return_size() && (what_key(right) >= what_key(newparent)))
    {
        newparent = right;
    }

    //jezeli ktores dziecko okazalo sie wieksze od rodzica zamien miejscami
    if(newparent!=u)
    {
        Dynamic<E,P>::wymiana(u, newparent);
        u = newparent;
    }
    //i rekurencyjnue kontynulujemy, za kazdym razem glebiej

    else{break;}    //jezeli dzieci nie sa wiekszze od rodzica, prawidlowe miejsce wychodzimy
}   


}

template<typename E, typename P>
void PriorityQueueMax<E,P>:: modify(int where, const P& key)
{
P old_key=what_key(where);
if(old_key==key){return;}

Dynamic<E, P>::change_key(where, key);              //zmiana wartosci priorytetu
if(key>old_key){heapify_up(where);}                 //szukamy nwoego miejsca przesuwamy w gore
else if(key<old_key){heapify_down(where);}           //szukamy nowego miejsca przesuwamy w dol
}

template<typename E, typename P>
std::pair<E, P> PriorityQueueMax<E,P>::peek() const
{
    std::pair<E, P> result;
    result.first = Dynamic<E,P>::array[0].value;
    result.second = Dynamic<E,P>::array[0].priority;
    return result;
    //std::pair<int, int> extracted = g1.peek(); std::cout <<"(" <<extracted.first <<", "<<extracted.second<<")"<<std::endl;
}

template<typename E, typename P>
std::pair<E, P> PriorityQueueMax<E,P>::extract_max()
{
    std::pair<E, P> result;    //zapamietany korzen
    result=peek();
    Dynamic<E,P>::zmiana(return_size()-1);  //wstawiamy ostatni element w roota (dzieki nie trzeba przesuwac calego kopca z removeFront)
    Dynamic<E,P>::removeEnd();   //uswuamy jego kopie z konca
    heapify_down(0);            //przesuwamy go w dol
    return result;
    //std::pair<int, int> extracted = g1.extract_max(); std::cout <<"(" <<extracted.first <<", "<<extracted.second<<")"<<std::endl;
}
