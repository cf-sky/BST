#include<iostream>
#include<functional>
#include<queue>
#include<stack>
using namespace std;

template<typename T,typename comp=less<T>>
class BSTree
{
public:
	BSTree():_root(nullptr){}
	~BSTree()
	{
		Node* node = _root;
		queue<Node*> que;
		que.push(_root);
		while (!que.empty())
		{
			Node* front = que.front();
			que.pop();
			if (front->_left != nullptr)
			{
				que.push(front->_left);
			}
			if (front->_right != nullptr)
			{
				que.push(front->_right);
			}
			delete front;
		}
	}

	//非递归插入操作
	void n_insert(const T& val)
	{
		//树为空，生成根节点
		if (_root == nullptr)
		{
			_root = new Node(val);
			return;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		//搜索合适的插入位置，记录父节点的位置
		while (cur != nullptr)
		{
			if (cur->_data == val)//不插入元素相同的
			{
				return;
			}
			else if (_comp(cur->_data, val))//小于
			{
				parent = cur;
				cur = cur->_right;
			}
			else//大于
			{
				parent = cur;
				cur = cur->_left;
			}
		}
		//把新节点插入到parent节点的孩子上
		if (_comp(parent->_data, val))
		{
			parent->_right = new Node(val);
		}
		else
		{
			parent->_left = new Node(val);
		}
	}
	//非递归删除操作
	void n_remove(const T& val)
	{
		if (_root == nullptr)
		{
			return;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur != nullptr)
		{
			if (cur->_data == val) // 找到待删除节点
			{
				break;
			}
			else if (_comp(cur->_data, val))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				parent = cur;
				cur = cur->_left;
			}
		}
		//没有找到待删除节点
		if (cur == nullptr)
		{
			return;
		}
		//情况3
		if (cur->_left != nullptr && cur->_right != nullptr)
		{
			Node* pre = cur->_left;
			while (pre->_right != nullptr)
			{
				parent = pre;
				pre = pre->_right;
			}
			cur->_data = pre->_data;
			cur = pre;//让cur指向前驱节点转化成情况1、2 
		}

		//cur指向删除节点，parent指向其父节点统一处理情况1、2
		Node* child = cur->_left;
		if (cur->_right != nullptr)
		{
			child = cur->_right;
		}
		//把待删除节点(nullptr或者不空)写入其父亲节点相应的地址域中
		if (parent->_left == cur)
		{
			parent->_left = child;
		}
		else
		{
			parent->_right = child;
		}
		delete cur;
	}
	//非递归查询
	bool n_query(const T& val)
	{
		if (_root == nullptr)
		{
			return false;
		}
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_data == val)
			{
				return true;
			}
			else if (_comp(cur->_data, val))
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
		}
		return false;
	}
	//非递归层次遍历
	void n_levelOrder()
	{
		cout << "[非递归]层次遍历：";
		queue<Node*> que;
		if (_root == nullptr)
		{
			return;
		}
		que.push(_root);
		while (!que.empty())
		{
			Node* front = que.front();
			que.pop();
			cout << front->_data << " ";
			if (front->_left != nullptr)
			{
				que.push(front->_left);
			}
			if (front->_right != nullptr)
			{
				que.push(front->_right);
			}
		}
		cout << endl;
	}
	//前序遍历非递归实现
	void n_preOrder()
	{
		cout << "[非递归]前序遍历：";
		stack<Node*> s;
		if (_root == nullptr)
		{
			return;
		}
		s.push(_root);
		while (!s.empty())
		{
			Node* top = s.top();
			cout << top->_data << " ";
			s.pop();
			if (top->_right != nullptr)
			{
				s.push(top->_right);
			}
			if (top->_left != nullptr)
			{
				s.push(top->_left);
			}
		}
		cout << endl;
	}
	//中序非递归实现
	void n_inOrder()
	{
		cout << "[非递归]中序遍历：";
		stack<Node*> s;
		Node* cur = _root;
		if (_root == nullptr)
		{
			return;
		}
		while (!s.empty()||cur!=nullptr)
		{
			if (cur != nullptr)
			{
				s.push(cur);
				cur = cur->_left;
			}
			else
			{
				Node* top = s.top();
				s.pop();
				cout << top->_data << " ";
				cur = top->_right;
			}
		}
		cout << endl;
	}
	//后序非递归实现
	void n_postOrder()
	{
		cout << "[非递归]后序遍历：";
		stack<Node*> s1;
		stack<Node*> s2;
		if (_root == nullptr)
		{
			return;
		}
		s1.push(_root);
		while (!s1.empty())
		{
			Node* top = s1.top();
			s1.pop();
			s2.push(top);
			if (top->_left != nullptr)
			{
				s1.push(top->_left);
			}
			if (top->_right != nullptr)
			{
				s1.push(top->_right);
			}
		}
		while (!s2.empty())
		{
			cout << s2.top()->_data << " ";
			s2.pop();
		}
		cout << endl;
	}
	//递归插入操作,用户接口
	void insert(const T& val)
	{
		_root=insert(_root, val);
	}
	//递归删除操作，用户接口
	void remove(const T &val)
	{
		if (_root == nullptr)
		{
			return;
		}
		_root = remove(_root, val);
	}
	//递归查询操作，用户接口
	bool query(const T& val)
	{
		return nullptr != query(_root, val);
	}
	//递归层次遍历，用户接口
	void levelOrder()const
	{
		cout << "[递归]层次遍历：";
		int treeHigh = high(_root);
		for (int i = 0; i < treeHigh; i++)
		{
			levelOrder(_root, i);
		}
		cout << endl;
	}
	//前序遍历递归实现，用户接口
	void preOrder()
	{
		cout << "[递归]前序遍历结果：";
		preOrder(_root);
		cout << endl;
	}
	//中序遍历递归实现，用户接口
	void inOrder()
	{
		cout << "[递归]中序遍历结果：";
		inOrder(_root);
		cout << endl;
	}
	//后序遍历递归实现，用户接口
	void postOrder()
	{
		cout << "[递归]后序遍历结果：";
		postOrder(_root);
		cout << endl;
	}

	//BST树区间元素查找接口
	void findValues(vector<int>& vec, int i, int j)
	{
		findValues(_root, vec, i, j);
	}
	//判断一棵树是否是二叉搜索树用户接口
	bool isBST()
	{
		Node* pre = nullptr;
		return isBST(_root, pre);
	}
	//BST树求子树问题
	bool isChildTree(const BSTree<T, comp>& child)const
	{
		if (child._root == nullptr)
			return true;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_data == child._root->_data)
				break;
			if (_comp(cur->_data, child._root->_data))
				cur=cur->_right;
			else
				cur=cur->_left;
		}
		return cur==nullptr?false:isChildTree(cur,child._root);
	}
	//二叉搜索树最近公共祖先LCA
	T getLCA(const T& val1, const T& val2)
	{
		if (_root == nullptr)
		{
			throw "no LCA";
		}
		Node* lca = getLCA(_root, val1, val2);
		if (lca == nullptr)
		{
			throw "no lca";
		}
		return lca->_data;
	}
	//求镜像翻转用户接口
	void mirrorReverse()
	{
		mirrorReverse(_root);
	}
	//判断镜像对称接口
	bool mirrorSymmetry()
	{
		if (_root == nullptr)
			return true;
		return mirrorSymmetry(_root->_left,_root->_right);
	}
	//前序中序遍历重建二叉树
	void rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		_root = _rebuild(pre, i, j, in, m, n);
	}
	//中序遍历的倒数第k个节点 非递归
	int n_getVal(int k)
	{
		int cnt = 0;
		stack<Node*> s;
		Node* p = _root;
		if (_root == nullptr)
			return -1;
		s.push(_root);
		while (!s.empty() || p != nullptr)
		{
			if (p != nullptr)
			{
				s.push(p);
				p = p->_right;
			}
			else
			{
				if(++cnt==k)
					return s.top()->_data;
				Node* top = s.top();
				s.pop();
				p = top->_left;
			}
		}
		return -1;
	}
	//中序遍历的倒数第k个节点 递归接口
	int getVal(int k)
	{
		int i = 0;
		Node* node = getVal(_root, k, i);
		if (node != nullptr)
			return node->_data;
		else
		{
			string err = "no NO.";
			err += k;
			throw err;
		}
	}
	//判断二叉树是否为平衡树用户接口
	bool isBalance()
	{
		return isBalance(_root);
	}
	//判断二叉树是否为平衡二叉树优化用户接口
	bool _isBalance()
	{
		return _isBalance(_root);
	}
