void printString(char*);
int readString(char*);
void readSector(char*,int);
int mod(int,int);
int div(int,int);
void handleInterrupt21(int,int,int,int);

int main()
{

char line[80];
//char line[80];
printString("enter a line: \0");
//readString(line);
//printString(line);
//char buffer[512];
//readSector(buffer, 30);
//printString(buffer);
//makeInterrupt21();
//interrupt(0x21,0,0,0,0);

makeInterrupt21();
interrupt(0x21,1,line,0,0);
interrupt(0x21,0,line,0,0);

//while(1=1){}

}
//PART 1

void printString(char* chary){
int i=0;
while(*(chary+i)!='\0'){
interrupt(0x10, 0xE*256+chary[i], 0, 0, 0);
i++;
}
interrupt(0x10, 0xE*256+0xa, 0, 0, 0);
  interrupt(0x10, 0xE*256+0xd, 0, 0, 0);
}

//PART 2
int readString(char* line)
{
  int i = 0;
 char in = 0x0;
 while (in != 0xd)
   {
    in = interrupt(0x16, 0x0, 0x0, 0x0, 0x0);

    if (in == 0x8)
       {
        if (i != 0)
        {
          i--;
            interrupt(0x10,0xe*0x100+8,0x0,0x0,0x0);
            interrupt(0x10,0xe*0x100+' ',0x0,0x0,0x0);
            interrupt(0x10,0xe*0x100+8,0x0,0x0,0x0);

        }
       }
       else {

    *(line + i) = in;
    interrupt(0x10,0xe*0x100+in,0x0,0x0,0x0);
    i++;
            }
   }

 *(line + i) = 0xa;
  interrupt(0x10,0xe*0x100+0xa,0x0,0x0,0x0);
  i++;  *(line + i) = 0x0;
 return i;
}


/* part 3 */
void readSector (char* buffer,int sector){
int relativeSector , head , track;
int dx,cx,ax;
 relativeSector = mod(sector,18) +1 ;
 head=mod(div(sector,18),2);
 track=div(sector, 36);
dx = head*256 + 0;
cx = track*256 + relativeSector;
ax = 2*256+1;
interrupt(0x13,0x2*256+1,buffer,cx,dx);
}
// MOD Fucntion
int mod (int a,int b){
//int c=a % b;
//if(c<0)
//c+=b;
int c;
c= (a-(div(a,b))*b);
return c;
}

//DIV Function
int div (int a,int b) {
  int c=0;
while(a>=b)
{
  a=a-b;
  c++;
}
return c;
}




/* part 4/5 */

void handleInterrupt21(int ax, int bx, int cx, int dx){

if (ax == 0){
printString(bx);
}

if (ax == 1){
readString(bx);
}

if (ax == 2){
readSector(bx,bx);
}

if (ax >= 3){
printString("error");
}
}
