/*
Info
    Author:  Liu Yilin        CQUPT#:2019215075   BUL#:1944419
    Purpose: Database of student
    File: stu.txt
          records.txt
       *** THE TWO FILES AND THIS PROGRAMME MUST BE IN TEH SAME FILECILP ***
       *** the two files and this programme must be in the same filecilp ***  
    Environment： IDE：Visual Studio Code
                  Extensions：
                     C/C++           verson：0.26.3-insiders2
                     Code Runner     version：0.9.154
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//struct declaration 
     struct transcript {
        int stuno1;
        char cname[50];
        int score;
        char remark[100];};
    
     struct student {
            int stuno;
            char fname[20]; 
            char lname[20]; 
            int age; 
            struct transcript subject; };

//functions' defination
/*function name:Q1readstu
  purpose:read data from stu.txt
  usage:Q1readstu(pointer of struct,linetemp,row,pointer of file)*/
  void Q1readstu(struct student *sturecord,char *b,int row_stu,FILE *fp_stu)
  {
      for (int g = -1; g < row_stu; g++)
    {   int charcounter_stu1,charcounter_stu2=0;
        fgets(b, 100, fp_stu);
         //ruler                     0123 456789 012345 67
        //now each line format:      101, Keanu, Reeves,21
        //                     => part A,part B,part C,part D

        sscanf(b,"%d",&sturecord[g].stuno);//put part A into stuno
        charcounter_stu1=counter(b,4);
        strncpy(sturecord[g].fname,b+4,charcounter_stu1);//put partB into fname
        charcounter_stu2=counter(b,4+charcounter_stu1+1);
        strncpy(sturecord[g].lname,b+4+charcounter_stu1+1,charcounter_stu2);//put partC into lname
        char tempscore2[1][2]={'0','0'};
        strncpy(tempscore2,b+4+charcounter_stu1+charcounter_stu2+2,2);//put partD into tempscore
        sturecord[g].age=((tempscore2[0][0]-48)*10+tempscore2[0][1]-48);//covert char tempscore to int score

    }
    fclose(fp_stu);
  }

/*function name:Q2sortbyage
  purpose:sort the data by age
  usage:Q2sortbyage(pointer of struct,row)*/
  void Q2sortbyage(struct student *sturecord,int row_stu)
  {
     struct student tmp;
   for (int i = 0; i < row_stu; i++)
    {
        for (int j = 0; j < row_stu-1-i; j++)
        {
            if (sturecord[j].age>sturecord[j+1].age)
            {
                tmp=sturecord[j];
                sturecord[j]=sturecord[j+1];
                sturecord[j+1]=tmp;
             }
        
        }
    } 

  }

/*function name:Q3sortbyscore
  purpose:sort the data by score
  usage:Q3sortbyscore(pointer of struct,row)*/
  void Q3sortbyscore(struct student *sturecord,int row_record)
  {
      struct student tmp2;
     for (int i = 0; i < row_record; i++)
     {
            for (int j = 0; j < row_record-1-i; j++)
            {
                if (sturecord[j].subject.score>sturecord[j+1].subject.score)
                {
                    tmp2=sturecord[j];
                    sturecord[j]=sturecord[j+1];
                    sturecord[j+1]=tmp2;
                }
        
            }
     } 
  }


/*function name:Q4avsc_cacul
    purpose:caculate average score
    usage:avse_caul(arryname,lenth of arry)*/
    float Q4avsc_cacul(struct student *A,int n)
    { 
        if(n==0)
            return A[n].subject.score;
        else
             return (A[n-1].subject.score+(n-1)*Q4avsc_cacul(A,n-1))/n;
    }

/*function name:Q5remarkscore
  purpose:remark the score
  usage:Q5remarkscore(pointer of structarry,row )*/
  void Q5remarkscore(struct student *sturecord,int row_record)
  {
      for (int i = 0; i < row_record; i++)
    {
        if (40<=sturecord[i].subject.score&&sturecord[i].subject.score<=44)
            { strcpy(sturecord[i].subject.remark,"Ordinary Degree(Pass)");}
        else if(45<=sturecord[i].subject.score&&sturecord[i].subject.score<=49)
            {strcpy(sturecord[i].subject.remark,"Third Class Degree");}
        else if(50<=sturecord[i].subject.score&&sturecord[i].subject.score<=59)
            {strcpy(sturecord[i].subject.remark,"Lower-second Class Degree");}
        else if(60<=sturecord[i].subject.score&&sturecord[i].subject.score<=69)
            {strcpy(sturecord[i].subject.remark,"Upper-second Class Degree");}
        else if(70<=sturecord[i].subject.score&&sturecord[i].subject.score<=100)
            {strcpy(sturecord[i].subject.remark,"First Honors Degree");}
        else
            {strcpy(sturecord[i].subject.remark," ");}
    }

  }


