// Luis Alberto Pérez Chapa
// A01282564

// Clase de Nodos

#define NULL 0

template <class T>
class Node{
	
	// Atributos publicos
	public:
		Node(T data);
		Node(T data, Node<T> *next);
		T getData();
		Node<T>* getNext();
		void setData(T data);
		void setNext(Node<T> *next);		
	
		// Atributos privados
	private:
		// Info dentro de cada nodo
		T data;
		// Apuntador al proximo nodo en la lista encadenada
		Node<T> *next;		
};

// Constructor default
template <class T>
Node<T>::Node(T data){
	this -> data = data;
	this -> next = NULL;
}

// Constructor con variables
template <class T>
Node<T>::Node(T data, Node<T> *next){
	this -> data = data;
	this -> next = next;
}

// Get Data <T>
template <class T>
T Node<T>::getData(){
	return data;
}

// Get apuntador Next
template <class T>
Node<T>* Node<T>::getNext(){
	return next;
}

// Set Data <T>
template <class T>
void Node <T>::setData(T data){
	this -> data = data;
}

// Set apuntador Next
template <class T>
void Node <T>::setNext(Node<T> *next){
	this -> next = next;
}

