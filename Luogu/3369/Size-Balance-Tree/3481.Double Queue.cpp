#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NUM 2000008

struct SBT
{
	int left,right,siz,key,id;
	void init() {
		left=right=id=key=0;
		siz=1;
	}
}T[MAX_NUM];
int root=0;  //root number
int node_num=0; //node numbers
void LeftRotate(int &t)
{
	int k=T[t].right;
	T[t].right=T[k].left;
	T[k].left=t;
	T[k].siz=T[t].siz;
	T[t].siz=T[T[t].left].siz+T[T[t].right].siz+1;
	t=k;
}
void RightRotate(int &t)
{
	int k=T[t].left;
	T[t].left=T[k].right;
	T[k].right=t;
	T[k].siz=T[t].siz;
	T[t].siz=T[T[t].left].siz+T[T[t].right].siz+1;
	t=k;
}
void Maintain(int &t,bool flag)
{
	if(!flag) {
		if(T[T[T[t].left].left].siz>T[T[t].right].siz) {
			RightRotate(t);
		}
		else if(T[T[T[t].left].right].siz>T[T[t].right].siz) {
			LeftRotate(T[t].left);
			RightRotate(t);
		}
		else {
			return ;
		}
	}
	else {
		if(T[T[T[t].right].right].siz>T[T[t].left].siz) {
			LeftRotate(t);
		}
		else if(T[T[T[t].right].left].siz>T[T[t].left].siz) {
			RightRotate(T[t].right);
			LeftRotate(t);
		}
		else {
			return;
		}
	}
	Maintain(T[t].left,false);
	Maintain(T[t].right,true);
	Maintain(t,false);
	Maintain(t,true);
}
void Insert(int &t,int ident,int value)
{
	if(t==0) {
		t=++node_num;
		T[t].init();
		T[t].key=value;
		T[t].id=ident;
		return;
	}
	else {
		T[t].siz++;
		if(value<T[t].key) {
			Insert(T[t].left,ident,value);
		}
		else {
			Insert(T[t].right,ident,value);
		}
		Maintain(t,value>=T[t].key);
	}
}
int Delete(int &t,int value)
{
	int res;
	T[t].siz--;
	if(T[t].key==value||(value<T[t].key&&T[t].left==0)||(value>T[t].key&&T[t].right==0)) {
		res=T[t].key;
		//有右左两个孩子
		//从左子树的最大值选出来覆盖
		//也就是直接前驱的值覆盖原来的值
		if(T[t].left&&T[t].right) {
			T[t].key=Delete(T[t].left,value+1); //直接前驱
			//key[t]=Delete(T[t].right,value-1); //直接后继
		}
		//有其中一个左孩子或者右孩子
		//用其孩子覆盖父节点
		else {
			t=T[t].left+T[t].right;
		}
	}
	else {
		if(value>T[t].key) res=Delete(T[t].right,value);
		else  res=Delete(T[t].left,value);
	}
	return res;
}
int Get_Max()
{
	int x;
	for(x=root;T[x].right;x=T[x].right) ;
	return x;
}
int Get_Min()
{
	int x;
	for(x=root;T[x].left;x=T[x].left);
	return x;
}
int main()
{
	int code;
	while(scanf("%d",&code),code) {
		if(code==1) {
			int ident,value;
			scanf("%d%d",&ident,&value);
			Insert(root,ident,value);
		}
		else if(code==2) {
			int cc=Get_Max();
			printf("%d\n",T[cc].id);
			Delete(root,T[cc].key);
		}
		else {
			int cc=Get_Min();
			printf("%d\n",T[cc].id);
			Delete(root,T[cc].key);
		}
	}
    return 0;
}