/*function name:file_checker
  purpose:test whether the file can be opened
  usage:file_checker(pointer of file)*/
    int file_checker(FILE *fp)
    {   
        if (fp == NULL)
	    {
		    printf("Cannot open file!\n");
		    return 1;
	    }
    }
/*function name:counter
  purpose:count how many characters from ',' to ',' in each line
  usage:counter(arryname,startpoint)*/
    int counter(char *a,int n)
    {  
        int m=0;
        for (int j = n; ; j++)//before the nth char is part A
            {
                if (a[j]!=',')
                    m++;
                else
                    break;
            }
        return m;
    }
/*function name:row_counter
  purpose:count how many rows in file and then rewind fp 
  usage:row_counter(pointer of file)*/
    int row_counter(FILE *fp)
    {  
        int row=0;
        char examiner;
	    while (!feof(fp))//note:feof(fp); reading file ends
	    {
		    examiner = fgetc(fp);
		    if (examiner == '\n') 
			    row++;
        
	    }
        rewind(fp);//reset the fp to sturecord
        return row;
    }

int main(){
    char a[100];
    FILE *fp_record;
    fp_record=fopen("records.txt","r");
    file_checker(fp_record);

    char b[100];
    FILE *fp_stu;
    fp_stu=fopen("stu.txt","r");
    file_checker(fp_stu);

// creat a struct with number of row
   int row_record;
    row_record=row_counter(fp_record);
	struct student *sturecord = NULL;
	sturecord= (struct student*)malloc(sizeof(struct student)*(row_record)); // creat a struct with number of row

    int row_stu;
    row_stu=row_counter(fp_stu);

//get data from  records.txt
	for (int i = -1; i <= row_record; i++)//omit the title
	{
		fgets(a, 100, fp_record); //each read by one line
        //now each line format:     101,C Programming,41
        //                     =>part A,     part B  ,part C
        
        sscanf(a,"%d",&sturecord[i].subject.stuno1);//put partA into stuno1


        
        int charcounter=0;
        char tempscore[1][2]={'0','0'};
        charcounter=counter(a,4);
        strncpy(sturecord[i].subject.cname,a+4,charcounter);//put partB into cname  note:strncpy(destination,source+startpoint,length);
        strncpy(tempscore,a+4+charcounter+1,2);//put part C into tempscore
        sturecord[i].subject.score=((tempscore[0][0]-48)*10+tempscore[0][1]-48);// convert char tempscore to int score 
    }
   fclose(fp_record);

//get data from stu.txt
   Q1readstu(sturecord,b,row_stu,fp_stu);

//rank basing on age
   Q2sortbyage(sturecord,row_stu);


// output the data student-age
    printf("the ranked student-age data:\n");
    printf("name     age\n");
    for (int i = 0; i < row_stu; i++)
        {
            printf("%s %s%5d\n",sturecord[i].fname,sturecord[i].lname,sturecord[i].age);//print data
        }
//rank basing on scores
    Q3sortbyscore(sturecord,row_record);    

// output the data  subject-scores
    printf("the ranked subject-scores data:\n");
    printf("stuno   score  subject\n");
    for(int j=0;j<row_record;j++)
        {   //print data
            printf("%d     %d     ", sturecord[j].subject.stuno1,  sturecord[j].subject.score);
            puts(sturecord[j].subject.cname);
        }
//caculate the average of c programming
    //put all the cprogramming score into 1 arry
    int x=0;
    struct student Cprogram[30];
    for (int i = 0; i < row_record; i++)
    {
        if (strcmp(sturecord[i].subject.cname,"C Programming")==0)
        {
            
            Cprogram[x]=sturecord[i];
            x++;
        }
    }
    
    float average=Q4avsc_cacul(Cprogram,x);//caculate average score
    printf("AVG of C programming is:%.2f\n",average);//output on the screen
    
//remark each score
    Q5remarkscore(sturecord,row_record);
//output the data into 1944419.txt
    printf("writing the score-remarks into 1944419.txt...\n");
    FILE *fp_nrecord;
    fp_nrecord=fopen("1944419.txt","r");
    if (fp_nrecord!=NULL)//check whether the file has been exist
        printf("Faild:file has existed,please delete it\n");
    else   
        {   fp_nrecord=fopen("1944419.txt","w");//create new file
            fprintf(fp_nrecord,"C programming Score\nstuno     score     cname     \n");//print title
            for (int i = 0; i < row_record; i++)
            {
                fprintf(fp_nrecord,"%d    %5d     %s     %s\n",sturecord[i].subject.stuno1,sturecord[i].subject.score,sturecord[i].subject.cname,sturecord[i].subject.remark);//print data
            }
            printf("Done!\n");
        }
    fclose(fp_nrecord);    
  
    

  
     
     

return 0;}