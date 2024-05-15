#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX_STUDENT 100

#define TRUE 1
#define FALSE 0

int isValidID(int id){
    return id>0;
}

int isValidName(const char name[]){
    if(strlen(name)>0 && strlen(name)<=50){
        for(int i=0; name[i]!='\0'; i++){
            if(!isalpha(name[i])){
                return 0;
            }
        }
        return 1;
    }
}

int isValidPhoneNumber(const char phoneNumber[]){
    if(strlen(phoneNumber)>0 && strlen(phoneNumber)<=15){
        for(int i=0; phoneNumber[i] !='\0'; i++){
            if(!isdigit(phoneNumber[i])){
               return 0;
            }
        }
        return 1;
    }
}

int isValidMarks(int marks){
    return marks>=1 && marks<=100;
}

void saveStudentToFile(const char filename[], const int ids[], const char names[][50], const char phoneNumber[][15], const int assignmentMarks[], const int midtermMarks[], const int finalexamMarks[], int numStudents){
    FILE*file=fopen(filename,"w");
    if(file==NULL){
        printf("Error opening file.\n");
        return;
    }
    fprintf(file,"%d\n",numStudents);
    for(int i=0; i< numStudents; i++){
        fprintf(file,"%d %s %s %d %d %d\n", ids[i],names[i],phoneNumber[i],assignmentMarks[i],midtermMarks[i],finalexamMarks[i]);
    }
    fclose(file);
    printf("Student information saved to file: %s\n",filename);
}

void addStudent(int ids[], char names[][50], char phoneNumber[][15],int assignmentMarks[], int midtermMarks[], int finalexamMarks[], int*numStudents){
    int id, assignmentMarksVal, midtermMarksVal, finalexamMarksVal;
    char name[50],phone[15];
    do{
        printf("Please enter ID:");
        if(scanf("%d",&id)!=1 || id<=0){
           printf("Invalid input.Please enter a positive integer for ID.\n");
           while(getchar()!='\n');
       }else{
           break;
       }
    }while(1);

    do{
        printf("Please enter student name (up to 50 characters):");
        scanf("%s",name);
        if(!isValidName(name)){
            printf("Invalid name.Please enter a name with at most 50 characters.\n");
        }else{
            break;
        }
    }while(1);

    do{
        printf("Please enter phone number (up to 15 characters):");
        scanf("%s",phone);
        if(!isValidPhoneNumber(phone)){
            printf("Invalid phone number.Please enter a phone number with at most 15 characters.\n");
        }else{
            break;
        }
    }while(1);

    do{
        printf("Please enter student's Assignment marks (1-100):");
        if(scanf("%d",&assignmentMarksVal)!=1 || !isValidMarks(assignmentMarksVal)){
            printf("Invalid input.Please enter an integer between 1 and 100 for Assignment Marks.");
            while(getchar()!='\n');
        }else{
            break;
        }
    }while(1);

    do{
        printf("Please enter student's Midterm marks (1-100):");
        if(scanf("%d",&midtermMarksVal)!=1 || !isValidMarks(midtermMarksVal)){
            printf("Invalid input.Please enter an integer between 1 and 100 for Midterm Marks.");
            while(getchar()!='\n');
        }else{
            break;
        }
    }while(1);

    do{
        printf("Please enter student's Final exam marks (1-100):");
        if(scanf("%d",&finalexamMarksVal)!=1 || !isValidMarks(finalexamMarksVal)){
            printf("Invalid input.Please enter an integer between 1 and 100 for final exam Marks.");
            while(getchar()!='\n');
        }else{
            break;
        }
    }while(1);

    ids[*numStudents]=id;
    strcpy(names[*numStudents],name);
    strcpy(phoneNumber[*numStudents],phone);
    assignmentMarks[*numStudents]=assignmentMarksVal;
    midtermMarks[*numStudents]=midtermMarksVal;
    finalexamMarks[*numStudents]=finalexamMarksVal;

    printf("Student added successfully.\n");
    (*numStudents)++;

    printf("Do you want to save student information to a file? (1=Yes,0=No):");
    int saveOption;
    scanf("%d",&saveOption);
    if(saveOption==1){
        saveStudentToFile("student_data.txt",ids,names,phoneNumber,assignmentMarks,midtermMarks,finalexamMarks,*numStudents);
    }
}

int readStudentFromFile(const char filename[],int searchID){
    FILE*file=fopen(filename,"r");
    if(file==NULL){
        printf("Error opening file.\n");
        return FALSE;
    }
     int numStudents;
     fscanf(file,"%d",&numStudents);

     for(int i=0; i<numStudents; i++){
        int id;
        char name[50];
        char phone[15];
        int assignmentMarks,midtermMarks,finalexamMarks;

        fscanf(file,"%d %50s %15s %d %d %d",&id, name,phone,&assignmentMarks,&midtermMarks,&finalexamMarks);

        if(id==searchID){
            printf("Student found:\n");
            printf("ID:%d\n",id);
            printf("Name:%s\n",name);
            printf("Phone:%s\n",phone);
            printf("Assignment Marks:%d\n",assignmentMarks);
            printf("Midterm Marks:%d\n",midtermMarks);
            printf("Final Exam Marks:%d\n",finalexamMarks);
            fclose(file);
            return TRUE;
        }
     }
     printf("Student with ID %d not found.\n",searchID);
     fclose(file);
     return FALSE;
}

