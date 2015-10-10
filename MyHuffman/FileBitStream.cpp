//
//  FileBitStream.cpp
//  MyHuffman
//
//  Created by mac on 15/10/10.
//  Copyright © 2015年 mac. All rights reserved.
//

#include "FileBitStream.h"
GFileStream::GFileStream(void){
    fout=0;
    buffer=0;
    usedBuffer=0;
    writedLen=0;
}

GFileStream::~GFileStream(){
    
}

bool GFileStream::openOutStram(const char *outFileName){
    fout=fopen(outFileName, "ab");
    if (fout) {
        return true;
    }
    return false;
}

int GFileStream::closeOutStream(void){
    if (usedBuffer>0) {
        fputc(buffer, fout);
        writedLen++;
    }
    fclose(fout);
    return writedLen;
}

bool GFileStream::pushABit(bool theBit){
    usedBuffer++;
    buffer=buffer|(theBit<<(8-usedBuffer));
    if (usedBuffer==8) {
        printf("%c",buffer);
        fputc(buffer, fout);
        usedBuffer=0;
        buffer=0;
        writedLen++;
    }
    return true;
}

void GFileStream::pushBits(HBit &bits){
    for (int i=0; i<bits.getLength(); i++) {
        pushABit(bits.getABit(i));
    }
}

bool GFileStream::openInStream(const char *inFileName){
    usedBuffer=8;
    fin=fopen(inFileName, "rb");
    if (fin) {
        return true;
    }
    return false;
}

bool GFileStream::getCurrentBit(void){
    if (usedBuffer==8) {
        buffer=fgetc(fin);
        usedBuffer=0;
    }
    usedBuffer++;
    return (buffer&(unsigned char)(1<<(8-usedBuffer)))!=0;
}

void GFileStream::closeInStream(void){
    fclose(fin);
}