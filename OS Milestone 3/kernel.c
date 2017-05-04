void printString(char*);
int readString(char*);
void readSector(char*,int);
int mod(int,int);
int div(int,int);
void handleInterrupt21(int,int,int,int);
void readFile(char*,char*);
int filename (char * , int, char * );
void executeProgram(char* , int );
void terminate();
void deleteFile(char* );
void writeSector(char* ,int );
void writeFile(char*, char* , int );
void PrintNum(int);
char directory[512];
char map[512];


int main()
{

//char line[80];
//char buffer[13312]; /*this is the maximum size of a file*/
//char line[80];
//printString("This is the start of the main method \0");
//readString(line);
//printString(line);
//char buffer[512];
//readSector(buffer, 30);
//printString(buffer);
//makeInterrupt21();
//interrupt(0x21,0,0,0,0);
//makeInterrupt21();
//interrupt(0x21, 3, "messag\0", buffer, 0); /*read the file into buffer*/
//interrupt(0x21, 0, buffer, 0, 0); /*print out the file*/
makeInterrupt21();
interrupt(0x21, 4, "shell\0", 0x2000, 0);
//interrupt(0x21, 7, "messag\0", 0, 0); //delete messag
//interrupt(0x21, 3, "messag\0", buffer, 0); // try to read messag
//interrupt(0x21, 0, buffer, 0, 0); //print out the contents of buffer
//int i=0;
//char buffer1[13312];
//char buffer2[13312];
//buffer2[0]='h'; buffer2[1]='e'; buffer2[2]='l'; buffer2[3]='l'; buffer2[4]='o';
//for(i=5; i<13312; i++) buffer2[i]=0x0;
//makeInterrupt21();
//interrupt(0x21,8, "testW\0", buffer2, 1); //write file testW
//interrupt(0x21,3, "testW\0", buffer1, 0); //read file testW
//interrupt(0x21,0, buffer1, 0, 0); // print out contents of testW
while(1);

}
 // WRITES A SECTOR
void writeSector(char* buffer,int sector){
int relativeSector , head , track;
int dx,cx,ax;
 relativeSector = mod(sector,18) +1 ;
 head=mod(div(sector,18),2);
 track=div(sector, 36);
dx = head*256 + 0;
cx = track*256 + relativeSector;
ax = 2*256+1;
interrupt(0x13,0x3*256+1,buffer,cx,dx);
}


// DELETS A FILE
void deleteFile(char* name){
int i = 0;
int y,x,s;
int sec[27];
int found;

(directory, 2);
readSector(map,1);

 found=filename(directory,i,name);


while(found !=1 && i<16){
i++;
found=filename(directory,i*32,name);
}

if(found==0){

printString("File not found\n\0");
return;
}

//for( x=0;x<6;x++){
directory[i*32] =0x00;
//}


for(y=0;y<26;y++){
sec[y] = directory[i*32+6+y];
//directory[i*32+6+y]= 0x00;
}
sec[26]=0x0;

for( s=0;s<26;s++){
if(sec[s] == 0x0){
break;
}

map[sec[s+1]]=0x00;
}
writeSector(map,1);
writeSector(directory,2);
}

//WRITES A FILE
void writeFile(char* name, char* buffer, int secNum)
{
int buffSize=0;
int s,y,l,m,h;
int i=0;
int sec[512];
int sector;
int length;
int k=0;
readSector(directory,2);
readSector(map,1);

while(directory[i*32] != 0x00 && i<16){
i++;
}

if(directory[i*32] != 0x00){
printString("no free space");
return;
}

for(length=0; name[length]!='\0' && name[length]!=0x0 ;length++){

}

for( y=0;y<length;y++){
directory[i*32+y] = name [y];
}

if (length<6){
 for( l=length; l<6 ;l++){
directory[i*32+l] = 0x00;
}
}

/* For each sector making up the file */

for(s=0; s<secNum ; s++){
sector=0;

/*finding a free sector*/
while(map[sector] != 0x00 ){
sector++;
}

if(sec==26){
printString("no free space\n");
return;
}

map[sector]=0xFF;

directory[i*32+6+s] = sector;

writeSector(buffer+k,sector);
k+=512;
}


for( h=s; h<32;h++){
directory[i*32+6+h] = 0x00;
}

writeSector(directory,2);
writeSector(map,1);
}



