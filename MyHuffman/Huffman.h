//
//  Huffman.h
//  MyHuffman
//
//  Created by mac on 15/10/10.
//  Copyright © 2015年 mac. All rights reserved.
//

#ifndef Huffman_h
#define Huffman_h

#include "Bit.h"
class GHuffman{
    bool stageCode[255];
    typedef struct _Node{
        _Node(int value,char data,_Node*l,_Node*r){
            this->value=value;
            this->data=data;
            this->l=l;
            this->r=r;
        }
        int value;
        unsigned char data;
        _Node *l;
        _Node *r;
    }Node,*LPNODE;
public:
    GHuffman(void);
    virtual ~GHuffman(void);
    void createByMap(int map[]);
    void qsort(LPNODE*ppNodes,int start,int end,bool isDesc=1);
    LPNODE root;
    HBit code[256];
    void destroyTree(void);
    int locateByABit(bool bit){
        if (root==NULL)return -1;
        if (curNode==0) curNode=root;
        if (bit==0) {
            curNode=curNode->l;
        }else{
            curNode=curNode->r;
        }
        
        if (curNode->r==NULL&&curNode->l==NULL) {
            unsigned char ch=curNode->data;
            curNode=NULL;
            return ch;
        }else{
            return -1;
        }
    }
private:
    int destroyTreeR(LPNODE root);
    void generateCode(LPNODE root,int pos);
    void stateCodetoCode(unsigned char data,int len);
    LPNODE curNode;
public:
    unsigned char getDataByCode(HBit &code);
};


#endif /* Huffman_h */
