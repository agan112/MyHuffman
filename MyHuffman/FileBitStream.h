//
//  FileBitStream.hpp
//  MyHuffman
//
//  Created by mac on 15/10/10.
//  Copyright © 2015年 mac. All rights reserved.
//

#ifndef FileBitStream_hpp
#define FileBitStream_hpp

#include <stdio.h>
#include "Bit.h"
class GFileStream{
public:
    GFileStream(void);
    virtual ~GFileStream(void);
    bool openOutStram(const char* outFileName);
    int closeOutStream(void);
private:
    FILE* fout;
    FILE* fin;
    char buffer;
    int usedBuffer;
    int writedLen;
public:
    void skip(int size){
        fseek(fin,size,SEEK_SET);
    }
    bool pushABit(bool theBit);
    void pushBits(HBit &bits);
    bool openInStream(const char* inFileName);
    bool getCurrentBit(void);
    void closeInStream(void);
    
};


#endif /* FileBitStream_hpp */
