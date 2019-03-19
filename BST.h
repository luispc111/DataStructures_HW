#include "NodeT.h"
#include <stack>
#include <queue>
#include <set>

class BST{
	public:
		BST();
		~BST();
		BST(const BST &tree);
		
		void add(int data);
		bool search(int data);
		void remove(int data);
		
		int height();
		void ancestors(int data);
		int whatLevelamI(int data);
		void print(int c);
		
		int nearestRelative(int a, int b);
		int maxWidth();
		
		void mirror(NodeT &tree);
		bool operator==(BST tree);
		
		int count();
				
	private:
		NodeT *root;
		int howManyChildren(NodeT *r);
		int pred(NodeT *r);
		int succ(NodeT *r);
		void preOrder(NodeT *r);
		void inOrder(NodeT *r);
		void postOrder(NodeT *r);
		void liberar(NodeT *r);
		
		void preHeight(NodeT *r, int max, int &level);
		void levelXlevel(NodeT *r);
		void printLeaves(NodeT *r);
		
		int cuenta(NodeT *r);
		void copy (NodeT *root1, NodeT *root2);
		void equal (NodeT *R1, NodeT *R2, bool &Validator);
};

BST::BST(){
	root=NULL;
}

BST::~BST(){
	liberar(root);
}

int BST::howManyChildren(NodeT *r){
	int cont = 0;
	if (r->getLeft() != NULL){
		cont++;
	}
	if (r->getRight() != NULL){
		cont++;
	}
	return cont;
}

int BST::pred(NodeT *r){
	NodeT *aux = r->getLeft();
	while (aux->getRight() != NULL){
		aux = aux->getRight();
	}
	return aux->getData();
}

int BST::succ(NodeT *r){
	NodeT *aux = r->getRight();
	while (aux->getLeft() != NULL){
		aux = aux->getLeft();
	}
	return aux->getData();
}

void BST::preOrder(NodeT *r){
	if (r != NULL){
		cout << r->getData() << " ";
		preOrder(r->getLeft());
		preOrder(r->getRight());
	}
}

void BST::inOrder(NodeT *r){
	if (r != NULL){
		inOrder(r->getLeft());
		cout << r->getData() << " ";
		inOrder(r->getRight());
	}
}

void BST::postOrder(NodeT *r){
	if(r != NULL){
		postOrder(r->getLeft());
		postOrder(r->getRight());
		cout << r->getData() << " ";
	}
}

void BST::liberar(NodeT *r){
	if (r != NULL){
		liberar(r->getLeft());
		liberar(r->getRight());
		delete r;
	}
}

bool BST::search(int data){
	NodeT *curr = root;
	while (curr!= NULL){
		if(curr -> getData() == data){
			return true;
		}
		curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
	}
	return false;
}

void BST::add(int data){
	NodeT *curr = root;
	NodeT *father = NULL;
	while (curr != NULL){
		if(curr->getData() == data){
			return;
		}
		father = curr;
		curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
	}
	
	if (father == NULL){
		root = new NodeT(data);
	} 
	else{
		if (father->getData() > data){
			father->setLeft(new NodeT(data));
		}
		else{
			father->setRight(new NodeT(data));
		}
	}
}

void BST::remove(int data){
	NodeT *father = NULL;
	NodeT *curr = root;
	
	while (curr != NULL && curr->getData() != data){
		father = curr;
		curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight(); 
	}
	
	if (curr == NULL){
		return;
	}
	int c = howManyChildren(curr);
	
	switch (c){
		case 0:
			if (father == NULL){
				root = NULL;
			}
			else{
				if (father->getData() > data){
					father->setLeft(NULL);
				}	
				else{
					father->setRight(NULL);
				}
			}
			delete curr;
			break;
			
			
		case 1:
			if (father == NULL){
				if(curr->getLeft() != NULL){
					root = curr->getLeft();
				}
				else{
					root=curr->getRight();
				}
			}
			else{
				if (father->getData() > data){
					if (curr->getLeft() != NULL){
						father->setLeft(curr->getLeft());
					}
					else{
						father->setLeft(curr->getRight());
					}
				}
				else{
					if (curr->getLeft() != NULL){
						father->setRight(curr->getLeft());
					}
					else{
						father->setRight(curr->getRight());
					}
				}
			}
			delete curr;
			break;
			
		case 2:
			int x = succ(curr);
			remove(x);
			curr->setData(x);
			break;
	}
}

void BST::print(int c){
	
	switch (c){
		case 1:
			preOrder(root);
			break;
						
		case 2:
			inOrder(root);
			break;
			
		case 3:
			postOrder(root);
			break;
		case 4:
			printLeaves(root);
			break;
		case 5: 
			levelXlevel(root);
			break;
	}	
	cout << endl;
}

void BST::preHeight(NodeT *r, int max, int &level){
	if (r != NULL){
		if (max > level){
			level = max;
		}
		max++;
		preHeight(r->getLeft(), max, level);
		preHeight(r->getRight(), max, level);
	}
}

int BST::height(){
	int max= 1, level= 1;
	preHeight(root, max, level);
	return level;
}

void BST::ancestors(int data){
	stack<int> stack;
	NodeT *curr = root;
	if (curr != NULL){
		
		stack.push(curr->getData());
		
		while (curr->getData() != data){
			stack.push(curr->getData());
			curr = (data < curr->getData()) ? curr->getLeft() : curr->getRight();
		}
		
		for(int i=0; i<=stack.size(); i++){
			cout << stack.top() << " ";
			stack.pop();
		}
		cout << endl;
		return;
	}
		cout << "NO ESTA EL DATO" << endl;
}

