#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
using namespace std;
int main(int argc, char const *argv[]){

    char Buffer[512]={0};
    int InputLength = atoi( getenv("INPUT_LENGTH") );
    InputLength = min<int>( InputLength, sizeof(Buffer)-1 ); 
    fread( Buffer, InputLength, 1, stdin );
    for(int i =0; i < sizeof(Buffer); ++i){
        cout << Buffer[i]<<"\n";
    }
}