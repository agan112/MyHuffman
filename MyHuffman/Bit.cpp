//
//  Bit.cpp
//  MyHuffman
//
//  Created by mac on 15/10/10.
//  Copyright © 2015年 mac. All rights reserved.
//

#include "Bit.h"
#include <strings.h>
#include <stdlib.h>

HBit::HBit(void):len(0),lpBuffer(0),bufferLen(0)
{
}
HBit::HBit(HBit&bit)
{
    len=bit.len;
    bufferLen=bit.bufferLen;
    lpBuffer=(unsigned char*)malloc(bufferLen);
    memcpy(lpBuffer,bit.lpBuffer,bufferLen);
}

HBit::~HBit(void){
    clear();
}

void HBit::appendABit(bool bit){
    if (len%8==0) {
        bufferLen++;
        if (lpBuffer) {
            lpBuffer=(unsigned char *)realloc(lpBuffer, bufferLen);
            memset(lpBuffer+bufferLen-1, 0, 1);
        }else{
            lpBuffer=(unsigned char*)malloc(bufferLen);
            memset(lpBuffer, 0, bufferLen);
        }
    }
    len++;
    setABit(len-1, bit);
    
}

bool HBit::getABit(int pos){
    if (pos<len) {
        return (lpBuffer[(pos)/8]&((unsigned char)(1<<(7-pos%8))))!=0;
    }
    return false;
}

void HBit::setABit(int pos, bool bit){
    lpBuffer[(pos)/8]|=((unsigned char)(bit<<(7-pos%8)));
}


