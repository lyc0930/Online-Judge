#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <cstring>
#include <stack>
#include <list>
#include <vector>

using namespace std;

int left[100],right[100],size[100],key[100];
static int node_num=0; //node numbers
void LeftRotate(int &t)
{
	int k=right[t];
	right[t]=left[k];
	left[k]=t;
	size[k]=size[t];
	size[t]=size[left[t]]+size[right[t]]+1;
	t=k;
}
void RightRotate(int &t)
{
	int k=left[t];
	left[t]=right[k];
	right[k]=t;
	size[k]=size[t];
	size[t]=size[left[t]]+size[right[t]]+1;
	t=k;
}
void Maintain(int &t,bool flag)
{
	if(!flag) {
		if(size[left[left[t]]]>size[right[t]]) {
			RightRotate(t);
		}
		else if(size[left[right[t]]]>size[right[t]]) {
			LeftRotate(right[t]);
			RightRotate(t);
		}
	}
	else {
		if(size[right[right[t]]]>size[left[t]]) {
			LeftRotate(t);
		}
		else if(size[right[left[t]]]>size[left[t]]) {
			RightRotate(left[t]);
			LeftRotate(t);
		}
	}
	Maintain(left[t],false);
	Maintain(right[t],true);
	Maintain(t,false);
	Maintain(t,true);
}
int NewNode(int value)
{
	int num=++node_num;
	key[num]=value;
	left[num]=0;
	right[num]=0;
	size[num]=1;
	return num;
}
void Insert(int &t,int value)
{
	if(t==0) {
		t=NewNode(value);
		return;
	}
	else {
		size[t]++;
		if(value<key[t]) {
			Insert(left[t],value);
		}
		else {
			Insert(right[t],value);
		}
		Maintain(t,value>=key[t])
	}
}
int Delete(int &t,int value)
{
	int res;
	size[t]--;
	if(key[t]==value||(value<key[t]&&left[t]==0)||(value>key[t]&&right[t]==0)) {
		res=key[t];
		//有右左两个孩子
		//从左子树的最大值选出来覆盖
		//也就是直接前驱的值覆盖原来的值
		if(left[t]&&right[t]) {
			key[t]=Delete(left[t],value+1); //直接前驱
			//key[t]=Delete(right[t],value-1); //直接后继
		}
		//有其中一个左孩子或者右孩子
		//用其孩子覆盖父节点
		else {
			t=left[t]+right[t];
		}
	}
	else {
		if(value>key[t]) Delete(right[t],value);
		else  Delete(left[t],value);
	}
	return res;
}