int BST::whatLevelamI(int data){
	NodeT *curr = root;
	int iLevel = 0;

	while (curr != NULL){

		if (curr->getData() == data){
			return iLevel;
		}
		curr = (data < curr->getData()) ? curr->getLeft() : curr->getRight();
		iLevel++;
	
		
		if (curr->getData() == data){
			return iLevel;
		}
		return -1;
	}
}

void BST::levelXlevel(NodeT *r){
	if (r != NULL){
		
		queue<NodeT*> fila;
		fila.push(r);
		
		while (fila.size() != 0){
			if (fila.front()->getLeft() != NULL){
				fila.push(fila.front()->getLeft());
			}
			if (fila.front()->getRight() != NULL){
				fila.push(fila.front()->getRight());
			}
			cout << fila.front()->getData() << " ";
			fila.pop();
		}
		return;
	}
	cout << "NO HAY DATOS" << endl;
}

void BST::printLeaves(NodeT *r){
	if (r != NULL){
		if (r->getRight() == NULL && r->getLeft() == NULL){
			cout << r->getData() << " ";
		}
		else{
			printLeaves(r->getLeft());
			printLeaves(r->getRight());
		}	
	}
}

int BST::count(){
	return cuenta(root);
}

int BST::cuenta(NodeT *r){
	if (r == NULL){
		return 0;
	}
	return 1+cuenta(r->getLeft())+cuenta(r->getRight());
}

int BST::nearestRelative(int a, int b){
	
	set<int> mySet;
	
	NodeT *curr = root;
	while (curr->getData() != a){
		mySet.insert(curr->getData());
		curr = (a < curr->getData()) ? curr->getLeft() : curr->getRight();
	}
	
	
	
	int sizeA = mySet.size(), iCurr;
	curr = root;
	
	while (curr->getData() != b){
		
		mySet.insert(curr->getData());
		if(mySet.size() != sizeA){
			return iCurr;
		}
		
		iCurr = curr->getData();
		curr = (b < curr->getData()) ? curr->getLeft() : curr->getRight();
	}
}

int BST::maxWidth(){
	
	queue<NodeT*> fila;
	fila.push(root);
	
	int iCount=1, iMax = 0, iCurr=1;
	
	if (root != NULL){
		
		iMax = 1;
		while (fila.front() != NULL){
			iCount = 0;
			while (iCurr > 0){	
				if (fila.front()->getLeft() != NULL){
					fila.push(fila.front()->getLeft());
					iCount++;
				}
				if (fila.front()->getRight() != NULL){
					fila.push(fila.front()->getRight());
					iCount++;
				}
				fila.pop();
				iCurr--;
			}
			iCurr = iCount;
			iMax = (iCount > iMax) ? iCount : iMax;
		}
	}
	return iMax;
}

void BST::mirror(NodeT &tree){
	queue<NodeT*> fila;
	fila.push(root);
	
	int iCurr=1;
	NodeT *curr;
	
	if (root != NULL){
		while (fila.front() != NULL){
			while (iCurr > 0){	
			
				if (fila.front()->getLeft() != NULL || fila.front()->getRight() != NULL){
					curr = fila.front()->getLeft();
					fila.front()->setLeft(fila.front()->getRight());
					fila.front()->setRight(curr);
				}
				
				if (fila.front()->getLeft() != NULL){
					fila.push(fila.front()->getLeft());
				}
				if (fila.front()->getRight() != NULL){
					fila.push(fila.front()->getRight());
				}
				fila.pop();
				iCurr--;
			}
			iCurr = fila.size();
		}
	}
}


BST::BST(const BST &tree){
	if (tree.root == NULL){
		root = NULL;
		
	}
	else{
		root = (tree.root);	
		NodeT *curr = root;
		copy(curr, tree.root);
	}
}

void BST::copy(NodeT *root1, NodeT *root2){
	
	if (root1 == NULL){
		return;
	}
	if (root1->getRight() != NULL && root2->getLeft() != NULL) {
		root1->setLeft(new NodeT(root2->getLeft()->getData()));
		root1->setRight(new NodeT(root2->getRight()->getData()));
		copy(root1->getLeft(), root2->getLeft());
		copy(root1->getRight(), root2->getRight());
	}
	else if (root2->getRight()==NULL && root2->getLeft()!=NULL) {
		root1->setLeft(new NodeT(root2->getLeft()->getData()));
		copy(root1->getLeft(), root2->getLeft());
	}
	else if (root2->getRight()!=NULL && root2->getLeft()==NULL) {
		root1->setRight(new NodeT(root2->getRight()->getData()));
		copy(root1->getRight(), root2->getRight());		
	}
	else {
		return;
	}
}

bool BST::operator==(BST tree){
	if (root == NULL && tree.root == NULL){
		return true;
	}
	else{
		bool Validator = true;
		equal(root, tree.root, Validator);
		return Validator;	
	}		
}

void BST::equal(NodeT *R1, NodeT *R2, bool &Validator){
	if (Validator == false){
		return;	
	}
	else if (R1 == NULL && R2 == NULL){
		return;
	}
	else if ((R1 == NULL && R2 != NULL) || (R1 != NULL && R2 == NULL)){
		Validator = false;
		return;
	}
	else if (R1->getData() != R2->getData()){
		Validator = false;
	}
	
	equal(R1->getLeft(), R2->getLeft(), Validator);
	equal(R1->getRight(), R2->getRight(), Validator);
} 

