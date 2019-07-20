/**
    文件名：二叉排序树
*/

#include <stdio.h>
#include <stdlib.h>

typedef int Status;

//二叉排序树的结点结构//
typedef struct BiTNode{//这里开头要写BiTree是为了让左右孩子指针为单层指针形式
	int data;
	struct BiTNode *lchild, *rchild;
}*BiTree;

//递归查找二叉排序树中是否存在key值//
//如果存在则让p指向该节点，如果不存在p指向最后查找的结点//
//f初始值为空，之后指向正在查找的结点的双亲结点//
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) {
	if(T!=NULL)
		printf("该值为%d\n", T->data);
	if (T == NULL) {
		//没有找到
		*p = f;
		printf("没有找到%d\n",key);
		return false;
	}
	else if (T->data == key) {
		//找到了
		*p = T;
		printf("值%d找到了\n", key);
		return true;
	}
	else if (key < T->data) {
		//小的都在左边
		return SearchBST(T->lchild, key, T, p);
	}
	else if (key > T->data) {
		//大的都在右边
		return SearchBST(T->rchild, key, T, p);
	}
}

//二叉排序树的插入操作//
//先查找key是否在排序树中，如果不在的话p为指向的最后一个查找的结点//
//判断如果key比p大的话插入p的右孩子那，如果比p小的话插入左孩子那//
Status InsertBST(BiTree *T, int key) {
	BiTree p, s;
	if (SearchBST(*T, key, NULL, &p) == 0) {
		//这表示没有找到，p传地址，引用指针，头结点的双亲为NULL
		//printf("p指向的值为%d\n", p->data);
		s = (BiTNode *)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (p == NULL) {
			//如果是空树的话
			*T = s;//新结点就是根节点
			printf("值%d插入成功,插入在根节点上\n", key);
			return true;
		}
		else if (key < p->data) {
			//如果小的话就插入左孩子那
			p->lchild = s;
			printf("值%d插入成功,插入在左子树上\n", key);
			return true;
		}
		else if (key > p->data) {
			//如果大的话就插入右孩子那
			p->rchild = s;
			printf("值%d插入成功,插入在右子树上\n", key);
			return true;
		}
		else
			return false;
	}
}

//二叉排序树的删除操作//
//删除操作有分三种情况//
//只有左子树，只要把左子树替换上去就行了//
//只有右子树，只要把右子树替换上去就行了//
//既有左子树，又有右子树，那么需要找到该结点的直接前驱（左子树中最右边的）,或者直接后继（右子树中最左边的）//
Status Delete(BiTree *p) {
	BiTree q, s;
	if ((*p)->rchild == NULL) {
		//如果右子树为空，只要重接左子树
		s = (*p)->lchild;
		(*p)->data = s->data;
		(*p)->rchild = s->rchild;
		(*p)->lchild = s->lchild;
		q = s;
		free(q);
		printf("该值右子树空\n");
	}
	else if ((*p)->lchild == NULL) {
		//如果左子树为空，只要重接右子树
		s = (*p)->rchild;
		(*p)->data = s->data;
		(*p)->rchild = s->rchild;
		(*p)->lchild = s->lchild;
		q = s;
		free(q);
		printf("该值左子树空\n");
	}
	else if((*p)->lchild != NULL && (*p)->rchild != NULL){
		//左右子树都不空
		q = (*p);
		s = (*p)->lchild;
		while (s->rchild) {
			//取的是p的直接前驱
			q = s;
			s = s->rchild;
		}
		//此时q指向直接前驱的前驱，s指向直接前驱
		(*p)->data = s->data;//直接赋值上去
		if (q != (*p)) {
			//s不是p的直接左子树
			//重接右子树
			q->rchild = s->lchild;//重接在原来的直接前驱的位置
		}
		else {
			//s是p的直接左子树
			//重接左子树
			q->lchild = s->lchild;//直接就是NULL
		}
		free(s);
		printf("该值左右子树都不空\n");
	}
	else if ((*p)->lchild == NULL && (*p)->rchild == NULL) {
		free(p);
	}
	printf("删除完成\n");
	return true;
}

Status DeleteBST(BiTree T, int key) {
	if (T == NULL) {
		printf("要删除的元素不存在\n");
		return false;
	}
	else if (T->data == key) {
		//找到了，直接删除就行
		BiTree *t=&T;
		Delete(t);
	}
	else if (key < T->data) {
		//可能在T的左子树
		DeleteBST(T->lchild, key);
	}
	else if (key > T->data) {
		//可能在T的右子树
		DeleteBST(T->rchild, key);
	}
}



int main()
{
	BiTree T = NULL;
	BiTree p = (BiTNode *)malloc(sizeof(BiTNode));
	for (int i = 0; i < 10; i++) {
		InsertBST(&T, i);
		printf("T的值为%d\n", T->data);
	}
	BiTree t = T;
	system("pause");
	system("cls");
	while (t->rchild != NULL) {
		printf("%d->", t->data);
		t = t->rchild;
	}
	printf("%d\n", t->data);
	SearchBST(T, 8, NULL, &p);
	DeleteBST(T, 0);
	SearchBST(T, 7, NULL, &p);
    return 0;
}
