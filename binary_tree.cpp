#include <iostream>
#include <string>

using namespace std;

typedef struct Node
{
	int val;
	struct Node * left;
	struct Node * right; 
	struct Node * parent;
}node;

node * InsertNode(node * root, int val)
{
	if(root == NULL)
	{
		root = new node;
		root->val = val;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
	}
	else if(val <= root->val)
	{
		root->left = InsertNode(root->left,val);
		root->left->parent = root;
	}
	else if(val > root->val)
	{
		root->right = InsertNode(root->right,val);
		root->right->parent = root;
	}
	return root;
}

void InOrder(node * root)
{
	if(root == NULL)
	{
		return;
	}
	InOrder(root->left);
	cout << root->val << " ";
	InOrder(root->right);
}

void PreOrder(node * root)
{
	if(root == NULL)
	{
		return;
	}
	cout << root->val << " ";
	PreOrder(root->left);
	PreOrder(root->right);
}

void PostOrder(node * root)
{
	if(root == NULL)
	{
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	cout << root->val << " ";
}

int Height(node * root)
{
	if(root == NULL)
	{
		return(-1);
	}
	
	int lsh = Height(root->left);
	int rsh = Height(root->right);

	return(lsh > rsh ? lsh+1 : rsh+1);
}

int Leaf(node * root)
{
	if(root == NULL)
	{
		return(0);
	}
	
	int l = Leaf(root->left);
	int r = Leaf(root->right);
	
	if(l == 0 && r == 0)
	{
		return(1);
	}
	
	return(l+r);
}

int MaxVal(int x, int y)
{
	return(x > y ? x : y);
}

int Diameter(node * root)
{
	if(root == NULL)
	{
		return(0);
	}
	int lsd = Diameter(root->left);
	int rsd = Diameter(root->right);
	
	int lsh = Height(root->left);
	int rsh = Height(root->right);
	
	return(MaxVal(lsh+rsh+3,MaxVal(lsd,rsd)));
}

node * Search(node * root, int val)
{
	if(root == NULL)
	{
		return(root);
	}
	else if(root->val == val)
	{
		return(root);
	}
	else if(val < root->val)
	{
		Search(root->left,val);
	}
	else if(val > root->val)
	{
		Search(root->right,val);
	}
}

int Min(node * root)
{
	if(root->left == NULL)
	{
		return(root->val);
	}
	Min(root->left);
}

int Max(node * root)
{
	if(root->right == NULL)
	{
		return(root->val);
	}
	Max(root->right);
}

int Successor(node * root, int val)
{
	if(root->right != NULL)
	{
		return(Min(root->right));
	}
	node * succ = root->parent;
	while(succ->val < root->val)
	{
		root = succ;
		succ = root->parent;
	}
	return(succ->val);	
}

int Predecessor(node * root, int val)
{
	if(root->left != NULL)
	{
		return(Max(root->left));
	}
	node * succ = root->parent;
	while(succ->val > root->val)
	{
		root = succ;
		succ = root->parent;
	}
	return(succ->val);	
}

node * Delete(node * root, int val)
{
	if(val < root->val)
	{
		root->left = Delete(root->left,val);
	}
	else if(val > root->val)
	{
		root->right = Delete(root->right,val);
	}
	else
	{
		if(root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else if(root->right == NULL)
		{
			root->val = root->left->val;
			root->left = Delete(root->left,root->left->val);
		}
		else if(root->left == NULL)
		{
			root->val = root->right->val;
			root->right = Delete(root->right,root->right->val);
		}
		else
		{
			int k = Min(root->right);
			root->val = k;
			root->right = Delete(root->right,k);
		}
	}
	return root;
}

int main()
{
	node * root = NULL;
	string ch;
	while(1)
	{
		cin >> ch;
		if(ch == "insert")
		{
			int val;
			cin >> val;
			root = InsertNode(root,val);
		}
		else if(ch == "delete")
		{
			int val;
			cin >> val;
			root = Delete(root,val);
		}
		else if(ch == "inorder")
		{
			InOrder(root);
			cout << "\n";
		}
		else if(ch == "preorder")
		{
			PreOrder(root);
			cout << "\n";
		}
		else if(ch == "postorder")
		{
			PostOrder(root);
			cout << "\n";
		}
		else if(ch == "height")
		{
			cout << "Height of BST is: " << Height(root) << "\n";
		}
		else if(ch == "leaf")
		{
			cout << "Leaf nodes in BST are: " << Leaf(root) << "\n";
		}
		else if(ch == "diameter")
		{
			cout << "Diameter of the BST is: " << Diameter(root) << "\n";
		}
		else if(ch == "search")
		{
			int val;
			cin >> val;
			Search(root,val) != NULL ? cout << "Value Found in BST\n" : cout << "Value Not Found in BST\n";
		}
		else if(ch == "min")
		{
			cout << "Minimum value in the BST: " << Min(root) << "\n";
		}
		else if(ch == "max")
		{
			cout << "Maximum value in the BST: " << Max(root) << "\n";
		}
		else if(ch == "successor")
		{
			int val;
			cin >> val;
			node * temp = Search(root,val);
			if(temp->val == Max(root))
			{
				cout << "No Successor for " << val << "\n";
			}
			else
			{
				cout << "Successor of " << val << " is: " << Successor(temp,val) << "\n";
			}
		}
		else if(ch == "predecessor")
		{
			int val;
			cin >> val;
			node * temp = Search(root,val);
			if(temp->val == Min(root))
			{
				cout << "No Predecessor for " << val << "\n";
			}
			else
			{
				cout << "Predecessor of " << val << " is: " << Predecessor(temp,val) << "\n";
			}
		}
		else if(ch == "exit")
		{
			break;
		}
	}
	return(0);
}