private:
	struct Node
	{
		//T data=new T()是零构造：如果是编译器内置类型就是0或者0.0，对于指针就是空，对于自定义类型相当于调用默认构造对象。
		Node(T data=T())
			:_data(data),_left(nullptr),_right(nullptr){}
		T _data;
		Node* _left;
		Node* _right;
	};
	Node* _root;
	comp _comp;
private:
	// 在以node为根结点的树中插入val，并返回插入节点后的树的根结点
	Node* insert(Node* node, const T& val)
	{
		// 找到合适的位置，生成新节点，并返回节点地址
		if (node == nullptr)
		{
			return new Node(val);
		}
		//不插入相同数据
		if (node->_data == val)
		{
			return node;
		}
		else if (_comp(node->_data, val))
		{
			node->_right = insert(node->_right, val);
		}
		else
		{
			node->_left = insert(node->_left, val);
		}
		return node;
	}
	// 在以node为根结点的树中寻找值为val的节点删除,删除指定节点后，需要把删除节点的孩子节点的地址返回给对应父节点
	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		//找到待删除节点
		if (node->_data == val)
		{
			//情况3
			if (node->_left != nullptr && node->_right != nullptr)
			{
				Node* pre = node->_left;
				while (pre->_right != nullptr)
				{
					pre = pre->_right;
				}
				node->_data = pre->_data;
				node->_left = remove(node->_left, pre->_data);
			}
			//情况1、2
			Node* child = node->_left;
			if (node->_right != nullptr)
			{
				child = node->_right;
			}
			delete node;
			return child;
		}
		else if (_comp(node->_data, val))
		{
			node->_right = remove(node->_right, val);
		}
		else
		{
			node->_left = remove(node->_left, val);
		}
		return node;
	}
	//递归查询实现
	Node* query(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->_data == val)
		{
			return node;
		}
		else if (_comp(node->_data, val))
		{
			return query(node->_right, val);
		}
		else
		{
			return query(node->_left, val);
		}
		return nullptr;
	}
	//求树的高度
	int high(Node* node)const
	{
		if (node == nullptr)
		{
			return 0;
		}
		int leftHigh = high(node->_left);
		int rightHigh = high(node->_right);
		if (leftHigh >= rightHigh)
		{
			return leftHigh + 1;
		}
		return rightHigh+1;

	}
	//递归层次遍历实现,可输出以node为根节点的第i层的节点
	void levelOrder(Node* node, int i)const
	{
		// 当树的某个分支比其他的分支都要长，就可能出现在某个第i层i不为0，node为nullptr的情况
		if (node == nullptr)
		{
			return;
		}
		if (i == 0)
		{
			cout << node->_data << " ";
			return;
		}
		levelOrder(node->_left, i - 1);
		levelOrder(node->_right, i - 1);
	}
	//前序遍历实现
	void preOrder(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		cout << node->_data << " ";
		preOrder(node->_left);
		preOrder(node->_right);
	}
	//中序遍历实现
	void inOrder(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}	
		inOrder(node->_left);
		cout << node->_data << " ";
		inOrder(node->_right);
	}
	//后序遍历实现
	void postOrder(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		postOrder(node->_left);
		postOrder(node->_right);
		cout << node->_data << " ";
	}

	//BST树区间元素查找实现
	void findValues(Node* node, vector<int>& vec, int i, int j)
	{
		if (node == nullptr)
			return;
		if (node->_data > i)
		{
			findValues(node->_left, vec, i, j);
		}
		if (node->_data >= i && node->_data <= j)
		{
			vec.push_back(node->_data);
		}
		if (node->_data < j)
		{
			findValues(node->_right, vec, i, j);
		}
	}
	//判断一棵树是否是二叉搜索树实现
	bool isBST(Node* node, Node*& pre)
	{
		if (node == nullptr)
			return true;
		if (!isBST(node->_left, pre))
			return false;
		if (pre != nullptr)
		{
			if (_comp(node->_data, pre->_data))
			{
				return false;
			}
		}
		pre = node;
		return isBST(node->_right, pre);
	}
	bool isChildTree(Node* father, Node* child)const
	{
		if (father == nullptr && child == nullptr)
			return true;
		if (father == nullptr)
			return false;
		if (child == nullptr)
			return true;
		if (father->_data != child->_data)
			return false;
		return isChildTree(father->_left, child->_left) && isChildTree(father->_right, child->_right);
	}
	Node* getLCA(Node* node, const T& val1, const T& val2)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (_comp(node->_data, val1) && _comp(node->_data, val2))
		{
			return getLCA(node->_right, val1, val2);
		}
		else if (_comp(val1, node->_data) && _comp(val2, node->_data))
		{
			return getLCA(node->_left, val1, val2);
		}
		else
		{
			return node;
		}
	}
	//镜像翻转实现
	void mirrorReverse(Node* node)
	{
		if (!node)
			return;
		Node* tmp = node->_left;
		node->_left = node->_right;
		node->_right = tmp;
		mirrorReverse(node->_left);
		mirrorReverse(node->_right);
	}
	//判断镜像对称实现
	bool mirrorSymmetry(Node* l,Node* r)
	{
		if (l== nullptr && r == nullptr)
			return true;
		if (l == nullptr || r == nullptr)
			return false;
		if (l->_data != r->_data)
			return false;
		return mirrorSymmetry(l->_left, r->_right) && mirrorSymmetry(l->_right, r->_left);
	}
	//前序中序构造二叉树实现
	Node* _rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		if (i > j || m > n)
			return nullptr;
		Node* node = new Node(pre[i]);
		for (int k = m; k <= n; k++)
		{
			if (pre[i] == in[k])
			{
				node->left = _rebuild(pre, i + 1, i + (k - m), in, m, k - 1);
				node->right = _rebuild(pre, i + (k - m) + 1, j, in, k + 1, n);
			}
		}
		return node;
	}
	//中序遍历倒数第k个节点 递归实现
	Node* getVal(Node* node, int k, int& i)
	{
		if (node == nullptr)
			return nullptr;
		Node* right = getVal(node->_right, k, i);
		if (right != nullptr)
			return right;
		if (++i == k)
			return node;
		return getVal(node->_left, k, i);
	}
	//判断二叉树是否为平衡树实现
	bool isBalance(Node* node)
	{
		if (node == nullptr)
			return true;
		if (!isBalance(node->_left))
			return false;
		if (!isBalance(node->_right))
			return false;
		int left = high(node->_left);
		int right = high(node->_right);
		return abs(left - right) <= 1;
	}
	//判断二叉树是否为平衡二叉树优化实现
	int _isBalance(Node* root) {
		if (root == NULL) {
			return 0;
		}
		int leftHeight = _isBalance(root->_left);
		int rightHeight = _isBalance(root->_right);
		if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
			return -1;
		}
		else {
			return max(leftHeight, rightHeight) + 1;
		}
	}
};

#if 0
int main()
{
	int arr[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTree<int> bst;
	for (int v : arr)
	{
		bst.n_insert(v);
	}
	bst.insert(12);
	cout << bst.n_query(12) << endl;
	bst.remove(12);
	cout << bst.query(12) << endl;
	bst.n_levelOrder();
	bst.levelOrder();
	bst.preOrder();
	bst.n_preOrder();
	bst.inOrder();
	bst.n_inOrder();
	bst.postOrder();
	bst.n_postOrder();

	vector<int> vec;
	bst.findValues(vec, 50, 70);
	for (int v : vec)
		cout << v << " ";
	cout << endl;
	cout << "判断二叉搜索树:"<<bst.isBST() << endl;
	cout << "是否是其子树:"<<bst.isChildTree(bst) << endl;
	cout << "最近公共祖先:"<<bst.getLCA(64, 78) << endl;
	//bst.mirrorReverse();
	cout << "是否镜像对称:" << bst.mirrorSymmetry() << endl;
	cout << "中序遍历的倒数第k个节点:" << bst.getVal(3) << endl;
	cout << "是否是平衡二叉树:" << bst._isBalance() << endl;
	return 0;
}
#endif