void searchByID(int ids[], char names[][50], char phoneNumber[][15],int assignmentMarks[], int midtermMarks[], int finalexamMarks[], int numStudents){
    int searchID;
    do{
        printf("Please enter the ID of the student to search:");
        if(scanf("%d",&searchID)!=1 || !isValidID(searchID)){
           printf("Invalid input.Please enter a positive integer for ID.\n");
           while(getchar()!='\n');
        }else{
            break;
        }
    }while(1);

   int found= readStudentFromFile("student_data.txt",searchID);
   if(found){
     printf("Do you want to search for another student? ( 1=Yes, 2=No):");
     int choice;
     scanf("%d",&choice);
     if(choice ==1){
        searchByID(ids,names,phoneNumber,assignmentMarks,midtermMarks,finalexamMarks,numStudents);
        }
    }
}


void calculateTotalMarks(int ids[], char names[][50],int assignmentMarks[], int midtermMarks[], int finalexamMarks[], int numStudents){
    float classtotalMarks=0;
    for(int i=0; i< numStudents; i++){
        if(!isValidMarks(assignmentMarks[i]) || !isValidMarks(midtermMarks[i]) || !isValidMarks(finalexamMarks[i])){
            printf("Invalid marks for students %s (ID: %d). Please enter valid marks (1-100) for all exam.\n",names[i],ids[i]);
            continue;
        }

        float totalMarks= assignmentMarks[i]+midtermMarks[i]+finalexamMarks[i];
        float totalPercentage= totalMarks /3.0;

        printf("Student ID: %d\n ",ids[i]);
        printf("Student Name: %s\n",names[i]);
        printf("Total Marks of assignment(%d %%),midterm (%d %%)and final exam marks (%d %%): %.2f%%\n",assignmentMarks[i],midtermMarks[i],finalexamMarks[i],totalPercentage);
        printf("---------------------------------------------------------------------------------------\n");

        classtotalMarks+=totalMarks;
    }
    printf("Class total marks: %.2f\n",classtotalMarks);
}

void generateGrades( int ids[],char names[][50],char grades[], int assignmentMarks[], int midtermMarks[], int finalexamMarks[], int numStudents){
    printf("---------------------------------------------------------------------------------------\n");
    printf("| %-20s | %-6s | %-15s | %-8s | %-15s | %-5s |\n", "Name", "ID", "AssignmentMarks", "Midterm", "Finalexam Marks", "Grade");
    printf("---------------------------------------------------------------------------------------\n");

    for(int i=0; i <numStudents; i++){
        if(!isValidMarks(assignmentMarks[i]) || !isValidMarks(midtermMarks[i]) || !isValidMarks(finalexamMarks[i])){
            printf("Invalid marks for students %s (ID: %d). Please enter valid marks (1-100) for all exam.\n",names[i],ids[i]);
            continue;
        }
        float totalMarks= assignmentMarks[i]+midtermMarks[i]+finalexamMarks[i];
        float totalPercentage= totalMarks /3.0;

        if(totalPercentage>=80){
            grades[i]='A';
        }else if (totalPercentage>=70){
            grades[i]='B';
        }else if (totalPercentage>=60){
            grades[i]='C';
        }else if (totalPercentage>=50){
            grades[i]='D';
        }else{
            grades[i]='F';
        }
        printf("| %-20s | %-6d | %-15d | %-8d | %-15d | %-5c |\n", names[i], ids[i], assignmentMarks[i], midtermMarks[i], finalexamMarks[i], grades[i]);
        printf("---------------------------------------------------------------------------------------\n");
    }
}


