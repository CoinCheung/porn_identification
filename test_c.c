#include<stdio.h>
#include<string.h>
#include<stdlib.h> /* system() */
/* #include"cserver.h" */
#include<sys/socket.h>
#include<malloc.h>
/* #include<string.h> */

#define true 1
#define false 0

typedef struct
{
    int channel;
    int width;
    int height;
    int8_t*** data;
} img_para;


void* fun()
{
    char *p = NULL;

    p = malloc(10*sizeof(char));

    return (void*)p;
}

int main()
{
    int i = 0;
    char rec[10];
    int rec2[5][2];
    char* p = NULL;

    rec[0] = 65;
    rec[1] = 65;
    /* rec[2] = 66;
     * rec[3] = 67;
     * rec[4] = 65;
     * rec[5] = 66;
     * rec[6] = 67;
     * rec[7] = 66;
     * rec[8] = 67; */
    rec[9] = 0;

    int *ipp = NULL;
    ipp = fun();
    *ipp = 3;
    fprintf(stdout,"value of *ipp is: %d\n",*ipp);


    /* rec2[9][1] = 0; */
    p = rec;

    int d[10];
    int *dp = 0;
    dp = d;

    img_para ip;

    fprintf(stdout,"length of pointer is: %ld\n",sizeof(p));

    p = (char *)malloc(100);
    memset(p,5,100);

    // char *str = "0x040xdc";
    // fprintf(stdout,"number is(hex): %ld\n", strtol(str, NULL, 0));

    int m=3, n= 5;
    /* char (*pp)[m][n] = malloc(m*n*4); */
    /* int aa[m] = {1,2,3}; */
    char (*pp)[m][n];

    pp = malloc(m*n*4);
    memset(pp,3,m*n*4);
    fprintf(stdout, "array value is: %d\n",pp[1][1][1]);

    char *str = "abcdefghijklmn";
    void *vp;
    vp = str;
    fprintf(stdout,"%s\n",vp);
    fprintf(stdout,"%s\n",vp+2);

    int width = 500;
    int height = 30;
    int skin = 1000;
    double ratio;

    ratio = (double)skin/(width*height);
    fprintf(stdout, "ratio is: %lf\n",ratio);
    char *cp = malloc(sizeof(char)*10);

    for(int i = 0; i < 10; i++)
        sprintf(cp+i,"%d",i);

    fprintf(stdout, "printed char is: %s\n",cp);

    /* fprintf(stdout, "array value is: %d\n",aa[3]); */

/*     while(1){
 *         i ++;
 *         printf("finished\n");
 *         if(i == 0)
 *             break;
 *         while(1){
 *             i ++;
 *             if(i == 0)
 *                 break;
 *         }
 *     }
 *  */

    /*     char *str = "good"; */
    /*     char ca1[] = {'h','e','l','l','o'}; */
    /*     char ca2[7] = {65,66,67,68,69,70,0}; */
    /*     char ca3[7] = "seven77"; */
    /*  */
    /*     printf("%s %s %s %s",str,ca1,ca2,ca3); */
    /*     printf("\n"); */
    /*     printf("\n"); */
    /*     printf("%d %d %d %d",strlen(str),strlen(ca1),strlen(ca2),strlen(ca3)); */
    /*     printf("\n"); */
    /*  */
    /*  */
    /* printf("finished\n"); */
    /* printf("%d\n",sizeof(rec)); */
    /*  */
    /* system("netstat -na > netstat.log"); */
    /*  */
    /* char *str1 = "giood"; */
    /* printf("%d %d",strcmp(str1,str),strcmp(str1,str)); */
    /*  */
    /* printf("\n"); */
    /* int num = 100; */
    /* char strng[2]; */
    /* sprintf(strng,"jjjjjjjjjj%d\n",num); */
    /* printf("%s",strng); */
    /* printf("%d\n",strlen(strng)); */
    /*  */
    /* int n = 10; */
    /* n = n*n; */
    /* int astr[n]; */
    /* for(int i = 0;i < n; i++) */
    /*     astr[i] = 1; */
    /* for(int i = 0;i < n; i++) */
    /*     printf("%d",astr[i]); */
    /*  */
    /* [> printf("\nthe port not being used is: %d\n",scan_leisure_port()); <] */
    /*  */
    /* printf("SEEK_END VALUE is %d\n",SEEK_END); */
    /* FILE *fhd = NULL; */
    /*  */
    /* system("netstat -ano > netstat.log"); */
    /*  */
    /* fhd = fopen("netstat.log", "r+"); */
    /*  */
    /* char *ss = (char*)malloc(1024); */
    /* fgets(ss,1024,fhd); */
    /* printf("sizeof return of fgetc is: %d\n",sizeof(fgetc(fhd))); */
    /* printf("return of fputc is: %d\n",fputc(65,fhd)); */
    /* printf("return of fgetc is: %d\n",fgetc(fhd)); */
    /* printf("return of fgets is: %s\n",ss); */
    /* // scanf("scanf input %s\n",ss); */
    /* printf("string got by scantf is: %s\n",ss); */
    /*  */
    /* if(fclose(fhd)) */
    /* { */
    /*     perror("cannot close the file\n"); */
    /*     exit(0); */
    /* } */
    /*  */
    /* char *a = "abcdefg"; */
    /* char b[10]; */
    /* memset(b,0,sizeof(b)); */
    /* strncpy(b,a,3); */
    /* b[3] = 0; */
    /* // strcpy(b,a); */
    /* fputs(b,stdout); */
    /* fprintf(stdout,"\n%d\n",(int)strlen(b)); */

}

/* function: unsigned int scan_leisure_port()
 * scan the ports of the computer and return an unoccupied one
 * netstat is required here */
/* unsigned int scan_leisure_port()
 * {
 *
 *     unsigned int port_num = 1025;
 *     char line[1024];
 *     FILE *fhd = NULL;
 *     char portExists = 0;
 *
 *     system("netstat -ano > netstat.log");
 *
 *     fhd = fopen("netstat.log", "r");
 *
 *     while(1)
 *     {
 *         memset(line, 0, sizeof(line));  //reset the readline buffer
 *         // if(rewind(fhd) != 0) // rewind the file pointer position
 *         // {
 *         //     perror("failed to rewind the file when scan port %d", port_num);
 *         //     fclose(fhd);
 *         //     exit(0);
 *         // }
 *
 *         portExists = 0;
 *         while(!feof(fhd))
 *         {
 *             fgets(line,sizeof(line),fhd);  // read one line from the file
 *             portExists = is_port_occupied(line, strlen(line), port_num);
 *             if(portExists == true) // if the port is occupied, try next one
 *                 break;
 *         }
 *
 *         if(portExists == false) // if the port is not occupied, break the loop
 *             break;
 *
 *         port_num++;
 *     }
 *
 *
 *     fclose(fhd);
 *
 *     return port_num;
 * } */


/* function: is_port_occupied(char[], int len, int port_num)
 * try the line char[] to see if port is in it */
int is_port_occupied(char line[],int len, int port_num)
{
    char port_str1[10];
    char port_str2[10];
    char substr[10];
    short i;
    short port_len;

    sprintf(port_str1," %d ",port_num); /*  " port_num " partern */
    sprintf(port_str2,":%d ",port_num);  /* ":port_num " partern */

    port_len = strlen(port_str1);
    for(i = 0; i < len-port_len+1; i++)
    {
        strncpy(substr,line+i,port_len);
        if(strcmp(substr,port_str1) || strcmp(substr,port_str2))
            return true;
    }
    return false;
}

