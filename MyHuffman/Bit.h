//
//  Bit.h
//  MyHuffman
//
//  Created by mac on 15/10/10.
//  Copyright © 2015年 mac. All rights reserved.
//

#ifndef Bit_h
#define Bit_h

#include <stdlib.h>
class HBit
{
    int len;
    unsigned char* lpBuffer;
    int bufferLen;
public:
    HBit(void);
    HBit(HBit& bit);
    void clear(){
        if (lpBuffer) {
            free(lpBuffer);
        }
        lpBuffer=0;
        bufferLen=0;
        len=0;
    }
    bool isEmpty(){
        return len==0;
    }
    int getLength(){
        return len;
    }
    int getBufferLength(){
        return bufferLen;
    }
    bool getABit(int pos);
    void setABit(int pos,bool bit);
    virtual ~HBit(void);
    void appendABit(bool bit);
    
};

#endif /* Bit_h */
