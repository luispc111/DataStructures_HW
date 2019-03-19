#include "Node.h"

template <class T>
class queue {
    public:
        queue();
        ~queue();

        T front();
        void push(T data);
        void pop();
        int size();
        bool empty();

    private:
        Node<T> *fin;
        int tam;
};

template <class T>
queue<T>::queue(){
    fin = NULL;
    tam = 0;
}

template <class T>
queue<T>::~queue(){
    Node<T> *curr = fin->getNext();
    if (fin != NULL){
        fin->setNext(NULL);
        fin = curr;
    }
    while (fin != NULL){
        fin = fin->getNext();
        delete curr;
        curr = fin;
    }
}

template <class T>
T queue<T>::front(){
    return fin->getNext()->getData();
}

template <class T>
int queue<T>::size(){
    return tam;
}

template <class T>
bool queue<T>::empty(){
    return fin == NULL;
}

template <class T>
void queue<T>::push(T data){
    if (fin == NULL){
        fin = new Node<T>(data);
        fin->setNext(fin);
    }
    else{
        fin ->setNext(new Node<T>(data, fin->getNext()));
        fin = fin->getNext();
    }
    tam++;
}

template <class T>
void queue<T>::pop(){

    Node <T> * curr = fin->getNext();
    if (fin->getNext() == fin){
        fin = NULL;
    }
    else{
        fin->setNext(curr->getNext());
    }
    delete curr;
    tam--;
}









