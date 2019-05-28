//
// Created by Julia on 2019-05-12.
//

#include "Shader.h"


char* Shader::readFile(const std::string File) {
    int filesize;
    FILE *plik;
    char* result;

    plik=fopen(File.c_str(),"rb");
    fseek(plik,0,SEEK_END);
    filesize=ftell(plik);
    fseek(plik,0,SEEK_SET);
    result=new char[filesize+1];
    fread(result,1,filesize,plik);
    result[filesize]=0;
    fclose(plik);

    return result;
}