//USELESS
void terminate()
{
while(1);
}
// READ FILE
void readFile (char* fileName,char* buffer)
{
  //The Directory lists the names and locations of the files
  //Directory has 16 entries. each entry is 32 bytes
  //the first 6 bytes of each entry is the file name
  //remaining 26 bytes are sector numbers
  char DirectoryBuffer[512];
  char firstSector;
  char lastSector;
  int found;
  int i=0;
  int k=6;
  int j=0;
  int count=0;
  int inc =0;
  int firstSectorN;
  int lastSectorN;
  int sector;
  int index;
  char arr[512];
  char* error = "File not found \0";

  readSector(DirectoryBuffer, 2);
  found = filename(DirectoryBuffer,i*32,fileName);

  while (found != 1 && i<16)
  {

i++;
found = filename(DirectoryBuffer,i*32,fileName);
}

if (found == 1){
 index=i;

i=6;
 sector=0;


while (DirectoryBuffer[index*32+i] != 0x00 && i <32)
{
sector= DirectoryBuffer[index*32+i];
readSector(arr,sector);
for ( j=0;j<512;j++)
{
buffer [j+inc] = arr[j];

}
i++;
inc += 512;
}

}
if (found ==0){

 printString("File not found!\n\0");
 printString(error);

}
}


int filename(char * DirectoryBuffer, int index, char * name){
    int i = 0;
    int result = 1;
    for(i = 0; i < 6; i++){
        if(name[i] == '\0' && DirectoryBuffer[i+index] == '\0' && i != 0){
            return result;
        }
        if(DirectoryBuffer[i+index] != name[i]){
            result = 0;

        }
    }
    return result;
}
//Excute program
void executeProgram(char* name, int segment){
  int i;
  char buffer[13312];
  int count;
  readFile(name,buffer);
  for(i=0;i<13312;i++)
  {
    putInMemory(segment,i,buffer[i]);

  }
  launchProgram(segment);
}


//PRINTS A STRING
void printString(char* chary){
int i=0;
while(*(chary+i)!='\0'){
interrupt(0x10, 0xE*256+chary[i], 0, 0, 0);
i++;
}
interrupt(0x10, 0xE*256+0xa, 0, 0, 0);
  interrupt(0x10, 0xE*256+0xd, 0, 0, 0);
}

//READS A STRING
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


// READS A SECTOR
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

//PRINTS A number
void printNum(int num)
{

	int current,mask,i;
	do{
		i = num;
		mask = 1;
		while(i>9){
			i = div(i,10);
			mask = mask*10;
		}
		current = div(num,mask);
		num = mod(num,mask);
		interrupt(0x10, 0xE*256+current+48, 0, 0, 0);
	}while(num!=0);

}


// HANDLES INTERRUPTS

void handleInterrupt21(int ax, int bx, int cx, int dx){

if (ax == 0){
printString(bx);
}

if (ax == 1){
readString(bx);
}

if (ax == 2){
readSector(bx,cx);
}

if (ax == 3){
readFile(bx,cx);
}
if (ax ==4)
{
  executeProgram(bx,cx);
}
if(ax ==5)
{
  char shell[5];
  shell[0]='s'; shell[1]='h';shell[2]='e';shell[3]='l';shell[4]='l';shell[5]='\0';
interrupt(0x21, 4, shell, 0x2000, 0);
}
if(ax ==6)
{
  writeSector(bx,cx);
}
if(ax==7)
{
  deleteFile(bx);
}
if(ax==8)
{
  writeFile(bx,cx,dx);
}
if(ax==20)
{
  printNum(bx);
}
}
