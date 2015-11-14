/*****************************************************************************
* This file is Student Attendance System.
*
* Student Attendance System is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Foobar is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Student Attendance System. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/
#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct student {
	char roll_no[100];
	char name[1024];
};

void main(){
	
	//variable decalaration
	int ch,student_count=0, i,set_str_flag=0; 
	int roll_no,roll_no_string_count=0,flag_absent=0;
	int student_record_count=0,current_field=0;
	int i1,num_of_absent_stud=0,found_flag=0;
	int exit1,exit2;

	char standard[100];	
	char division[100];
	char absent_nos[1024];	
	char standard_dir[1024] = "attend/",stud_name[1024],standard_division_student_record_dir[1024];
	char standard_division_dir[1024],student_record_file_path[100],standard_division_att_dir[1024];
	char roll_no_string[2056],roll_no_string_1[2056];
	char roll_no_string1[100],roll_no_string2[100],roll_no_string3[100],roll_no_string4[100],roll_no_string5[100];
	char roll_no_string6[100],roll_no_string7[100];
	char li[13], buffer1[4000], buffer[2056],user_entered_roll[1024],buffer_edit[4000],buffer_delete[4000],buffer_view[4000];
	char user_entered_date[1024],user_entered_date1[1024],standard_division_att_dir_temp[1024];
	char student_att_file_path[1024],buffer_4[4000],buffer_5[4000];
	char possible_std[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char user_entered_name[2056],user_entered_standard[2056],student_att_file_path_for_std[2056];
	char user_entered_division[2056], cmd[2056];
	char user_entered_year[2056],current_year[2056],li1[13],this_year_his_path[2056];	
	char restore_year[100] = "0000";
	char year_archive_choice[2056];
	char restore_this_year[2056],user_entered_roll_no[100];
	
	int m;	
	time_t now;

	struct tm *d;
	struct stat st = {0};
	struct student stud[100],student_record_struct[200],student_record_struct_edit[200];
	struct student student_record_struct_delete[200],student_record_struct_view[200];
	FILE *fp=NULL;
 
	printf("\t\t\tWelcome to Attendance management System\n\n");

	//firstly accept the standard and the division
	printf("Enter the Standard \n");
	scanf("%s",standard);

	//get(standard);	
	printf("Enter the division \n");
	scanf("%s",division);
	
 	//check for the directory "attend" if not present then create
	if(stat("attend", &st)==-1){
		mkdir("attend",0700);
	}

	//check for the directory "history" if not present then create
	if(stat("history", &st)==-1){
		mkdir("history",0700);
	}

	//create a directory for standard and division
	strcat(standard_dir,standard);
	if(stat(standard_dir, &st)==-1){
		mkdir(standard_dir, 0700);
	}

	strcat(standard_division_dir,standard_dir);
	strcat(standard_division_dir,"/");
	strcat(standard_division_dir,division);
	
	if(stat(standard_division_dir, &st)==-1){
		mkdir(standard_division_dir,0700);
	}

	//dir path for attedance txt
	strcat(standard_division_att_dir,standard_division_dir);
	strcat(standard_division_att_dir,"/");
	strcat(standard_division_att_dir,"attlog");
	
	if(stat(standard_division_att_dir, &st)==-1){
		mkdir(standard_division_att_dir,0700);
	}
	
	//store todays date
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
	
	if(stat(standard_division_student_record_dir, &st)==-1){
		mkdir(standard_division_student_record_dir,0700);
	}
	strcpy(student_record_file_path, standard_division_student_record_dir);
	strcat(student_record_file_path,"/studrec.txt");

	//take the user choice
	do{

	printf("\nEnter your Choice\n");
	printf("\t 1 - Add student records \n\t 2 - Take Attendance \n\t 3 - View todays Attendance \n\t 4 - View attendance by date \n\t 5 - View attendance by student roll no \n\t 6 - View attendance by student name \n\t 7 - View attendance by Standard \n\t 8 - View attendance by Division \n\t 9 - Archive this year \n\t 10 - Restore a Year \n\t 11 - Edit Student Record \n\t 12 - Delete Student Record \n\t 13 - View Student Record\n\t");
	scanf("%d",&ch);

	switch(ch){

		case 1:
			//add student entry to file

			fp = fopen(student_record_file_path,"a+");
			do{
				printf("\n\tEnter the roll no :: ");
				scanf("%d",&roll_no);
				printf("\n\tEnter the name :: ");
				scanf("%s",stud_name);

				fprintf(fp, "%d,%s\n",roll_no, stud_name);
				printf("\n\tDo you want to continue with  inserting the student entries (1/0)??");
				scanf("%d",&exit1);

			}while(exit1==1);
 
			fclose(fp);
			break;
 
		case 2:
			//take absent roll nos and set in file
		       printf("\n\tEnter Comma Seperated Absent roll nos :: \n");
		       scanf("%s",absent_nos);
		
		       fp = fopen(student_att_file_path,"w+");
		       fprintf(fp, "%s\n", absent_nos);
		       fclose(fp);

		       break;

		case 3:

		       fp = fopen(student_att_file_path,"r+");
		       fread(buffer, 1,2056, fp);
		      //cal # absent students
		       for(i=0;i<2056;i++){
				if(buffer[i]==','){
					num_of_absent_stud++;
				}
			}
			
			if(fp!=NULL && strlen(buffer)>0){
				num_of_absent_stud++;				
			}
			
		        fclose(fp);
		
			printf("\nNumber of student absent on %s - %d", li,num_of_absent_stud);
			printf("\nRoll Nos. of absent student(s) on %s are %s", li,buffer);
			num_of_absent_stud =0;
			memset(&buffer[0],0,sizeof(buffer));

			break;

		case 4:

			printf("Enter the date in dd-mm-yyyy format");
			scanf("%s",user_entered_date);	
			
			num_of_absent_stud = 0;

			//set the path of the file as per date
			strcat(standard_division_att_dir_temp,standard_division_att_dir);
			strcat(standard_division_att_dir_temp,"/");
			strcat(user_entered_date1,user_entered_date);			
			strcat(user_entered_date,".txt");
			strcat(standard_division_att_dir_temp,user_entered_date);

			fp = fopen(standard_division_att_dir_temp,"r+");
			fread(buffer_4, 1,2056, fp);
			printf("%s",buffer_4);
			//read and cal the # absent students
			for(i=0;i<2056;i++){
				if(buffer_4[i]==','){
					num_of_absent_stud++;
				}
			}

			if(fp!=NULL && strlen(buffer_4)>0){
				num_of_absent_stud++;				
			}
			
			
		       fclose(fp);
		       
		       printf("\nNumber of student absent on %s - %d", user_entered_date1,num_of_absent_stud);
		       printf("\nRoll nos of students absent on %s - %s", user_entered_date1,buffer_4);	

		       num_of_absent_stud =0;
			memset(&standard_division_att_dir_temp,0,sizeof(standard_division_att_dir_temp));
		       break;

		case 5:

			printf("Enter the roll number");
			scanf("%s",user_entered_roll);				
			printf("Enter the date in dd-mm-yyyy format");
			scanf("%s",user_entered_date);	
			

			strcat(standard_division_att_dir_temp,standard_division_att_dir);
			strcat(standard_division_att_dir_temp,"/");
			strcpy(user_entered_date1,user_entered_date);			
			strcat(user_entered_date,".txt");
			strcat(standard_division_att_dir_temp,user_entered_date);
			
			fp = fopen(standard_division_att_dir_temp,"r+");
			fread(buffer_5, 1,4000, fp);

			for(i=0;i<4000;i++){
				if(buffer_5[i]==','){
					if(strcmp(user_entered_roll,roll_no_string)==0){
						flag_absent = 1;						
						break;
					}
					roll_no_string_count = 0;
				}
				if(buffer_5[i]!=',' && buffer_5[i]!=' ' && buffer_5[i]!='\0' && buffer_5[i]!='\n'){
					roll_no_string[roll_no_string_count++]=buffer_5[i];
				}
			}
			
			if(strcmp(user_entered_roll,roll_no_string)==0){
				flag_absent = 1;						
			}
			
			if(flag_absent==1){
			printf("\nRoll no  %s was absent on %s",user_entered_roll,user_entered_date1);				
			}else{
			printf("\nRoll no  %s was present on %s",user_entered_roll,user_entered_date1);
			}
			memset(&standard_division_att_dir_temp,0,sizeof(standard_division_att_dir_temp));
			break;	

		case 6:

			fp = fopen(student_record_file_path,"r+");
         		roll_no_string_count=0;
		        fread(buffer1, 1,4000, fp);
			student_record_count = 0;
			current_field = 0;

			for(i=0;i<4000;i++){
				
				if(buffer1[i]==',' || buffer1[i]=='\n'){

					current_field++;
					if(current_field==1){
						strcpy(student_record_struct[student_record_count].roll_no,roll_no_string1);
					}else{
						strcpy(student_record_struct[student_record_count].name,roll_no_string);
						current_field = 0;
					}
					
					roll_no_string_count=0;
					roll_no_string[roll_no_string_count] = '\0';
					strcpy(roll_no_string,"");
					memset(&roll_no_string1[0], 0, sizeof(roll_no_string1));
					memset(&roll_no_string[0], 0, sizeof(roll_no_string));

					
				}

				if(buffer1[i]!=',' && buffer1[i]!='\n'&& buffer1[i]!=' '){
					if(current_field==0){					
						roll_no_string1[roll_no_string_count++]=buffer1[i];
					}else{
						roll_no_string[roll_no_string_count++]=buffer1[i];
					}
				}
				
				if(buffer1[i]=='\n'){
					student_record_count++;
				}

			}

			printf("Enter the name of the student");
			scanf("%s",user_entered_name);				
			printf("Enter the date in dd-mm-yyyy format");
			scanf("%s",user_entered_date);				
		 
			for(i=0;i<student_record_count;i++){
				if(strcmp(user_entered_name,student_record_struct[i].name)==0){
					strcpy(user_entered_roll,student_record_struct[i].roll_no);
				}
			}
			 
			strcat(standard_division_att_dir_temp,standard_division_att_dir);
			strcat(standard_division_att_dir_temp,"/");
			strcpy(user_entered_date1,user_entered_date);			
			strcat(user_entered_date,".txt");
			strcat(standard_division_att_dir_temp,user_entered_date);
						 
			fclose(fp);
			fp = fopen(standard_division_att_dir_temp,"r+");
		        fread(buffer, 1,2056, fp);

			roll_no_string_count = 0;

			for(i=0;i<2056;i++){

				if(buffer[i]==','){

					if(strcmp(user_entered_roll,roll_no_string_1)==0){
						flag_absent = 1;						
						break;
					}
					roll_no_string_count = 0;
				}

				if(buffer[i]!=',' && buffer[i]!=' ' && buffer[i]!='\0' && buffer[i]!='\n'){
					roll_no_string_1[roll_no_string_count++]=buffer[i];
				}
			}
			
			if(strcmp(user_entered_roll,roll_no_string)==0){
				flag_absent = 1;						
			}
			
			if(flag_absent==1){
			printf("\nRoll no  %s was absent on %s",user_entered_roll,user_entered_date1);				
			}else{
			printf("\nRoll no  %s was present on %s",user_entered_roll,user_entered_date1);
			}

			break;
	
	 	case 7:

			printf("Enter the standard");
			scanf("%s",user_entered_standard);
			printf("Enter the date in dd-mm-yyyy format");
			scanf("%s",user_entered_date);
			
			num_of_absent_stud =0;
			
			for(m=0;m<26;m++){
				
				strcpy(student_att_file_path_for_std,"attend/");
				strcat(student_att_file_path_for_std,user_entered_standard);
				strcat(student_att_file_path_for_std,"/");

				student_att_file_path_for_std[strlen(student_att_file_path_for_std)] = possible_std[m];
				
				if(stat(student_att_file_path_for_std, &st)!=-1){
					
					if(set_str_flag==0){	
						strcat(student_att_file_path_for_std,"/attlog/");
						strcpy(user_entered_date1,user_entered_date);
						strcat(user_entered_date,".txt");			
					        strcat(student_att_file_path_for_std,user_entered_date);	
						set_str_flag=1;
					}
		
					fp = fopen(student_att_file_path_for_std,"r+");

					if(fp!=NULL){
						fread(buffer, 1,2056, fp);			
						for(i=0;i<2056;i++){
							if(buffer[i]==','){
								num_of_absent_stud++;
							}
						}

						if(fp!=NULL && strlen(buffer)>0){
							num_of_absent_stud++;				
						}
		
						fclose(fp);
						printf("\nNumber of student absent in Division %c on %s = %d\n", possible_std[m], user_entered_date1,num_of_absent_stud);
						num_of_absent_stud =0;
					}

				}
				strcpy(student_att_file_path_for_std,"");	
			}
			break;
			
	 	case 8:

			printf("Enter the standard");
			scanf("%s",user_entered_standard);
			
			printf("Enter the division");
			scanf("%s",user_entered_division);
			
			printf("Enter the date in dd-mm-yyyy format");
			scanf("%s",user_entered_date);
			
			num_of_absent_stud =0;
			set_str_flag = 0;
						
			strcpy(student_att_file_path_for_std,"attend/");
			strcat(student_att_file_path_for_std,user_entered_standard);
			strcat(student_att_file_path_for_std,"/");

			strcat(student_att_file_path_for_std,user_entered_division);
			 	
			if(stat(student_att_file_path_for_std, &st)!=-1){

				if(set_str_flag==0){	

					strcat(student_att_file_path_for_std,"/attlog/");
					strcpy(user_entered_date1,user_entered_date);
					strcat(user_entered_date,".txt");			
			        	strcat(student_att_file_path_for_std,user_entered_date);	
					set_str_flag=1;

				}		

				fp = fopen(student_att_file_path_for_std,"r+");

				if(fp!=NULL){

					fread(buffer, 1,2056, fp);

					for(i=0;i<2056;i++){
						if(buffer[i]==','){
							num_of_absent_stud++;
						}

					}

					if(fp!=NULL && strlen(buffer)>0){
						num_of_absent_stud++;				
					}
		
					fclose(fp);
					printf("\n\nNumber of student absent in Division %s on %s = %d", user_entered_division, user_entered_date1,num_of_absent_stud);
					num_of_absent_stud =0;
				}
			}
			strcpy(student_att_file_path_for_std,"");	

			break;
		case 9:

			time(&now);
			d = localtime(&now);
			strftime(li1, 15, "%Y", d);
	
			strcpy(this_year_his_path, "history/");
			
			if(strcmp(restore_year,"0000")==0 || strcmp(restore_year,"")==0){			
				strcat(this_year_his_path, li1);
			}else{
				strcat(this_year_his_path, restore_year);
			}
			//printf("---%s---\n",restore_year);			
			//printf("---%s---\n",this_year_his_path);
			//check for the directory "history" if not present then create
			if(stat(this_year_his_path, &st)==-1){
				mkdir(this_year_his_path,0700);
			}

			strcpy(cmd," cp -a attend ");
			strcat(cmd, this_year_his_path);
			
			system(cmd);
			system("rm -r attend");
			
			if(strcmp(restore_year,"0000")==0 || strcmp(restore_year,"")==0){			
				printf("Year %s archived successfully",li1);
			}else{
				printf("Year %s archived successfully",restore_year);
			}
			break;						
		
		case 10:

			printf("Did you archive the current year (y/n)??");
			scanf("%s",year_archive_choice);
			
			if(strcmp(year_archive_choice,"y")==0){
			
				if(stat("attend", &st)==-1){
			
					printf("Enter the year(yyyy) to restore");
					scanf("%s", restore_year);
			
					strcpy(restore_this_year, "history/");
					strcat(restore_this_year, restore_year);
					strcat(restore_this_year, "/attend");
			
					strcpy(cmd, "");
					strcpy(cmd," cp -a ");
					strcat(cmd, restore_this_year);
					strcat(cmd, " attend");								

					system(cmd);
					printf("\n\nProgram will exit now, do start again and perform operartion on year %s \n\n", restore_year);
					exit(0);
				}else{
				printf("\nBefore proceeding with the restore option archive the current year using 9 option...\n\n");
				}
			}else{
				printf("\nBefore proceeding with the restore option archive the current year using 9 option...\n\n");
		
			}
			
			break;
		
		case 11:
			//edit student record
			
			fp = fopen(student_record_file_path,"r+");
			fread(buffer_edit, 1,4000, fp);
			student_record_count = 0;
			roll_no_string_count=0;
			current_field=0;
			
			for(i=0;i<4000;i++){
			
				if(buffer_edit[i]==',' || buffer_edit[i]=='\n'){
					current_field++;

					//store the name and roll no in struct
					if(current_field==1){
						strcpy(student_record_struct_edit[student_record_count].roll_no,roll_no_string2);
					}else{
						strcpy(student_record_struct_edit[student_record_count].name,roll_no_string3);
						current_field = 0;
					}
					
					//empty the previous string and reset the counters
					roll_no_string_count=0;
					roll_no_string[roll_no_string_count] = '\0';
					strcpy(roll_no_string,"");
					memset(&roll_no_string2[0], 0, sizeof(roll_no_string2));
					memset(&roll_no_string3[0], 0, sizeof(roll_no_string3));

			
				}

				if(buffer_edit[i]!=',' && buffer_edit[i]!='\n'&& buffer_edit[i]!=' '){
					if(current_field==0){					
						roll_no_string2[roll_no_string_count++]=buffer_edit[i];
					}else{
						roll_no_string3[roll_no_string_count++]=buffer_edit[i];
					}
				}
				
				if(buffer_edit[i]=='\n'){
					student_record_count++;
				}

			}
			printf("Enter roll no of student to edit");
			scanf("%s",user_entered_roll_no);
			found_flag = 0;
			fclose(fp);

			for(i=0;i<student_record_count;i++){
				if(strcmp(user_entered_roll_no,student_record_struct_edit[i].roll_no)==0){
					printf("Enter the new roll no :: ");
					scanf("%s",student_record_struct_edit[i].roll_no);
					printf("Enter the name :: ");
					scanf("%s",student_record_struct_edit[i].name);
					found_flag = 1;
				}
 	 		}

			if(found_flag==0){
				printf("\nRecord not found\n");
			}

			if(found_flag==1){
				fp = fopen(student_record_file_path,"w+");
				for(i=0;i<student_record_count;i++){
					if(strcmp(student_record_struct_edit[i].roll_no,"")!=0){
						fprintf(fp, "%s,%s\n",student_record_struct_edit[i].roll_no, student_record_struct_edit[i].name);
					}
				} 
				printf("\n\tRecorded Updated Successfully\n");
	 		}
			fclose(fp);
			break;
			
		case 12:
			//delete student record
			
			fp = fopen(student_record_file_path,"r+");
			fread(buffer_delete, 1,4000, fp);
			student_record_count = 0;
			roll_no_string_count=0;
			current_field=0;

			for(i=0;i<4000;i++){

				if(buffer_delete[i]==',' || buffer_delete[i]=='\n'){
					current_field++;
				
					//store the name and roll no in struct
					if(current_field==1){
						strcpy(student_record_struct_delete[student_record_count].roll_no,roll_no_string4);
					}else{
						strcpy(student_record_struct_delete[student_record_count].name,roll_no_string5);
						current_field = 0;
					}
					
					//empty the previous string and reset the counters
					roll_no_string_count=0;
					roll_no_string[roll_no_string_count] = '\0';
					strcpy(roll_no_string4,"");
					strcpy(roll_no_string5,"");
					memset(&roll_no_string4[0], 0, sizeof(roll_no_string4));
					memset(&roll_no_string5[0], 0, sizeof(roll_no_string5));


				}

				if(buffer_delete[i]!=',' && buffer_delete[i]!='\n'&& buffer_delete[i]!=' '){
					if(current_field==0){					
						roll_no_string4[roll_no_string_count++]=buffer_delete[i];
					}else{
						roll_no_string5[roll_no_string_count++]=buffer_delete[i];
					}
				}
				
				if(buffer_delete[i]=='\n'){
					student_record_count++;
				}

			}

			printf("Enter roll no of student to delete");
			scanf("%s",user_entered_roll_no);
			found_flag = 0;
			fclose(fp);

			for(i=0;i<student_record_count;i++){
				if(strcmp(user_entered_roll_no,student_record_struct_delete[i].roll_no)==0){
					strcpy(student_record_struct_delete[i].roll_no,"");
					found_flag = 1;
				}
 	 		}

			if(found_flag==0){
				printf("\nRecord not found\n");
			}
			
			if(found_flag==1){
				
				fp = fopen(student_record_file_path,"w+");
				for(i=0;i<student_record_count;i++){
					if(strcmp(student_record_struct_delete[i].roll_no,"")!=0){
						fprintf(fp, "%s,%s\n",student_record_struct_delete[i].roll_no, student_record_struct_delete[i].name);
					}
					} 
				printf("\n\tRecorded Deleted Successfully\n");
	 		}
 
			fclose(fp);
			break;
		case 13:
			//view student record
			
			fp = fopen(student_record_file_path,"r+");
			fread(buffer_view, 1,4000, fp);
			student_record_count = 0;
			roll_no_string_count = 0;
			current_field=0;

			for(i=0;i<4000;i++){

				if(buffer_view[i]==',' || buffer_view[i]=='\n'){
					current_field++;
				
					//store the name and roll no in struct
					if(current_field==1){

						strcpy(student_record_struct_view[student_record_count].roll_no,roll_no_string6);
					}else{
						
						strcpy(student_record_struct_view[student_record_count].name,roll_no_string7);
						current_field = 0;
					}
					
					//empty the previous string and reset the counters
					roll_no_string_count=0;
					roll_no_string7[roll_no_string_count] = '\0';
					roll_no_string6[roll_no_string_count] = '\0';
					strcpy(roll_no_string6,"");
					strcpy(roll_no_string7,"");
					memset(&roll_no_string6[0], 0, sizeof(roll_no_string6));
					memset(&roll_no_string7[0], 0, sizeof(roll_no_string7));
					printf("--%s--",roll_no_string7);
				}

				if(buffer_view[i]!=',' && buffer_view[i]!='\n'&& buffer_view[i]!=' '){
					if(current_field==0){					
						roll_no_string6[roll_no_string_count++]=buffer_view[i];
					}else{
						roll_no_string7[roll_no_string_count++]=buffer_view[i];
					}
				}
				
				if(buffer_view[i]=='\n'){
					student_record_count++;
				}

			}

			printf("\n\n-----------------  Student Records ---------------------");					
			printf("\n\t Standard - %s",standard);
			printf("\n\t Division - %s",division);
			printf("\n\n\tRoll No    Student Name \n\t");
			printf("------------------------------------------\n");		
			found_flag = 0;		
			for(i=0;i<student_record_count;i++){
				if(strcmp(student_record_struct_view[i].roll_no,"")!=0){
			printf("\t  %s        %s\n",student_record_struct_view[i].roll_no,student_record_struct_view[i].name);		
					found_flag = 1;
				}
 	 		}
			if(found_flag == 0 ){
				printf("\nNo Records Found\n");
			}
			fclose(fp);
			memset(&buffer_view[0],0,sizeof(buffer_view));
			break;
		}
	printf("\n\tDo you want to continue (1/0)??");
	scanf("%d",&exit2);
	}while(exit2 == 1);

}	