void generateTop5students(int ids[], char names[][50], int assignmentMarks[], int midtermMarks[], int finalexamMarks[], int numStudents) {
    if(numStudents<5){
        printf("There are less than 5 students in the system. Unable to generate  top 5 students.\n");
        return;
    }
    float totalMarks[MAX_STUDENT];
    for (int i = 0; i < numStudents; i++) {
        totalMarks[i] = assignmentMarks[i] + midtermMarks[i] + finalexamMarks[i];
    }
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (totalMarks[j] < totalMarks[j + 1]) {
                float temporarilyMarks = totalMarks[j];
                totalMarks[j] = totalMarks[j + 1];
                totalMarks[j + 1] = temporarilyMarks;

                int temporarilyID = ids[j];
                ids[j] = ids[j + 1];
                ids[j + 1] = temporarilyID;

                char temporarilyNames[50];
                strcpy(temporarilyNames, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temporarilyNames);

                int temporarilyAssignmentMarks = assignmentMarks[j];
                assignmentMarks[j] = assignmentMarks[j + 1];
                assignmentMarks[j + 1] = temporarilyAssignmentMarks;

                int temporarilyMidtermMarks = midtermMarks[j];
                midtermMarks[j] = midtermMarks[j + 1];
                midtermMarks[j + 1] = temporarilyMidtermMarks;

                int temporarilyFinalexamMarks = finalexamMarks[j];
                finalexamMarks[j] = finalexamMarks[j + 1];
                finalexamMarks[j + 1] = temporarilyFinalexamMarks;
            }
        }
    }
    printf("Top 5 students:\n");
    printf("---------------------------------------------------------------------------------------\n");
    printf("| %-20s | %-6s | %-15s | %-8s | %-15s | %-5s |\n", "Name", "ID", "AssignmentMarks", "Midterm", "Finalexam Marks", "Grade");
    printf("---------------------------------------------------------------------------------------\n");
    for (int i = 0; i < 5 && i < numStudents; i++) {
        float totalPercentage = totalMarks[i] / 3.0;
        char grade;
        if (totalPercentage >= 80) {
            grade = 'A';
        } else if (totalPercentage >= 70) {
            grade = 'B';
        } else if (totalPercentage >= 60) {
            grade = 'C';
        } else if (totalPercentage >= 50) {
            grade = 'D';
        } else {
            grade = 'F';
        }
        printf("| %-20s | %-6d | %-15d | %-8d | %-15d | %-5c |\n", names[i], ids[i], assignmentMarks[i], midtermMarks[i], finalexamMarks[i], grade);
        printf("---------------------------------------------------------------------------------------\n");
    }
}

int main(){
    int ids[MAX_STUDENT];
    char names[MAX_STUDENT][50];
    char phoneNumber[MAX_STUDENT][15];
    char grades[MAX_STUDENT]={0};
    int assignmentMarks[MAX_STUDENT];
    int midtermMarks[MAX_STUDENT];
    int finalexamMarks[MAX_STUDENT];
    int numStudents=0;
    int choice;

    printf("Welcome to Student Grade Tracker !!\n");
    printf("---------------------------------------------------------------------------------------\n");

    do{
        printf("\nOptions:\n");
        printf("1. Add student\n");
        printf("2. Search by ID\n");
        printf("3. Calculate Total Marks.\n");
        printf("4. Generate Grades\n");
        printf("5. Generate Top 5 students\n");
        printf("6. Exit\n");
        printf("Please enter your choice:");
        scanf("%d",&choice);

        switch(choice){
        case 1:
            addStudent(ids,names,phoneNumber, assignmentMarks, midtermMarks,finalexamMarks,&numStudents);
            printf("Student added successfully.\n");

            printf("\nStudent Details\n");
            printf("-------------------------------");
            for(int i=0; i < numStudents; i++){
                float assignmentPercentage=(assignmentMarks[i]*30/100);
                float midtermPercentage=(midtermMarks[i]*30/100);
                float finalexamPercentage=(finalexamMarks[i]*40/100);
                printf("\nStudent ID: %d\n",ids[i]);
                printf("Name: %s\n",names[i]);
                printf("Phone Number: %s\n", phoneNumber[i]);
                printf("Assignment Marks: %d (%.2f%%)\n",assignmentMarks[i],assignmentPercentage);
                printf("Midterm Marks: %d (%.2f %%)\n",midtermMarks[i],midtermPercentage);
                printf("Final Exam Marks: %d (%.2f%%)\n",finalexamMarks[i],finalexamPercentage);
                printf("---------------------------------------------------------------------------------------\n");
            }
            printf("Do you want to add another student? (1=Yes, 2=No):");
            scanf("%d",&choice);
            break;
        case 2:
            searchByID(ids,names,phoneNumber,assignmentMarks,midtermMarks,finalexamMarks,numStudents);
            printf("Do you want to search for another student? (1=Yes, 2=No):");
            scanf("%d",&choice);
            break;
        case 3:
            calculateTotalMarks(ids,names,assignmentMarks, midtermMarks,finalexamMarks,numStudents);
            break;
        case 4:
            generateGrades(ids, names,grades,assignmentMarks,midtermMarks,finalexamMarks,numStudents);
            printf("Grades generated successfully.\n");
            printf("Do you want to conduct another calculation? (1=Yes, 2=No):");
            scanf("%d",&choice);


            for(int i=0; i < numStudents; i++){
                float assignmentPercentage=(assignmentMarks[i]*30/100);
                float midtermPercentage=(midtermMarks[i]*30/100);
                float finalexamPercentage=(finalexamMarks[i]*40/100);
                printf("Assignment Marks: %d (%.2f%%)\n",assignmentMarks[i],assignmentPercentage);
                printf("Midterm Marks: %d (%.2f %%)\n",midtermMarks[i],midtermPercentage);
                printf("Final Exam Marks: %d (%.2f%%)\n",finalexamMarks[i],finalexamPercentage);
                printf("Grades: %c\n",grades[i]);
                printf("---------------------------------------------------------------------------------------\n");
            }
            break;
        case 5:
            generateTop5students(ids, names, assignmentMarks,midtermMarks,finalexamMarks, numStudents);
            break;
        case 6:
            printf("Exiting the program... Bye-bye~\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }while(choice!=0);

    return 0;
}

