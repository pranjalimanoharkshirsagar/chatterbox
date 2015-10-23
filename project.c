#include<stdio.h>
//#include<conio.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


//#include<unistd.h>
struct student {
	int roll_no;
	char name[100];
};

int main(){
	
	int ch, i, roll_no;
	char standard[100];
	int num_of_absent_stud=0;
	//int m;
	//int student_count=0;
	char division[100];
	char absent_nos[1024];	
	int exit1,exit2;
	char standard_dir[1024] = "attend/",stud_name[1024],standard_division_student_record_dir[1024];
	char standard_division_dir[1024],student_record_file_path[100],standard_division_att_dir[1024];
	//int m;	
	time_t now;
	struct tm *d;
	char li[13], buffer[2056],user_entered_date[1024],user_entered_date1[1024],standard_division_att_dir_temp[1024];

	
	char student_att_file_path[1024];
	struct stat st = {0};
	//struct student stud[100];
	FILE *fp=NULL;

	//clrscr();

	printf("\t\t\tWelcome to Attendance management System\n\n");

	//firstly accept the standard and the division
	printf("Enter the Standard \n");
	scanf("%s",standard);
	//get(standard);	
	printf("Enter the division \n");
	scanf("%s",division);
	
	printf("Standard:-%s\n",standard);
	printf("Division:-%s\n",division);
	//check for the directory "attendance" if not present then create
	//int    stat(const char *restrict, struct stat *restrict);
	if(stat("attend", &st)==-1){
		mkdir("attend",0700);
	}

	//create a directory for standard and division
	strcat(standard_dir,standard);
	if(stat(standard_dir, &st)==-1){
		mkdir(standard_dir, 0700);
	}

	strcat(standard_division_dir,standard_dir);
	strcat(standard_division_dir,"/");
	strcat(standard_division_dir,division);
	printf("%s",standard_division_dir);
	if(stat(standard_division_dir, &st)==-1){
		mkdir(standard_division_dir,0700);
	}

	//dir path for attedance txt
	strcat(standard_division_att_dir,standard_division_dir);
	strcat(standard_division_att_dir,"/");
	strcat(standard_division_att_dir,"attlog");
	printf("%s",standard_division_att_dir);
	if(stat(standard_division_att_dir, &st)==-1){
		mkdir(standard_division_att_dir,0700);
	}
	
	time(&now);
	d = localtime(&now);
	strftime(li, 15, "%d-%m-%Y", d);
	
	strcpy(student_att_file_path, standard_division_att_dir);
	strcat(student_att_file_path,"/");	
	strcat(student_att_file_path,li);
	strcat(student_att_file_path,".txt");

	//create student record dir and in that create the txt file student record
	strcpy(standard_division_student_record_dir, standard_division_dir);
	strcat(standard_division_student_record_dir,"/student");
	printf("\n%s",standard_division_student_record_dir);
	if(stat(standard_division_student_record_dir, &st)==-1){
		mkdir(standard_division_student_record_dir,0700);
	}
	strcpy(student_record_file_path, standard_division_student_record_dir);
	strcat(student_record_file_path,"/studrec.txt");

	//take the user choice
	do{
	printf("\nEnter your Choice\n");
	printf("\t 1 - Add student records\n \t 2 - Take Attendance \n \t3 - View todays Attendance \n \t4 - View by date\n\t");
	scanf("%d",&ch);
	switch(ch){
		case 1:
			fp = fopen(student_record_file_path,"w+");
			do{
				printf("\n\tEnter the roll no :: ");
				scanf("%d",&roll_no);
				printf("\n\tEnter the name :: ");
				scanf("%s",stud_name);
				//stud[student_count].roll_no = roll_no;
				//strcpy(stud[student_count].name, stud_name);
				//student_count++;
				fprintf(fp, "%d,%s\n",roll_no, stud_name);
				printf("\n\tDo you want to continue (1/0)??");
				scanf("%d",&exit1);
				printf("%d",exit1);
			}while(exit1==1);

			//for(i=0;i<student_count;i++){

			//}
			fclose(fp);
			break;

		case 2:
		       printf("\n\tEnter Comma Seperated Absent roll nos :: \n");
		       scanf("%s",absent_nos);
			//fgets(absent_nos,1024, stdin);
			//printf("%s",absent_nos);
		       fp = fopen(student_att_file_path,"w+");

		       fprintf(fp, "%s\n", absent_nos);

		       fclose(fp);
		       break;
		case 3:
			fp = fopen(student_att_file_path,"r+");
			
		       fread(buffer, 1,2056, fp);
			printf("--%s\n",buffer);			
			for(i=0;i<2056;i++){
				if(buffer[i]==','){
					num_of_absent_stud++;
				}
				//buffer[i]='\0';
			}
			if(fp!=NULL && strlen(buffer)>0){
				num_of_absent_stud++;				
			}
			
			
		        fclose(fp);
			printf("Number of student absent on %s - %d", li,num_of_absent_stud);
			num_of_absent_stud =0;
		case 4:
			printf("Enter the date in dd-mm-yyyy format");
			scanf("%s",user_entered_date);	
			strcat(standard_division_att_dir_temp,standard_division_att_dir);
			strcat(standard_division_att_dir_temp,"/");
			strcat(user_entered_date1,user_entered_date);			
			strcat(user_entered_date,".txt");
			strcat(standard_division_att_dir_temp,user_entered_date);
			printf("**%s**\n",standard_division_att_dir_temp);
			fp = fopen(standard_division_att_dir_temp,"r+");
			 
		        fread(buffer, 1,2056, fp);
			printf("--%s\n",buffer);			
			for(i=0;i<2056;i++){
				if(buffer[i]==','){
					num_of_absent_stud++;
				}
				//buffer[i]='\0';
			}
			if(fp!=NULL && strlen(buffer)>0){
				num_of_absent_stud++;				
			}
			
			
		       fclose(fp);
			printf("Number of student absent on %s - %d", user_entered_date1,num_of_absent_stud);
			num_of_absent_stud =0; 
	}
	printf("\n\tDo you want to continue (1/0)??");
	scanf("%d",&exit2);
	}while(exit2 == 1);

	return 0;
	//getch();




}
