//
//  main.cpp
//  MyHuffman
//
//  Created by gsr on 15/10/10.
//  Copyright © 2015年 mac. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Huffman.h"
#include "FileBitStream.h"

#define CharSize 256
#define FirstChar 'H'
#define SecondChar 'F'

using namespace std;

typedef struct {
    char id[2];         //the sign of the File
    int len;            //the numbers of chars
    int map[CharSize];  //the rate of each char
}FileHeader;

void compresss(const char* inFileName,const char* outFileName){
    int ch=0,fSize=0;
    int map[CharSize]={0};
    FILE *fin=fopen(inFileName, "rb");
    if (!fin) {
        return;
    }
    while ((ch=fgetc(fin))!=-1) {
        map[(unsigned char)ch]++;
    }
    fclose(fin);
    
    FileHeader header;
    memset(&header, 0, sizeof(header));
    header.id[0]=FirstChar;
    header.id[1]=SecondChar;
    memcpy(header.map, map, CharSize*sizeof(int));
    
    GHuffman huffman;
    huffman.createByMap(map);
    
    FILE *fout=fopen(outFileName, "wb");
    if (!fout) {
        return;
    }
    fin=fopen(inFileName, "rb");
    fwrite(&header, sizeof(header), 1, fout);
    fclose(fout);
    
    GFileStream fileStream;
    if (fileStream.openOutStram(outFileName)) {
        while ((ch=fgetc(fin))!=-1) {
            fSize++;
            fileStream.pushBits(huffman.code[(unsigned char)ch]);
        }
        fileStream.closeOutStream();
    }
    fout=fopen(outFileName, "rb+");
    header.len=fSize;
    fwrite(&header, sizeof(header), 1, fout);
    fclose(fout);
    fclose(fin);
    
}

void unCompress(const char* inFileName,const char* outFileName){
    FILE* fin=fopen(inFileName, "rb");
    if (!fin) {
        return;
    }
    FileHeader header;
    GHuffman huffman;
    GFileStream fileStream;
    fread(&header, sizeof(header), 1, fin);
    fclose(fin);
    int decodedSize=0;
    int ch=0;
    if (header.id[0]==FirstChar&&header.id[1]==SecondChar) {
        FILE* fout=fopen(outFileName, "wb");
        huffman.createByMap(header.map);
        if (fileStream.openInStream(inFileName)) {
            fileStream.skip(sizeof(header));
            while (decodedSize!=header.len) {
                while ((ch=huffman.locateByABit(fileStream.getCurrentBit()))==-1);
                fputc(ch, fout);
                decodedSize++;
            }
        }
        fileStream.closeInStream();
        fclose(fout);
    }else{
        cout<<"\""<<outFileName<<"\" this file is not compressed by huffman Algorithm. "<<endl;
    }
}

int main(int argc, const char * argv[]) {
    char inFileName[1024]={0};
    char outFileName[1024]={0};
    int choose=0;
    do{
        cout<<"please input your choice,1 (compress) or 2(uncompress)?"<<endl;
        cin>>choose;
        
    }while (choose!=1&&choose!=2);
    cout<<"please set your inputFilePath:"<<endl;
    cin>>inFileName;
    cout<<"please set your outputFilePath:"<<endl;
    cin>>outFileName;
    
    if (choose==1) {
        compresss(inFileName,outFileName);
    }else if (choose==2){
        unCompress(inFileName,outFileName);
    }
    cout<<"done!"<<endl;
    system("pause");
    
    return 0;
}
