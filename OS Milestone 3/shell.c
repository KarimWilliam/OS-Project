char input[80];
char buffer[13312];  /*this is the maximum size of a file*/
char fileName[80];
char fileName2[80];
char dirName[10];
char directory[512];
int u=0;
int k=0;
char userLine[80];


int equals (char* , char* );

int main()
{

  int empty=0;
  int i;
  int count=0;
  while(1=1){

count=0;
interrupt(0x21,0,"SHELL>\0",0,0);
interrupt(0x21,1,input,0,0);
if(equals(input,"view \0"))
{
  i=5;
  while(input[i]!=' ' && input[i]!='\0')
  {
fileName[i-5]=input[i];
i++;
  }
  fileName[i]='\0';
interrupt(0x21,0,"printing the file >\0",0,0);
interrupt(0x21,3,fileName,buffer,0);
interrupt(0x21, 0, buffer, 0, 0); /*print out the file*/
// empties the buffer
for(u=0;u<13312;u++)
{
   buffer[u]='\0';
}
}
else if(equals(input ,"execute \0"))
{
  i=8;
  while(input[i]!=' ' && input[i]!='\0')
  {
fileName[i-8]=input[i];
i++;
  }
  fileName[i]='\0';
  interrupt(0x21,0,"executing the file >\0",0,0);
interrupt(0x21,4,fileName,0x2000,0);



}
else if(equals(input ,"delete \0"))
{
  i=7;
  while(input[i]!=' ' && input[i]!='\0')
  {
  fileName[i-7]=input[i];
  i++;
  }
  fileName[i]='\0';
  interrupt(0x21,0,"deleting the file >\0",0,0);
  //interrupt(0x21, 7, "messag\0", 0, 0); //delete messag
  interrupt(0x21,7,fileName,0,0);
}
else if(equals(input ,"copy \0"))
{
  i=5;
  while(input[i]!=' ' && input[i]!='\0')
  {
  fileName[i-5]=input[i];
  i++;
  }
    fileName[i]='\0';

  while(input[i]!=' ' && input[i]!='\0')
  {
    fileName2[count]= input[i];
    i++;;
    count++;
  }
fileName2[count]='\0';
  interrupt(0x21,0,"copying the file >\0",0,0);
  //interrupt(0x21, 7, "messag\0", 0, 0); //delete messag
  interrupt(0x21,3,fileName,buffer,0);

  count=0;
  while(buffer[count++]!='\0');
  count= div(count,512)+1;

  interrupt(0x21,8,fileName2,buffer,count);

}

else if(equals(input ,"dir \0")|| equals(input ,"dir\0"))
{
  i=0;
interrupt(0x21,2,directory,2,0);
for(count=0;count<16;count++)
{
  if(directory[count*32]!=0x0)
  {
    for(i=0;directory[count*32+i]!='\0' && i<6;i++)
    {
      dirName[i]=directory[count*32+i];
    }
    dirName[i++]='\0';
    for(i=6;directory[count*32+i]!='\0';i++);

interrupt(0x21,0,dirName,0,0);
interrupt(0x21,0,"sectors: ",0,0);
interrupt(0x21,20,i-6,0,0);
interrupt(0x21,0,"\n",0,0);

for(u=0;u<6;u++)
{
   dirName[u]='\0';
}
  }
}


}
else if(equals(input ,"create \0"))
{
  i=7;
  while(input[i]!=' ' && input[i]!='\0')
  {
  fileName[i-7]=input[i];
  i++;
  }
  fileName[i]='\0';

i=0;
  while(1)
  {

    interrupt(0x21,1,userLine,0,0,0);


    for(k=0;userLine[k]!='\0';k++)
    {
      buffer[i]=userLine[k];
      i++;
    }


    for(u=1;u<80;u++)
    {
       userLine[u]='\0';
    }

    if(k<=2)
    {
      buffer[i]= '\0';
      break;
    }
  }

  interrupt(0x21,8,fileName,buffer,div(i,512)+1);

  for(u=0;u<13312;u++)
  {
     buffer[u]='\0';
  }

}

else{
  interrupt(0x21,0,"Bad Command\0",0,0);
}
}
}

int equals (char* s1, char* s2)
{
  int i=0;
  while(i<80)
  {


  if (s1[i]!=s2[i])
  {
    return 0;
  }

  i++;
  if ( s2[i]=='\0')
  {
    return 1;
  }
}
return 0;
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
