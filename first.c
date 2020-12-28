#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int M;
int H;

struct L** cache;

int memory_write;
int memory_read;


unsigned long int t;

typedef struct L{

    unsigned long int Tag;
    int v;
    unsigned long int dur;
} L;

L** makeCache(int associativity,int setting){
    int x=0;
    int y=0;
    cache=(L**)malloc(setting*sizeof(L*));
    for(x=0; x<setting; x++){

        cache[x]=(L*)malloc((associativity)*sizeof(L));
        
    }
    for(x=0; x<setting; x++){
        for(y=0; y<associativity; y++){

            cache[x][y].v=0;
           
        }
        


       
    }

    return cache;


}

void reading(unsigned long long tag, unsigned long long set, int associativity){

int x=0;
int y=0;
int low;

while(x<associativity){

    if(cache[set][x].v==0){

        M++;
        memory_read++;
        t++;
        cache[set][x].v=1;
        cache[set][x].Tag=tag;
        cache[set][x].dur=t;
        return;
    }

        
        else{ 

            if(cache[set][x].Tag==tag){
                H++;
                return;
            }

            else if(x==(associativity-1)){
                M++;
                memory_read++;
                low=0;
                while(y<associativity){

                    if(cache[set][y].dur<=cache[set][low].dur){

                        low=y;
                    }



                    y++;
                }

                cache[set][low].v=1;
                cache[set][low].Tag=tag;
                t++;
                cache[set][low].dur=t;
                return;
            }

            
          }


    x++;
}


return;
}

void readingL(unsigned long long tag, unsigned long long set, int associativity){

int x=0;
int y=0;
int low=0;

while(x<associativity){

    if(cache[set][x].v==0){

        M++;
        memory_read++;
        t++;
        cache[set][x].v=1;
        cache[set][x].Tag=tag;
        cache[set][x].dur=t;
        return;
    }

        
        else{ 

            if(cache[set][x].Tag==tag){
                H++;
                t++;
                cache[set][x].dur=t;
                return;
            }

            if(x==(associativity-1)){
                M++;
                memory_read++;
                low=0;
                while(y<associativity){

                    if(cache[set][y].dur<=cache[set][low].dur){

                        low=y;
                    }



                    y++;
                }

                cache[set][low].v=1;
                cache[set][low].Tag=tag;
                t++;
                cache[set][low].dur=t;
                return;
            }

            
          }


    x++;
}


return;
}
void writting(unsigned long long tag, unsigned long long set, int associativity){

int x=0;
int y=0;
int low;

while(x<associativity){

    if(cache[set][x].v==0){

        M++;
        memory_read++;
        memory_write++;
        t++;
        cache[set][x].v=1;
        cache[set][x].Tag=tag;
        cache[set][x].dur=t;
        return;
    }

        
        else{ 

            if(cache[set][x].Tag==tag){
                H++;
                memory_write++;
                return;
            }

            else if(x==(associativity-1)){
                M++;
                memory_read++;
                memory_write++;
                low=0;
                while(y<associativity){

                    if(cache[set][y].dur<=cache[set][low].dur){

                        low=y;
                    }



                    y++;
                }

                cache[set][low].v=1;
                cache[set][low].Tag=tag;
                t++;
                cache[set][low].dur=t;
                return;
            }

            
          }


   x++;
}


return;
}

void writtingL(unsigned long long tag, unsigned long long set, int associativity){

int x=0;
int y=0;
int low;

while(x<associativity){

    if(cache[set][x].v==0){

        M++;
        memory_read++;
        memory_write++;
        t++;
        cache[set][x].v=1;
        cache[set][x].Tag=tag;
        cache[set][x].dur=t;
        return;
    }

        
        else{ 

            if(cache[set][x].Tag==tag){
                H++;
                memory_write++;
                t++;
                cache[set][x].dur=t;
                return;
            }

            if(x==(associativity-1)){
                M++;
                memory_read++;
                memory_write++;
                low=0;
               while(y<associativity){

                    if(cache[set][y].dur<=cache[set][low].dur){

                        low=y;
                    }



                    y++;
                }

                cache[set][low].v=1;
                cache[set][low].Tag=tag;
                t++;
                cache[set][low].dur=t;
                return;
            }

            
          }


    x++;
}


return;
}

