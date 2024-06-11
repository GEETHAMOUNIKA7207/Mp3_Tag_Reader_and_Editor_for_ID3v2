#include "header_mp3.h"

int main(int argc,char *argv[])
{
    FILE *Fptr;
    if(argc == 1)
    {
	printf("ERROR : ./a.out : INVALID ARGUMENTS\n");
	printf("USAGE :\nTo view please pass like: ./a.out -v mp3filename\nTo edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c mp3filename\n");
	return 0;
    }

    if(strcmp("--help",argv[1]) == 0)
    {
	printf("Usage : mp3tag -[tTaAycg] ""\"value\""" file1\n\tmp3tag -v\t\n -t\tModifies a Title tag\n -T\tModifies a Track tag\n -a\tModifies a Artist tag\n -A\tModifies a Album tag\n -y\tModifies a Year tag\n -c\tModifies a Comment tag\n -g\tModifies a Genere tag\n -h\tDisplays this help info\n -v \tPrints version info\n");
	return 0;
    }
    if(strcmp("-v",argv[1]) == 0)
    {
	if(argv[2] == 0)
	{
	    printf("Please pass file name\n");
	    return 0;
	}
	Fptr=fopen(argv[2],"r");
	read_tags(Fptr);
	fclose(Fptr);
	return e_success;
    }
    FILE *orginal;
    FILE *duplicate;
    if(strcmp("-e",argv[1])== 0)
    {

	//if(argv[2] == 0)
	if(argc == 2)
	{
	    printf("----------SELECTED EDIT DETAILS----------\n");
	    printf("Please pass tag arguments which you want to edit\n");
	    printf("eg: ./a.out -e -t/-a/-A/-y/-m/-c mp3 filename\n");
	    return 0;
	}
	else if(argv[3] == 0)
	{
	    printf("please pass tag to edit\n");
	    return 0;
	}
	else if(argv[4] == 0)
	{
	    printf("Please pass mp3 file name\n");
	    return 0; 
	}
	char array[5],tag[150];
	orginal=fopen(argv[4],"r");
	duplicate=fopen("temp.mp3","w");
	if(duplicate == NULL)
	{
	    return 0;
	}
	strcpy(tag,argv[3]);
	if(strcmp("-t",argv[2]) == 0)
	{
	    strcpy(array,"TIT2");
	    printf("Title tag selected for editing\n");
	}
	else if(strcmp("-a",argv[2]) == 0)
	{
	    strcpy(array,"TPE1");
	    printf("Artist tag selected for editing\n");
	} 
	else if(strcmp("-A",argv[2]) == 0)
	{
	    strcpy(array,"TALB");
	    printf("Album tag selected for editing\n");
	}
	else if(strcmp("-y",argv[2]) == 0)
	{
	    strcpy(array,"TYER");
	    printf("Year tag selected for editing\n");
	} 
	else if(strcmp("-c",argv[2]) == 0)
	{
	    strcpy(array,"COMM");
	    printf("Content tag selected for editing\n");
	} 
	else if(strcmp("-g",argv[2]) == 0)
	{
	    strcpy(array,"TCON");
	    printf("Comments tag selected for editing\n");
	}
	else
	{
	    printf("Please pass Valid arguments to edit\n");
	    return 0;
	}
	printf("Function\n");
	edit_tags(orginal,duplicate,tag,array);
    }
    return 0;    
}
