// Priority.h
// Luis Alberto Pérez Chapa
// A01282564

#include <vector>

class Priority {
	public:
		Priority();
		Priority(bool pri);
		
		void push(int val);
		int top();
		int size();
		bool empty();
		void pop();
		
	private:
		vector<int> vec;
		bool prior;
		void changePush(int n);
		void changePop(int a);
};

Priority::Priority(){
	prior = true;
}

Priority::Priority(bool pri){
	prior = pri;
}

void Priority::push(int val){
	
	vec.push_back(val);
	if (vec.size() != 1){
		changePush(vec.size());	
	}
}

int Priority::top(){
	return vec.front();
}

int Priority::size(){
	return vec.size();
}

bool Priority::empty(){
	if (vec.size() == 0){
		return true;
	}
	return false;
}

void Priority::changePush(int n){
	n -= 1;
	while (n > 0){
		if (this->prior){
			if (vec[n] > vec[n/2]){	
				int a = vec[n];
				vec[n] = vec[n/2];
				vec[n/2] = a;
			}
			else{
				return;
			}
		}
		else{
			if (vec[n] < vec[n/2]){	
				int a = vec[n];
				vec[n] = vec[n/2];
				vec[n/2] = a;
			}
			else{
				return;
			}
		}
		n = n/2;
	}	
}

void Priority::pop(){
	vec[0] = vec[vec.size()-1];
	vec.pop_back();
//	int x = vec.size()/2;
//	changePop(x);
	changePop(vec.size()/2);
}

void Priority::changePop(int n){
		
//		if (this->prior){
//			if(vec.size() % 2 == 0){
//				if (vec[n*2-1]>vec[n-1]){
//					int a = vec[n];
//					vec[n] = vecn*2-1];
//					vec[n*2-1] = a;
//				}
//			}
//		}
//		else{
//			if(vec.size() % 2 == 0){
//				if (vec[n*2-1]<vec[n]){
//					int a = vec[n];
//					vec[n] = vecn*2-1];
//					vec[n*2-1] = a;
//				}
//			}
//		}
//	n--;
	
	int a;
	while (n > 0){		
		if (this->prior){
			if (n==vec.size()/2 && vec.size() % 2 == 0){
				if (vec[n]<vec[n*2]){
					a = vec[n];
					vec[n] = vec[n*2];
					vec[n*2] = a;
				}
			}
			else{
				if (vec[n]<vec[n*2] || vec[n]<vec[(n*2)+1]){
					a = (vec[n*2] > vec[(n*2)+1]) ? vec[n*2] : vec[(n*2)+1];
					vec[n] = (vec[n*2] > vec[(n*2)+1]) ? vec[n*2] : vec[(n*2)+1];
					(vec[n*2] > vec[(n*2)+1]) ? vec[n*2] : vec[(n*2)+1] = a;
				}
			}
		}
		else{
			if (n==vec.size()/2 && vec.size() % 2 == 0){
				if (vec[n]>vec[n*2]){
					a = vec[n];
					vec[n] = vec[n*2];
					vec[n*2] = a;
				}
			}
			else{
				if (vec[n]>vec[n*2] || vec[n]>vec[(n*2)+1]){
					a = (vec[n*2] < vec[(n*2)+1]) ? vec[n*2] : vec[(n*2)+1];
					vec[n] = (vec[n*2] < vec[(n*2)+1]) ? vec[n*2] : vec[(n*2)+1];
					(vec[n*2] < vec[(n*2)+1]) ? vec[n*2] : vec[(n*2)+1] = a;
				}
			}
		}
		n--;
	}
}



