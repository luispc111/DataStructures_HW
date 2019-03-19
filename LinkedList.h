// Luis Alberto Pérez Chapa
// A01282564

// Clase de Lista Encadenada

#include "Node.h"
#include <iostream>

template <class T>
class LinkedList {
	
	// Atributos publicos
	public:
		LinkedList();
		~LinkedList();
	
		void addFirst(T data);
		void addLast(T data); 
		bool add(T data, int pos);
	
		bool isEmpty();
	
		void deleteFirst();
		void deleteLast();
		void del(int pos);
		int deleteAll();
	
		int getSize();
	
		T set(T dato, int pos);
		T get(int pos);
		bool change(int pos1, int pos2);
	
		void print();
		void reverse();
		
		// Operadores
		bool operator==(const LinkedList <T> LL2);
		void operator+= (T data);
		void operator+= (const LinkedList <T> LL2);
		LinkedList(const LinkedList <T> &LLCopy);
		void operator=(LinkedList <T> &LL);
		
	// Atributos privados
	private:
		Node<T> *head;
		int size;
		void deleteHelper();
};

// Constructor default
template <class T>
LinkedList<T>::LinkedList() {
	head = NULL;
	size = 0;
}

// Destructor
template <class T>
LinkedList<T>::~LinkedList() {
	deleteHelper();
}

// Checa si la lista esta vacia
template <class T>
bool LinkedList<T>::isEmpty() {
	return (head == NULL);
	//return (size == 0)
}

// Añade un nodo en la primera posición, recorriendo todos los demás nodos
template <class T>
void LinkedList<T>::addFirst(T data) {
	head = new Node<T>(data, head);
	size++;
}

// Añade un nodo en la ultima posición
template <class T>
void LinkedList<T>::addLast(T data) {
	if (size == 0) {
		addFirst(data);
	}
	else {
		Node<T> *curr = head;
		while (curr->getNext() != NULL) {
			curr = curr->getNext();
		}
		curr->setNext(new Node<T>(data, NULL));
		size++;
	}
}

// Borra el primer nodo
template <class T>
void LinkedList<T>::deleteFirst() {
	if (!this->isEmpty()) { // size != 0
		Node<T> *curr = head;
		head = head->getNext();
		delete curr;
		size--;
	}
}

// Regresa la cantidad de nodos en la lista encadenada
template <class T>
int LinkedList<T>::getSize() {
	return size;
}

// Borra el ultimo nodo
template <class T>
void LinkedList<T>::deleteLast() {
	if (size <= 1) {
		deleteFirst();
	}
	else {
		Node<T> *curr = head;
		while (curr->getNext()->getNext() != NULL) {
			curr = curr->getNext();
		}
		delete curr->getNext();
		curr->setNext(NULL);
		size--;
	}
}

// Añade un nodo en la posición deseada
template <class T>
bool LinkedList<T>::add(T data, int pos) {
	if (pos > size)
		return false;
	if (pos == 0) {
		addFirst(data);
	}
	else if (pos == size) {
		addLast(data);
	}
	else {
		Node<T> *curr = head;
		for (int i = 1; i < pos; i++) {
			curr = curr->getNext();
		}
		curr->setNext(new Node<T>(data, curr->getNext()));
		size++;
	}
	return true;
 }

// Elimina un nodo en la posición deseada
template <class T>
void LinkedList<T>::del(int pos) {
	if (pos < size) {
		if (pos == 0) {
			deleteFirst();
		}
		else if (pos == size-1) {
			deleteLast();
		}
		else {
			Node<T> *curr = head;
			for (int i = 1; i < pos; i++) {
				curr = curr->getNext();
			}
			Node<T> *temp = curr->getNext();
			curr->setNext(temp->getNext());
			delete temp;
			size--;
		}
	}
}

// Borra todos menos el head
template <class T>
void LinkedList<T>::deleteHelper() {
	Node<T> *curr = head;
	while (!this->isEmpty()) {
		head = head->getNext();
		delete curr;
		curr = head;
	}
}

// Borra todos menos el head
template <class T>
int LinkedList<T>::deleteAll() {
	int cant = size;
	Node <T> *curr = head;
	while (! this->isEmpty()){
		head = head->getNext();
		delete curr;
		curr = head;
	}
	size = 0;
	return cant;
}