void freeing(int associativity, int setting){

    int x=0;
    int y=0;

    while(x<setting){

        while(y<associativity){

            cache[x][y].Tag=0;
            cache[x][y].v=0;
            cache[x][y].dur=0;
            y++;

        }

        x++;
    }
    M=0;
    H=0;
    memory_read=0;
    memory_write=0;
    t=0;
}


bool checkPower(int CS_BS)
{
   if(CS_BS==0)
   return false;
 
   return (ceil(log2(CS_BS)) == floor(log2(CS_BS)));
}

int main(int argc, char* argv[]){
//<cache size> <associativity> 
//<replace policy> <block size> <trace file>

int CS = atoi(argv[1]);
int  associativity;
int assoc;
int block;
int sett;
int setting;
int BS = atoi(argv[4]);
unsigned long long add; //long int
//unsigned long updateAdd;

if(!(checkPower(CS))){
    
    printf("error");
    return 0;
}
if(!(checkPower(BS))){

    printf("error");
    return 0;
}

char W_R;
unsigned long long setLines;
unsigned long long tag;
unsigned long long set;

//FILE* myFile;
//char c[10];
if(argv[3][0]=='f'){ //fifo

    FILE* myFile;
    myFile=fopen(argv[5], "r");

    if(myFile==NULL){

        printf("wrong file name!");
        return 0;
    }



if(argv[2][0]=='d'){

    associativity = 1;
    setting = CS/BS;

}

else if(argv[2][5]!=':'){

    setting = 1;
    associativity=CS/BS;
}   
else{

    sscanf(argv[2], "assoc:%d", &assoc);
    associativity=assoc;
    setting = CS/BS/assoc;

}

//number of buts in each index

block= log(BS)/log(2);
sett=log(setting)/log(2);
setLines = ((1ULL<<sett)-1);
int tagbits=48-sett-block; 
cache=makeCache(associativity, setting);

while(fscanf(myFile, "%*x: %c %llx", &W_R, &add)==2){

set=(add>>block)&setLines;
tag=(add>>(block+sett))&((1ULL<<tagbits)-1);

if(W_R=='W')
    writting(tag,set,associativity);

else if(W_R=='R')
    reading(tag,set,associativity);


}

fclose(myFile);
myFile=fopen(argv[5], "r");

    if(myFile==NULL){

        printf("there is no file with such name!");
        return 0;
    }

printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",memory_read,memory_write,H,M);

freeing(associativity, setting);



}
else if(argv[3][0]=='l'){ //LRU
 
    FILE* myFile;
    
    myFile=fopen(argv[5], "r");

    if(myFile==NULL){

        printf("there is no file with such name!");
        return 0;
    }



if(argv[2][0]=='d'){ 

    associativity = 1;
    setting = CS/BS;

}

else if(argv[2][5]!=':'){

    setting = 1;
    associativity=CS/BS;
}   
else{

    sscanf(argv[2], "assoc:%d", &assoc);
    associativity=assoc;
    setting = CS/BS/assoc;

}

//number of bits in each index

block= log(BS)/log(2);
sett=log(setting)/log(2);
setLines = ((1ULL<<sett)-1); //1ULL
int tagbits=48-sett-block; 
cache=makeCache(associativity,setting);

while(fscanf(myFile, "%*x: %c %llx", &W_R, &add)==2){

set=(add>>block)&setLines;
tag=(add>>(block+sett))&((1ULL<<tagbits)-1);

if(W_R=='W')
    writtingL(tag,set,associativity);

else if(W_R=='R')
    readingL(tag,set,associativity);


}

fclose(myFile);
myFile=fopen(argv[5], "r");

    if(myFile==NULL){

        printf("there is no file with such name!");
        return 0;
    }

printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",memory_read,memory_write,H,M);

freeing(associativity, setting);

}


else{

    printf("error");
    return 0;
}

//getchar();

//if(fscanf(myFile, "%s", &c)) exit;

return 0;


}



