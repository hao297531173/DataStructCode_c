/*
    文件名：avl树
*/
#ifndef _AVLTree_H_
#define _AVLTree_H_
/* 
	这个头文件是AVL树的c++实现
	AVL树的旋转情况有4中，但是可以最终归结为左旋和右旋两种
	算法应该都是没问题的，就是指针传出去后回来还是没有变
	所以要使用指向指针的指针
*/
#include <iostream>
using namespace std;
//代表结点的高度
typedef enum {
	LH = 1,
	EH = 0,
	RH = -1
}bh_t;
 
 
typedef int Elemtype;
class AVLTree {
	struct AVLNode {
		Elemtype data;
		int bf;     //高度因子
		struct AVLNode *lchild, *rchild;
	}*ANode;
	AVLNode *head;           //头结点
	bool first;              //表示头结点有没有被赋值，如果是1表示已经被赋值了
public:
	AVLTree();
	~AVLTree();
private:
	void destroy(AVLNode *);          //销毁这棵AVL树
public:
	void traverse();                  //调用遍历函数
private:
	void preOrder(AVLNode *);         //先序遍历这棵AVL树
	void R_Rotate(AVLNode **);         //右旋原子操作
	void L_Rotate(AVLNode **);         //左旋原子操作
	void LeftBalance(AVLNode **);
	void RightBalance(AVLNode **);     //干活的左右平衡操作
private:
	int insert(AVLNode **, Elemtype, bool *);  //插入操作
public:
	void insertAVL();
	void search();                   //查询某个结点
	int get_head();
};
//构造函数，要构造出头结点
AVLTree::AVLTree() {
	head = new AVLNode();
	head->bf = EH;
	head->lchild = head->rchild = NULL;
	head->data = NULL;
	first = 0;
}
AVLTree::~AVLTree() {
	destroy(head);
}
void AVLTree::destroy(AVLNode *root) {
	if (root == NULL)
		return;
	destroy(root->lchild);
	destroy(root->rchild);
	delete root;
}
void AVLTree::preOrder(AVLNode *p) {
	if (p == NULL)
		return;
	std::cout << p->data << " ";
	preOrder(p->lchild);
	preOrder(p->rchild);
}
void AVLTree::traverse() {
	preOrder(head);
}
/*
	右旋原子操作要将根节点左孩子的右子树给根节点，
	然后根节点左孩子变成新的根节点
*/
void AVLTree::R_Rotate(AVLNode **root) {
	AVLNode *lc =(*root)->lchild;   //根节点的左子树
	(*root)->lchild = lc->rchild;
	lc->rchild = *root;
	*root = lc;
}
/*
	左旋原子操作同上，先将根节点的右孩子的左子树给根节点的右孩子，
	然后根节点右孩子变成新的根节点
*/
void AVLTree::L_Rotate(AVLNode **root) {
	AVLNode *rc = (*root)->rchild;
	(*root)->rchild = rc->lchild;
	rc->rchild = *root;
	*root = rc;                      //这里如果不改变根节点指针的话就不能及时更新根节点
}
/*
	右平衡就是左子树高，有两种情况，一种是在最左边添加结点，
	这种情况只要一次右旋就行了LL，
	另一种情况就是在左孩子的右子树添加，这种情况需要时LR旋转，
	也就是先左子树左旋转，再右子树右旋转
	左平衡和右平衡类似只是方向不同
*/
void AVLTree::LeftBalance(AVLNode **t) {
	AVLNode *lc = (*t)->lchild;   //左子树
	AVLNode *rc = lc->rchild;  //左子树的右子树
	switch (lc->bf) {
	//左高
	case LH:   //LL
		lc->bf = (*t)->bf = EH;
		R_Rotate(t);
		/*(*t)->lchild = rc;
		lc->rchild = *t;
		*t = lc;
		//preOrder(t);*/
		break;
	case RH:   //LR
		switch (rc->bf) {
		case LH:
			lc->bf = EH;
			(*t)->bf = RH;
			break;
		case EH:
			//我觉得不会出现这种情况
			(*t)->bf = lc->bf = EH;
			break;
		case RH:
			(*t)->bf = EH;
			lc->bf = LH;
			break;
		}
		rc->bf = EH;
		//L_Rotate(&lc);           //先让左子树左旋
		AVLNode *lrlc = rc->lchild;
		lc->rchild = lrlc;
		rc->lchild = lc;
		lc = rc;
		//R_Rotate(t);            //再让整棵树右旋
		(*t)->lchild = lc->rchild;
		lc->rchild = *t;
		*t = lc;
		//preOrder(t);
		break;
	}
}
void AVLTree::RightBalance(AVLNode **t) {
	AVLNode *rc = (*t)->rchild;     //右子树
	AVLNode *lc = rc->lchild;    //右子树上的左子树
	switch (rc->bf) {
	case RH:   //RR
		(*t)->bf = rc->bf = EH;
		//L_Rotate(t);
		(*t)->rchild = lc;
		rc->lchild = *t;
		*t = rc;
		//preOrder(t);
		break;
	case LH:   //RL
		switch (lc->bf) {
		case LH:
			(*t)->bf = LH;
			rc->bf = EH;
			break;
		case EH:
			(*t)->bf = rc->bf = EH;
			break;
		case RH:
			(*t)->bf = LH;
			rc->bf = EH;
			break;
		}
		lc->bf = EH;
		//R_Rotate(&rc);
		AVLNode *rllc = lc->rchild;
		rc->lchild = rllc;
		lc->rchild = rc;
		rc = lc;
		//L_Rotate(t);
		(*t)->rchild = rc->lchild;
		rc->lchild = *t;
		*t = rc;
		//preOrder(t);
		break;
	}
}
//插入操作
int AVLTree::insert(AVLNode **t, Elemtype e, bool *taller) {
	if (t == NULL)		//第二层指针为空
		return 0;
	if (*t == NULL) {   //第一层指针为空
		*t = new AVLNode();
		(*t)->data = e;
		(*t)->lchild = (*t)->rchild = NULL;
		(*t)->bf = EH;
		*taller = 1;
	}
	else{
		if (e == (*t)->data) {
			//存在了就不进行插入了，所有的递归都会退出
			*taller = 0;
			return 0;       //这里是等于0的退出点，也就是不进行其他操作
		}
		else if (e < (*t)->data) {
			//如果是比该结点小的话就插入左边
			if (0 == insert(&((*t)->lchild), e, taller))
				return 0;
			/*if ((*t)->lchild == NULL) {
				(*t)->lchild = new AVLNode();
				(*t)->lchild->data = e;
				(*t)->lchild->lchild = (*t)->lchild->rchild = NULL;
				*taller = 1;
			}*/
			//这里是从递归出来之后各个结点进行判断
			if (*taller) {
				switch ((*t)->bf) {
				case LH:
					LeftBalance(t);
					*taller = 0;    //如果自己这边都是平衡的话那么上层也是平衡的
					break;
				case EH:
					(*t)->bf = LH;
					*taller = 1;    //表示上层还要继续判断有没有变高
					break;
				case RH:
					(*t)->bf = EH;
					*taller = 0;
					break;
				}
			}
		}
		else if (e > (*t)->data) {
			//如果比该结点的值大那么应该插入在右边
			if (0 == insert(&((*t)->rchild), e, taller))
				return 0;
			/*if ((*t)->rchild == NULL) {
				(*t)->rchild = new AVLNode();
				(*t)->rchild->data = e;
				(*t)->rchild->lchild = (*t)->rchild->rchild = NULL;
				*taller = 1;
			}*/
			if (*taller) {
				switch ((*t)->bf) {
				case LH:
					(*t)->bf = EH;
					*taller = 0;
					break;
				case EH:
					(*t)->bf = RH;
					*taller = 1;
					break;
				case RH:
					RightBalance(t);   //这时候差值的绝对值已经等于2了
					*taller = 0;       //四种旋转结束后根节点的都平衡了
					break;
				}
			}
		}
	}
	return 1;
}
void AVLTree::insertAVL() {
	int a;
	std::cout << "请输入想要插入AVL的数：";
	std::cin >> a;
	if (first == 0) {
		head->data = a;
		first = 1;
		std::cout << "插入成功" << std::endl;
		return;
	}
	bool b = 0;
	bool *taller=&b;
	int c;
	c = insert(&head, a, taller);
	if (c == 1)
		std::cout << "插入成功" << std::endl;
	else
		std::cout << "AVL树中已经存在这个数了，插入失败" << std::endl;
}
void AVLTree::search() {
	int a;
	std::cout << "请输入想要查询的数字：";
	std::cin >> a;
	AVLNode *p = head;
	while (p != NULL) {
		if (p->data == a) {
			std::cout << "存在这个数"<<std::endl;
			return;
		}
		else if (p->data > a)
			p = p->lchild;
		else
			p = p->rchild;
	}
	std::cout << "在AVL树中没有找到这个数" << std::endl;
}
int AVLTree::get_head() {
	return head->data;
}
#endif