// Regresa la información almacenada en el nodo deseado
template <class T>
T LinkedList<T>::get(int pos) {
	Node<T> *curr = head;
	for (int i = 0; i < pos - 1 && curr->getNext() != NULL; i++) {
		curr = curr->getNext();
	}
	return curr->getData();
}

// Cambia la información de un nodo en particular
template <class T>
T LinkedList<T>::set(T dato, int pos) {
	Node<T> *curr = head;
	for (int i = 0; i < pos-1; i++) {
		curr = curr->getNext();
	}
	T datoNodo = curr->getData();
	curr->setData(dato);
	return datoNodo;
}

// Cambia la información de dos nodos, uno por el otro
template <class T>
bool LinkedList<T>::change(int pos1, int pos2) {
	
	if (pos1 == pos2){
		return true;	
	}

	int posMen = (pos1 < pos2 ? pos1 : pos2);
	int posMay = (pos1 > pos2 ? pos1 : pos2);

	Node<T> *curr = head;
	for (int i = 1; i <= posMen; i++) {
		curr = curr->getNext();
	}
	Node<T> *curr2 = curr;
	for (int i = posMen; i < posMay; i++) {
		curr2 = curr2->getNext();
	}
	T dato = curr->getData();
	curr->setData(curr2->getData());
	curr2->setData(dato);
	return true;
}

// Imprime la información de una lista encadenada
template <class T>
void LinkedList<T>::print() {
	Node<T> *curr = head;
	while (curr != NULL) {
		cout << curr->getData() << " ";
		curr = curr->getNext();
	}
	cout << endl;
}

// Gira el sentido de la lista encadenada
template <class T>
void LinkedList<T>::reverse(){
	
	if (size > 2) {
		Node<T> *curr1 = NULL, *curr2 = head->getNext();
		while (curr2 != NULL) {
			head->setNext(curr1);
			curr1 = head;
			head = curr2;
			curr2 = head->getNext();
		}
		head->setNext(curr1);
		delete curr2;
	}
}

// Compara dos listas encadenadas y su contenido
template <class T>
bool LinkedList<T>::operator==(const LinkedList <T> LL2){
	
	if (this->size == LL2.size){
		Node<T> *curr1 = head, *curr2=LL2.head;
		for (int i = 0; i < size; i++){
			if (curr1->getData() != curr2->getData()){
				return false;
			}	
			curr1 = curr1->getNext();
			curr2 = curr2->getNext();
		}
	return true;	
	}
	return false;
}

// Añade un nodo con información al final de la lista
template <class T>
void LinkedList<T>::operator+= (T data){
	addLast(data);
}

// Añade una lista a otra, sin borrar añadida
template <class T>
void LinkedList<T>::operator+= (LinkedList <T> LL2){
	
	if (LL2.size > 0) {
		Node<T> *curr2 = LL2.head;
		if (size == 0) {
			head = new Node<T>(curr2->getData(), head);
			curr2 = curr2->getNext();
		}
		
		Node<T> *curr = head;
		while (curr->getNext() != NULL) {
			curr = curr->getNext();
		}
		
		while (curr2 != NULL) {
			curr->setNext(new Node<T>(curr2->getData(), NULL));
			curr = curr->getNext();
			curr2 = curr2->getNext();
		}
		
		size += LL2.size;
	}
}

// Crea una copia de la lista
template <class T>
LinkedList<T>::LinkedList(const LinkedList <T> &LLCopy){
	
	this->size = LLCopy.size;
	this->head = new Node<T> (LLCopy.head->getData(), NULL);
	
	Node<T> *curr = this->head, *curr2 = LLCopy.head->getNext();
	
	while (curr2 != NULL) {
		curr->setNext(new Node<T>(curr2->getData(), NULL));
		curr = curr->getNext();
		curr2 = curr2->getNext();
	}

}

// Asigna una lista dentro de otra
template <class T>
void LinkedList<T>::operator=(LinkedList <T> &LL){

	if (!isEmpty()){
		deleteAll();
	}
	
	Node<T> *curr = LL.head;
	
	for (int i = 0; i < LL.size; i++){
		addLast(curr->getData());
		curr = curr->getNext();
	}	
}

