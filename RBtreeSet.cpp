#include<iostream>
#include<vector>

class RBTree
{
public:
	class Node
	{
	public:
		bool isRed;
		int val;
		Node* left;
		Node* right;
		Node() : val(0), isRed(true), left(NULL), right(NULL) {}
		Node(int v) : val(v), isRed(true), left(NULL), right(NULL) {}
	};
	Node* root;
	std::vector<Node*>arr;
	RBTree() : root(NULL) {}
	RBTree(int v) : root(new Node(v)) {}
	~RBTree()
	{
		if (root != NULL)
		{
			destruct(root);
			delete root;
		}
		arr.clear();
	}

	void destruct(Node* node)
	{
		if (node->left != NULL)
		{
			destruct(node->left);
			delete node->left;

		}
		if (node->right != NULL)
		{
			destruct(node->right);
			delete node->right;

		}
	}

	bool isRed(Node* node)
	{
		if (node == NULL)
		{
			return false;
		}
		else
		{
			return node->isRed;
		}
	}

	void rotateRight(Node*& node)  
	{
		Node* temp = node->left;
		node->left = temp->right;
		temp->right = node;
		temp->isRed = node->isRed;
		node->isRed = true;
		node = temp;
	}

	void rotateLeft(Node*& node)
	{
		Node* temp = node->right;
		node->right = temp->left;
		temp->left = node;
		temp->isRed = node->isRed;
		node->isRed = true;
		node = temp;

	}

	void flipColor(Node*& node)
	{
		node->isRed = true;
		node->left->isRed = false;
		node->right->isRed = false;

	}

	void buildTree()
	{
		int tempArr[10] = { 3, 4, 7, 1, 2, 9, 8, 6, 5, 10 };
		for (int i = 0; i != 10; i++)
		{
			arr.push_back(new Node(tempArr[i]));
			insert(root, arr[i]);

		}
		display(root);
	}

	void insert(Node*& node, Node*& vNode)
	{
		if (node == NULL)
		{
			node = vNode;
		}

		if (node->val > vNode->val)
		{
			insert(node->left, vNode);

		}
		else if (node->val < vNode->val)
		{
			insert(node->right, vNode);
		}
		if (isRed(node->right) && !isRed(node->left))
		{
			rotateLeft(node);
		}
		if (isRed(node->left) && isRed(node->left->left))
		{
			rotateRight(node);
		}
		if (isRed(node->left) && isRed(node->right))
		{
			flipColor(node);
		}

	}

	void display(Node* node)
	{
		if (node == NULL)
		{
			return;
		}
		display(node->left);
		std::cout << node->val << " ";
		display(node->right);

	}

};

class Set : public RBTree {
private:
	RBTree mySet;
	//helper function
	bool containsHelper(Node* node, int x) {
		if (node == nullptr) {
			return false;
		}
		if (node->val == x) {
			return true;
		}
		return containsHelper(node->left, x) || containsHelper(node->right, x);
	}
	

public:
	Set() {}
	
	Set(int x) : RBTree(x) {
		mySet.root = new Node(x);
	}

	//initialize the set 
	void initializeSet(int* tempArr, int size) {
		for (int n = 0; n < size; ++n) {
			mySet.arr.push_back(new Node(tempArr[n]));
			mySet.insert(mySet.root, mySet.arr[n]);
		}
	}

	//checking if an element exists in the set
	bool contains(int x) {
		return containsHelper(mySet.root, x);
	}

	//insert an element into the set
	void insertSet(int x) {
		if (!contains(x)) {
			mySet.arr.push_back(new Node(x));
			mySet.insert(mySet.root, mySet.arr.back());
		}
		else {
			std::cout << x << " already exists" << "\n";
		}
	}
	

	//display the set elements
	void displaySet() {
		if (mySet.root == nullptr) {
			std::cout << " Empty set" << "\n";
			return;
		}
		RBTree::display(mySet.root);
		
	}
	

};


int main()
{
	/*RBTree rbtree;
	rbtree.buildTree();*/
	

	Set set;
	int array[] = { 3, 4, 7, 1, 2, 9, 8, 6, 10 };
	set.initializeSet(array, sizeof(array) / sizeof(array[0]));
	
	set.insertSet(4);
	set.insertSet(1);
	set.insertSet(10);
	set.insertSet(0);
	set.insertSet(11);
	set.insertSet(13);
	std::cout << std::boolalpha << set.contains(-1) << std::endl;
	std::cout << set.contains(30) << std::endl;
	std::cout << set.contains(3) << std::endl;
	set.displaySet();

	return 0;
}






