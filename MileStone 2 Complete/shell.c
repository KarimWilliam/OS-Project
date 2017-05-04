char input[80];
char buffer[13312]; /*this is the maximum size of a file*/
char fileName[80];
int equals (char* , char* );

int main()
{
  int i;
  while(1=1){

interrupt(0x21,0,"SHELL>\0",0,0);
interrupt(0x21,1,input,0,0);
if(equals(input,"view \0"))
{
  i=5;
  while(input[i]!=' ')
  {
fileName[i-5]=input[i];
i++;
  }
  fileName[i]='\0';
interrupt(0x21,0,"printing the file >\0",0,0);
interrupt(0x21,3,fileName,buffer,0);
interrupt(0x21, 0, buffer, 0, 0); /*print out the file*/

}
else if(equals(input ,"execute \0"))
{
  i=8;
  while(input[i]!=' ')
  {
fileName[i-8]=input[i];
i++;
  }
  fileName[i]='\0';
  interrupt(0x21,0,"executing the file >\0",0,0);
interrupt(0x21,4,fileName,0x2000,0);
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
