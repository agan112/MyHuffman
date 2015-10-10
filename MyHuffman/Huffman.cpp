//
//  Huffman.cpp
//  MyHuffman
//
//  Created by mac on 15/10/10.
//  Copyright © 2015年 mac. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Huffman.h"
using namespace std;

GHuffman::GHuffman(void):root(0),curNode(0)
{
    
}

GHuffman::~GHuffman(void)
{
    destroyTree();
}

int GHuffman::destroyTreeR(LPNODE root){
    if (root) {
        destroyTreeR(root->l);
        destroyTreeR(root->r);
        delete root;
    }
    return 0;
}

void GHuffman::createByMap(int map[]){
    LPNODE pNode[256]={0};
    for (int i=0; i<256; i++) {
        pNode[i]=new Node(map[i],i,0,0);
    }
    qsort(pNode, 0, 255);
    
    int len=0;
    for (; len<256&&pNode[len]->value!=0; len++) ;
    if (len==0) {
        return;
    }
    while (len>1) {
        LPNODE ptNode=new Node(pNode[len-1]->value+pNode[len-2]->value,0,pNode[len-2],pNode[len-1]);
        pNode[len-2]=ptNode;
        len--;
        qsort(pNode, 0, len-1);
    }
    root=pNode[0];
    if (root->r==NULL&&root->l==NULL) {
        code[root->data].appendABit(0);
        return;
    }
    memset(stageCode, 0, 256);
    generateCode(root, 0);
}

void GHuffman::generateCode(LPNODE root, int pos){
    if (root!=NULL) {
        if (root->l) {
            stageCode[pos]=0;
            generateCode(root->l, pos+1);
        }else{
            stateCodetoCode(root->data, pos);
            return;
        }
        if (root->r) {
            stageCode[pos]=1;
            generateCode(root->r, pos+1);
        }else{
            stateCodetoCode(root->data, pos);
            return;
        }
    }
}

void GHuffman::destroyTree(){
    destroyTreeR(root);
}

void GHuffman::stateCodetoCode(unsigned char data, int len){
    for (int i=0; i<len; i++) {
        code[data].appendABit(stageCode[i]);
    }
}

void GHuffman::qsort(LPNODE *ppNodes, int start, int end,bool isDesc){
    if ((end-start)<=0) return;
    int i=start;
    int j=0;
    for (j=start; j<end; j++) {
        if (isDesc) {
            if (ppNodes[j]->value>ppNodes[end]->value) {
                swap(ppNodes[j], ppNodes[i]);
                i++;
            }
        }else{
            if (ppNodes[j]->value<ppNodes[end]->value) {
                swap(ppNodes[j], ppNodes[i]);
                i++;
            }
        }
    }
    if (i!=end) {
        swap(ppNodes[i], ppNodes[end]);
    }
    GHuffman::qsort(ppNodes, start, i-1,isDesc);
    GHuffman::qsort(ppNodes, i+1,end,isDesc);
}