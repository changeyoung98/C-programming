#include<memory>
using namespace std;


template<typename T>
class Stack {
	class Node {
	public:
		T value;
		shared_ptr<Node> next;
		Node(T v) : value(v), next(NULL) {}
	};                                        //build a Node class

	shared_ptr<Node> top;                     //the top of the stack is a Node
	int size;
public:
	Stack();
	Stack(const Stack&) = delete;
	Stack& operator=(const Stack&) = delete;
	void push(T elem);
	bool pop(T& cell);
	~Stack() {};
};

template<typename T>
Stack<T>::Stack() {
	top = NULL;
}
template<typename T>
void Stack<T>::push(T elem) {
	shared_ptr<Node> node(new Node(elem));
	if (top == NULL) {
		top = move(node);
	}                          //when it is a null stack
	else  {
		node.get()->next = move(top); //previous top become next of node
		top = move(node);               //node become top
	}
	size++;
}

template<typename T>
bool Stack<T>::pop(T& cell) {
	if (top != NULL) {
		cell = top.get()->value;          //the value of top
		top = top.get()->next;            //next of top become the new top
		size--;
		return true;
		
	}
	else {
		return false;
	}
}