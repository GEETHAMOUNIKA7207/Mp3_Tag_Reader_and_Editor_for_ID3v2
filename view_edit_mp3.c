#include "header_mp3.h"

#define SWAP(n)\
{\
    unsigned char* ptr =(unsigned char*)&(n);\
    for(int i=0;i<2;i++)\
    {\
	unsigned char swap=ptr[i];\
	ptr[i]=ptr[4-i-1];\
	ptr[4-i-1]=swap;\
    }\
}

Status edit_tags(FILE *org,FILE *dup,char *usr_str,char *tag)
{
    char arr[100];
    fseek(org,0,SEEK_SET);
    fseek(dup,0,SEEK_SET);
    fread(arr,10,1,org);
    fwrite(arr,10,1,dup);
    int size=0,org_size=0;
    char str[5]={0};
    for(int i=0;i<6;i++)
    {
	fread(str,4,1,org);
	fwrite(str,4,1,dup);
	if(strncmp(str,tag,4) == 0)
	{   
	    size=strlen(usr_str);
	    int temp_size=size;
	    size++;

	    SWAP(size);
	    fwrite(&size,4,1,dup);

	    fread(&org_size,4,1,org);

	    fread(arr,3,1,org);
	    fwrite(arr,3,1,dup);

	    fwrite(usr_str,temp_size,1,dup);
	    SWAP(org_size);
	    fseek(org,org_size-1,SEEK_CUR);
	}
	else
	{
	    fread(&org_size,4,1,org);
	    fwrite(&org_size,4,1,dup);

	    SWAP(org_size);

	    fread(arr,3,1,org);
	    fwrite(arr,3,1,dup);

	    fread(arr,org_size-1,1,org);
	    arr[org_size-1]='\0';
	    fwrite(arr,org_size-1,1,dup);

	}
    }
    copy_remaining(org,dup);
    fclose(org);
    fclose(dup);
}
void copy_remaining(FILE *src,FILE *dest)
{
    char ch;
    while((fread(&ch,1,1,src)) > 0)
    {
	fwrite(&ch,1,1,dest);
    }
}
Status read_tags(FILE* Fptr)
{
    char Version[2],Title[50]={0},Artist[50]={0},Album[50]={0},Year[4]={0},Content[50]={0},Compose[50]={0};
    int size=0;
    char str[4]={0};
    fread(str,3,1,Fptr);
    str[3]='\0';
    if(strcmp(str,"ID3") != 0)
    {
	printf("Given file is not a MP3 file\n");
	return e_failure;
    }
    fread(Version,2,1,Fptr);
    if(Version[0] == 03 && Version[1] == 00)
    {
	strcpy(Version,"2");
    }
    fseek(Fptr,5,SEEK_CUR);
    for(int i=0;i<6;i++)
    {
	char arr[4]={0};
	fread(arr,4,1,Fptr);
	fread(&size,4,1,Fptr);
	SWAP(size);
	fseek(Fptr,3,SEEK_CUR);
	if(strncmp(arr,"TIT2",4) == 0)
	{
	    fread(Title,size-1,1,Fptr);
	    Title[size-1]='\0';
	}
	else if(strncmp(arr,"TPE1",4) == 0)
	{
	    fread(Artist,size-1,1,Fptr);
	    Artist[size-1]='\0';
	}
	else if(strncmp(arr,"TALB",4) == 0)
	{
	    fread(Album,size-1,1,Fptr);
	    Album[size-1]='\0';
	}
	else if(strncmp(arr,"TYER",4) == 0)
	{
	    fread(Year,size-1,1,Fptr);
	    Year[size-1]='\0';
	}
	else if(strncmp(arr,"TCON",4) == 0)
	{
	    fread(Content,size-1,1,Fptr);
	    Content[size-1]='\0';
	}
	else if(strncmp(arr,"COMM",4) == 0)
	{
	    fread(Compose,size-1,1,Fptr);
	    Compose[size-1]='\0';

	}
    }
    printf("-------------------------------------------\n");
    printf("MP3 Tag Reader and Editor for ID3v%s\n",Version);
    printf("-------------------------------------------\n");
    printf("Title \t\t: \t%s\nArtist \t\t: \t%s\nAlbum \t\t: \t%s\nYear \t\t: \t%s\nGenre \t\t: \t%s\nComposer \t: \t%s\n",Title,Artist,Album,Year,Content,Compose);
    printf("-------------------------------------------\n");
    return e_success;

}

