#pragma once
#include <cstdio>
#include <stdlib.h>
#include<iostream>
class FileDescriptor {

    private:
    FILE* placeholder;
    char* buffer;
    void scan() {
        char c;
        int size = 2, index = 0;
        buffer = (char*)malloc(sizeof(char) * 2);
        while((c = fgetc(placeholder)) != EOF) {
            if(size - 1 <= index) {
                size = size * 2;
                buffer = (char*)realloc(buffer,sizeof(char)*size);
            }
            buffer[index++] = c;
        }
        fclose(placeholder);
        buffer[index] = '\0';
    }
    public:
    FileDescriptor() {
        placeholder = nullptr;
    }
    FileDescriptor(char* FM) {
        placeholder = fopen(FM,"r");
        if(placeholder)
            scan();
        else {
            std::cerr << "no such a file with that name " << FM << std::endl;
            exit(2);
        }
    }
    char* getBuffer() {
        return buffer;
    }

};