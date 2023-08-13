#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file, *file1, *file2, *file3;

typedef struct {
    int day;
    int month;
    int year;
} DATE;

typedef struct {
  char CourseCode[7];
  char CourseName[80];
  char CourseType[10];
  char CourseStrength[4];
  DATE date;
} DICTIONARY;



int WriteCourses(FILE *file);
void ReadCourses(int n, DICTIONARY Stu[], FILE *file);

DATE CommonSubject(DICTIONARY Stu[], DATE CurrentDate, int CourseCount, char CourseType[], int dayofweek, int semester);
DATE BranchwiseCommonSubject(DICTIONARY Stu[], DATE CurrentDate, int CourseCount, char CourseType[], int dayofweek, char Dept[], int semester);
DATE CoreSubject(DICTIONARY Stu[], DATE CurrentDate, int CourseCount, char CourseType[], int dayofweek, char Dept[], int semester);

int HolidayCheck(DATE CurrentDate, int dayofweek);


void HallandInvigilatorAllotment(char Halls[][15], DICTIONARY Stu[], int CourseCount, FILE *file);
void SortSchedule(DICTIONARY Stu[], int CourseCount);

void PrintExamSchedule(void);
void PrintHallSchedule(void);



int main(){

    printf("\n\t\t\t ---------------------------------");
    printf("\n\t\t\t EXAMINATION  SCHEDULING  SOFTWARE");
    printf("\n\t\t\t ---------------------------------");

    printf("\n\t\t The software schedules examinations for the even semesters for 3 years (Academic Year 1, Academic Year2, Academic Year3) and 3 departments (Computer Science and Engineering, \n\t\t Information Technology, Electrical and Electronics Engineering).");
    printf("\n\t\t It also allocates halls/venues nad invigilators for smooth conduct of examination.");

    //Clearing the already existing exam schedules
    file=fopen("CS1.txt","w");
    fclose(file);

    file=fopen("IT1.txt","w");
    fclose(file);

    file=fopen("EE1.txt","w");
    fclose(file);

    file=fopen("CS2.txt","w");
    fclose(file);

    file=fopen("IT2.txt","w");
    fclose(file);

    file=fopen("EE2.txt","w");
    fclose(file);

    file=fopen("CS3.txt","w");
    fclose(file);

    file=fopen("IT3.txt","w");
    fclose(file);

    file=fopen("EE3.txt","w");
    fclose(file);

    file=fopen("CS1a.txt","w");
    fclose(file);

    file=fopen("IT1a.txt","w");
    fclose(file);

    file=fopen("EE1a.txt","w");
    fclose(file);

    file=fopen("CS2a.txt","w");
    fclose(file);

    file=fopen("IT2a.txt","w");
    fclose(file);

    file=fopen("EE2a.txt","w");
    fclose(file);

    file=fopen("CS3a.txt","w");
    fclose(file);

    file=fopen("IT3a.txt","w");
    fclose(file);

    file=fopen("EE3a.txt","w");
    fclose(file);
    
    
    //int CourseCount=WriteFunc();
    //int ArrearCount=WriteFuncArrear();
    int CourseCount=52;
    int ArrearCount=17;
    int day, month, year, startday;
    char choice[5];
 
    printf("\n\n\t\t ADD MORE COURSES TO EXISTING SUBJECTS FOR EXAMINATION (Yes/No) : ");
    scanf("%s", choice);
    if (strcmp(choice, "Yes")==0){
        file=fopen("Courses.txt","a");
        CourseCount+=WriteCourses(file);
    }
    printf("\n\n\t\t REMOVE THE EXISTING COURSES AND ADD NEW SET OF COURSES FOR EXAMINATION (Yes/No) : ");
    scanf("%s", choice);
    if (strcmp(choice, "Yes")==0){
        file=fopen("Courses.txt","w");
        CourseCount+=WriteCourses(file);
    }

    char dept[4];
    char Halls[69][15];
    
    DICTIONARY Stu[CourseCount], Arr[ArrearCount];
    DATE InitialDate, CurrentDate;
    
    //Reading the courses from the file
    file=fopen("Courses.txt","r");
    ReadCourses(CourseCount, Stu, file);

    file=fopen("Arrears.txt","r");
    ReadCourses(ArrearCount, Arr, file);
    
    printf("\n\n\t\t ENTER THE BEGINNING DATE OF EXAMINATION : ");
    scanf("%2d %2d %4d", &InitialDate.day, &InitialDate.month, &InitialDate.year);
    
    printf("\n\n\t\t ENTER THE BEGINNING DAY OF EXAMINATION (0-Sunday, 1-Monday,....., 6-Saturday) : ");
    scanf("%d", &startday);

    int var=startday;

    // Scheduling the Main Examinations (Even Semester)
    
    for (int i=2; i<7; i+=2){

        // Scheduling Theory Examinations
        CurrentDate=InitialDate;
        int dayofweek=var;
        
        DATE TempDate=CommonSubject(Stu, CurrentDate, CourseCount, "Theory", dayofweek, i);
    
        dayofweek=(((TempDate.day-CurrentDate.day))%7)+var;
   
        DATE CSDate=TempDate;
        DATE ITDate=TempDate;
        DATE ECDate=TempDate;
    
        strcpy(dept,"CS");
        CSDate=BranchwiseCommonSubject(Stu, CSDate, CourseCount, "Theory", dayofweek, dept, i);
    
        strcpy(dept, "IT");
        ITDate=BranchwiseCommonSubject(Stu, ITDate, CourseCount, "Theory", dayofweek, dept, i);

        strcpy(dept, "EE");
        ECDate=BranchwiseCommonSubject(Stu, ECDate, CourseCount, "Theory", dayofweek, dept, i);

        CSDate=CSDate;
        ITDate=ITDate;
        ECDate=ECDate;
    
        strcpy(dept,"CS");
        dayofweek=((CSDate.day-CurrentDate.day)%7)+var;
        CSDate=CoreSubject(Stu, CSDate, CourseCount, "Theory", dayofweek, dept, i);
    

        strcpy(dept, "IT");
        dayofweek=((ITDate.day-CurrentDate.day)%7)+var;
        ITDate=CoreSubject(Stu, ITDate, CourseCount, "Theory", dayofweek, dept, i);

        strcpy(dept, "EE");
        dayofweek=((ECDate.day-CurrentDate.day)%7)+var;
        ECDate=CoreSubject(Stu, ECDate, CourseCount, "Theory", dayofweek, dept, i);

        // Scheduling Practical Examinations
 
        if (CSDate.day>=ITDate.day){
            if (CSDate.day>=ECDate.day){
                TempDate=CSDate;
            }
            else TempDate=ECDate;
        }

        else{
            if (ITDate.day>=ECDate.day){
                TempDate=ITDate;
            }
            else TempDate=ECDate;
        }
    
        dayofweek=(((TempDate.day-CurrentDate.day))%7)+var;
        TempDate=CommonSubject(Stu, TempDate, CourseCount, "Practical", dayofweek, i);

        dayofweek=(((TempDate.day-CurrentDate.day))%7)+var;
        CSDate=TempDate;
        ITDate=TempDate;
        ECDate=TempDate;

        strcpy(dept,"CS");
        CSDate=CoreSubject(Stu, CSDate, CourseCount, "Practical", dayofweek, dept, i);

        strcpy(dept, "IT");
        ITDate=CoreSubject(Stu, ITDate, CourseCount, "Practical", dayofweek, dept, i);

        strcpy(dept, "EE");
        ITDate=CoreSubject(Stu, ECDate, CourseCount, "Practical", dayofweek, dept, i);

        if (CSDate.day>=ITDate.day){
            if (CSDate.day>=ECDate.day){
                TempDate=CSDate;
            }
            else TempDate=ECDate;
        }

        else{
            if (ITDate.day>=ECDate.day){
                TempDate=ITDate;
            }
            else TempDate=ECDate;
        }

        dayofweek=(((TempDate.day-CurrentDate.day))%7)+var;
    }

    // Scheduling the Arrear Examinations or Re-examinations (Odd Semester)

    for (int i=1; i<6; i+=2){
        
        // Scheduling Theory Examinations

        CurrentDate.day=InitialDate.day+1;
        int dayofweek=var+1;
   
        DATE TempDate=CommonSubject(Arr, CurrentDate, ArrearCount, "Theory", dayofweek, i);
    
        dayofweek=(((TempDate.day-CurrentDate.day))%7)+var;
        DATE CSDate=TempDate;
        DATE ITDate=TempDate;
        DATE ECDate=TempDate;
    
        strcpy(dept,"CS"); 
        CSDate=CoreSubject(Arr, CSDate, ArrearCount, "Theory", dayofweek, dept, i);

        strcpy(dept, "IT");
        ITDate=CoreSubject(Arr, ITDate, ArrearCount, "Theory", dayofweek, dept, i);

        strcpy(dept, "EE");
        ITDate=CoreSubject(Arr, ECDate, ArrearCount, "Theory", dayofweek, dept, i);
    
        if (CSDate.day>=ITDate.day){
            if (CSDate.day>=ECDate.day){
                TempDate=CSDate;
            }
            else TempDate=ECDate;
        }

        else{
            if (ITDate.day>=ECDate.day){
                TempDate=ITDate;
            }
            else TempDate=ECDate;
        }

        dayofweek=(((TempDate.day-CurrentDate.day))%7)+var;
        TempDate=CommonSubject(Arr, TempDate, ArrearCount, "Practical", dayofweek, i);

        dayofweek=(((TempDate.day-CurrentDate.day))%7)+var;
        CSDate=TempDate;
        ITDate=TempDate;
        ECDate=TempDate;

        strcpy(dept,"CS");
        CSDate=CoreSubject(Arr, CSDate, ArrearCount, "Practical", dayofweek, dept, i);

        strcpy(dept, "IT");
        ITDate=CoreSubject(Arr, ITDate, ArrearCount, "Practical", dayofweek, dept, i);

        strcpy(dept, "EE");
        ITDate=CoreSubject(Arr, ECDate, ArrearCount, "Practical", dayofweek, dept, i);

        if (CSDate.day>=ITDate.day){
            if (CSDate.day>=ECDate.day){
                TempDate=CSDate;
            }
            else TempDate=ECDate;
        }

        else{
            if (ITDate.day>=ECDate.day){
                TempDate=ITDate;
            }
            else TempDate=ECDate;
        }

        dayofweek=(((TempDate.day-CurrentDate.day))%7)+var;
    }
    printf("\n\t\t EXAMINATIONS SCHEDULED SUCCESSFULLY");
    
    //Arranging the Main Exam Schedule Datewise
    SortSchedule(Stu, CourseCount); 

    //Hall and Invigilator Allotment for Main Examinations
    file1=fopen("HallAllotment.txt","w");
    HallandInvigilatorAllotment(Halls, Stu, CourseCount, file1);

    //Arranging the Arrear Exam Schedule Datewise
    SortSchedule(Arr, ArrearCount);
    
    //Hall and Invigilator Allotment for Arrear Examinations
    file1=fopen("ArrearHallAllotment.txt","w");
    HallandInvigilatorAllotment(Halls, Arr, ArrearCount, file1);
    printf("\n\t\t HALLS AND INVIGILATORS ALOTTED SUCCESSFULLY");

    PrintExamSchedule(); 
    //PrintHallSchedule();  
}

int WriteCourses(FILE *file){

    int count=0;
    char CourseCode[7]="CODE";
    char CourseName[80];
    char CourseType[10];
    char CourseStrength[4];
    if (file==NULL){
        printf("\n\t\t ERROR IN OPENING THE FILE");
    }
    else{
        while (strcmp(CourseCode,"END")!=0){
            printf("\n\n\t Subject Code : ");
            scanf("%s",CourseCode);
            if (strcmp(CourseCode,"END")!=0){
                printf("\n\t Subject Name : ");
                scanf(" %[^\n]",CourseName);
                printf("\n\t Subject Type (Theory/Practical) : ");
                scanf("%s",CourseType);
                printf("\n\t Subject Strength (Number of enrollments) : ");
                scanf("%s", CourseStrength);

                fprintf(file,"%s-%s-%s-%s\n", CourseCode, CourseName, CourseType, CourseStrength);
                count++;
            } 
        }
    }
    fclose(file);
    return count;
}

void ReadCourses(int n, DICTIONARY Stu[], FILE *file){
    
    int i=0, integer;
    char temp[120], *token, s[2]="-";
    if (file==NULL){
        printf("\n\t\t ERROR IN OPENING THE FILE");
    }
    else{
        for (i=0; i<n; i++){
            fscanf(file,"%s",temp);
            int j=0;
            token=strtok(temp, s);
            
            while (token!=NULL){
                if (j==0) {
                    strcpy(Stu[i].CourseCode,token);
                }
                else if (j==1) {
                    strcpy(Stu[i].CourseName,token);
                }
                else if (j==2) {
                    strcpy(Stu[i].CourseType,token);
                }
                else if (j==3) {
                    strcpy(Stu[i].CourseStrength,token);
                }
                j++;
                token=strtok(NULL,s);
            }
        }
    }
    fclose(file);
}

DATE CommonSubject(DICTIONARY Stu[], DATE CurrentDate, int CourseCount, char CourseType[], int dayofweek, int semester){

    if (semester==2) {
        file1=fopen("CS1.txt","a");
        file2=fopen("IT1.txt","a");
        file3=fopen("EE1.txt","a");
    }
    else if (semester==1){
        file1=fopen("CS1a.txt","a");
        file2=fopen("IT1a.txt","a");
        file3=fopen("EE1a.txt","a");
    }
    else if (semester==4){
        file1=fopen("CS2.txt","a");
        file2=fopen("IT2.txt","a");
        file3=fopen("EE2.txt","a");
    }
    else if (semester==3){
        file1=fopen("CS2a.txt","a");
        file2=fopen("IT2a.txt","a");
        file3=fopen("EE2a.txt","a");
    }
    else if (semester==6){
        file1=fopen("CS3.txt","a");
        file2=fopen("IT3.txt","a");
        file3=fopen("EE3.txt","a");
    }
    else if (semester==5){
        file1=fopen("CS3a.txt","a");
        file2=fopen("IT3a.txt","a");
        file3=fopen("EE3a.txt","a");
    }
    
    int i=0;
    for (i=0; i<CourseCount; i++){
        if ((Stu[i].CourseCode[0]!='C' && Stu[i].CourseCode[1]!='S') && (Stu[i].CourseCode[0]!='I' && Stu[i].CourseCode[1]!='T') && (Stu[i].CourseCode[0]!='E' && Stu[i].CourseCode[1]!='E') && (strcmp(Stu[i].CourseType, CourseType)==0) && ((Stu[i].CourseCode[3])==(semester+'0'))){
            
            while (HolidayCheck(CurrentDate, dayofweek)==1){
                if (CurrentDate.day<29){
                    CurrentDate.day=CurrentDate.day+2;
                    dayofweek=(dayofweek+2)%7;
                }
                else if (CurrentDate.day==29){
                    CurrentDate.day=1;
                    CurrentDate.month=CurrentDate.month+1;
                    dayofweek=(dayofweek+2)%7;
                }
                else if (CurrentDate.day==30){
                    CurrentDate.day=2;
                    CurrentDate.month=CurrentDate.month+1;
                    dayofweek=(dayofweek+2)%7;
                }
            }
            
            Stu[i].date.day=CurrentDate.day;
            Stu[i].date.month=CurrentDate.month;
            Stu[i].date.year=CurrentDate.year;
            fprintf(file1, "%d-%d-%d %s %s\n", CurrentDate.day, CurrentDate.month, CurrentDate.year, Stu[i].CourseCode, Stu[i].CourseName);
            fprintf(file2, "%d-%d-%d %s %s\n", CurrentDate.day, CurrentDate.month, CurrentDate.year, Stu[i].CourseCode, Stu[i].CourseName);
            fprintf(file3, "%d-%d-%d %s %s\n", CurrentDate.day, CurrentDate.month, CurrentDate.year, Stu[i].CourseCode, Stu[i].CourseName);
                   
            if (CurrentDate.day<29){
                CurrentDate.day=CurrentDate.day+2;
                dayofweek=(dayofweek+2)%7;
            }
            else if (CurrentDate.day==29){
                CurrentDate.day=1;
                CurrentDate.month=CurrentDate.month+1;
                dayofweek=(dayofweek+2)%7;
            }
            else if (CurrentDate.day==30){
                CurrentDate.day=2;
                CurrentDate.month=CurrentDate.month+1;
                dayofweek=(dayofweek+2)%7;
            }
        }
    }
    fclose(file1);
    fclose(file2);
    fclose(file3);
    return CurrentDate;
}

DATE BranchwiseCommonSubject(DICTIONARY Stu[], DATE CurrentDate, int CourseCount, char CourseType[], int dayofweek, char Dept[], int semester){

    if (semester==2) {
        strcat(Dept, "1.txt");
    }
    else if (semester==1){
        strcat(Dept, "1a.txt");
    }
    else if (semester==4){
        strcat(Dept, "2.txt");
    }
    else if (semester==3){
        strcat(Dept, "2a.txt");
    }
    else if (semester==6){
        strcat(Dept, "3.txt");
    }
    else if (semester==5){
        strcat(Dept, "3a.txt");
    }
    file1=fopen(Dept,"a");

    for (int i=0; i<CourseCount; i++){
        if (Stu[i].CourseCode[0]==Dept[0] && Stu[i].CourseCode[1]==Dept[1]){
            // Pass Condition
            printf("");
        }
        else{
            if (((Stu[i].CourseCode[0]==Dept[0]) || (Stu[i].CourseCode[1]==Dept[1]) || (Stu[i].CourseCode[0]==Dept[1]) || (Stu[i].CourseCode[1]==Dept[0])) && (strcmp(Stu[i].CourseType, CourseType)==0) && ((int)(Stu[i].CourseCode[3])==(semester+'0'))){
                while (HolidayCheck(CurrentDate, dayofweek)==1){
                    if (CurrentDate.day<29){
                        CurrentDate.day=CurrentDate.day+2;
                        dayofweek=(dayofweek+2)%7;
                    }
                    else if (CurrentDate.day==29){
                        CurrentDate.day=1;
                        CurrentDate.month=CurrentDate.month+1;
                        dayofweek=(dayofweek+2)%7;
                    }
                    else if (CurrentDate.day==30){
                        CurrentDate.day=2;
                        CurrentDate.month=CurrentDate.month+1;
                        dayofweek=(dayofweek+2)%7;
                    }
                }

                Stu[i].date.day=CurrentDate.day;
                Stu[i].date.month=CurrentDate.month;
                Stu[i].date.year=CurrentDate.year;
                fprintf(file1, "%d-%d-%d %s %s\n", CurrentDate.day, CurrentDate.month, CurrentDate.year, Stu[i].CourseCode, Stu[i].CourseName);

                if (CurrentDate.day<29){
                    CurrentDate.day=CurrentDate.day+2;
                    dayofweek=(dayofweek+2)%7;
                }
                else if (CurrentDate.day==29){
                    CurrentDate.day=1;
                    CurrentDate.month=CurrentDate.month+1;
                    dayofweek=(dayofweek+2)%7;
                }
                else if (CurrentDate.day==30){
                    CurrentDate.day=2;
                    CurrentDate.month=CurrentDate.month+1;
                    dayofweek=(dayofweek+2)%7;
                }
            }
        }
    }
    fclose(file1);
    return CurrentDate;
}

DATE CoreSubject(DICTIONARY Stu[], DATE CurrentDate, int CourseCount, char CourseType[], int dayofweek, char Dept[], int semester){

    if (semester==2) {
        strcat(Dept, "1.txt");
    }
    else if (semester==1){
        strcat(Dept, "1a.txt");
    }
    else if (semester==4){
        strcat(Dept, "2.txt");
    }
    else if (semester==3){
        strcat(Dept, "2a.txt");
    }
    else if (semester==6){
        strcat(Dept, "3.txt");
    }
    else if (semester==5){
        strcat(Dept, "3a.txt");
    }
    file1=fopen(Dept,"a");

    for (int i=0; i<CourseCount; i++){
        if ((Stu[i].CourseCode[0]==Dept[0]) && (Stu[i].CourseCode[1]==Dept[1]) && (strcmp(Stu[i].CourseType, CourseType)==0) && ((int)(Stu[i].CourseCode[3])==(semester+'0'))){
            while (HolidayCheck(CurrentDate, dayofweek)==1){
                if (CurrentDate.day<29){
                    CurrentDate.day=CurrentDate.day+2;
                    dayofweek=(dayofweek+2)%7;
                }
                else if (CurrentDate.day==29){
                    CurrentDate.day=1;
                    CurrentDate.month=CurrentDate.month+1;
                    dayofweek=(dayofweek+2)%7;
                }
                else if (CurrentDate.day==30){
                    CurrentDate.day=2;
                    CurrentDate.month=CurrentDate.month+1;
                    dayofweek=(dayofweek+2)%7;
                }
            }
            Stu[i].date.day=CurrentDate.day;
            Stu[i].date.month=CurrentDate.month;
            Stu[i].date.year=CurrentDate.year;
            fprintf(file1, "%d-%d-%d %s %s\n", CurrentDate.day, CurrentDate.month, CurrentDate.year, Stu[i].CourseCode, Stu[i].CourseName);

            if (CurrentDate.day<29){
                CurrentDate.day=CurrentDate.day+2;
                dayofweek=(dayofweek+2)%7;
            }
            else if (CurrentDate.day==29){
                CurrentDate.day=1;
                CurrentDate.month=CurrentDate.month+1;
                dayofweek=(dayofweek+2)%7;
            }
            else if (CurrentDate.day==30){
                CurrentDate.day=2;
                CurrentDate.month=CurrentDate.month+1;
                dayofweek=(dayofweek+2)%7;
            }
        }
    }
    fclose(file1);
    return CurrentDate;
}

int HolidayCheck(DATE CurrentDate, int dayofweek){

    if (dayofweek%7==0) return 1;
    else{
        file=fopen("Holidays.txt","r");
        DATE HolidayDate;
        while (fscanf(file, "%d-%d-%d", &HolidayDate.day, &HolidayDate.month, &HolidayDate.year)!=EOF){
            if ((CurrentDate.day==HolidayDate.day) && (CurrentDate.month==HolidayDate.month) && (CurrentDate.year==HolidayDate.year)){
                return 1;
            }
        }
        fclose(file);
        return 0;
    }   
}

void HallandInvigilatorAllotment(char Halls[][15], DICTIONARY Stu[], int CourseCount, FILE *file1){

    char Invigilators[35][2][25], temp[30], *token, s[2]="-";;
    DATE InvigilationDate[35];
    int i=0;

    // Initialising the structure to pseudo-dates
    for (int s=0; s<23; s++){
        InvigilationDate[s].day=0;
        InvigilationDate[s].month=0;
        InvigilationDate[s].year=0;
    }

    // Reading the invigilators
    file2=fopen("Invigilators.txt","r"); 
    if (file2==NULL){
        printf("\n\t\t ERROR IN OPENING THE FILE");
    }
    else{
        int j=0;
        while (fscanf(file2, "%s", temp)!=EOF){
            j=0;
            token=strtok(temp, s);

            while (token!=NULL){
                strcpy(Invigilators[i][j], token);
                token=strtok(NULL, s);
                j++;
            }
            i++;
        }
    }
    fclose(file2);
    
    //Reading the Halls
    file=fopen("Halls.txt","r");
    int j=0, l=0, Frequency, Remaining, NumberHalls, NumberStudents;
    i=0;
    if (file==NULL){
        printf("\n\t\t ERROR IN OPENING THE FILE");
    }
    else{  
        while (fscanf(file,"%s",Halls[j])!=EOF){
            j++;
        }
        int MaxHalls=j-1;
        j=0;
        i=0;
        
        while (i<CourseCount){ 
            
            // To calculate the number of halls for each exam
            
            Frequency=atoi(Stu[i].CourseStrength);
            Remaining=Frequency%25;
            NumberHalls=(Frequency/25);
            if (Remaining>10) {
                NumberHalls+=1;
            }
            NumberStudents=25;
            if (strcmp(Stu[i].CourseType, "Theory")==0){
                int k=0;
                if ((i>0) && (Stu[i-1].date.day!=Stu[i].date.day)) {
                    j=0;
                    l=0;
                }
                while (k<NumberHalls){
                    if (k==NumberHalls-1){
                        if (Remaining>10) NumberStudents=Remaining;
                        else NumberStudents+=Remaining;
                    }
                    
                    if (((InvigilationDate[l].day!=Stu[i].date.day)) || ((InvigilationDate[l].day!=Stu[i].date.day) && (InvigilationDate[l].month!=Stu[i].date.month) && (InvigilationDate[l].year!=Stu[i].date.year))){
                        InvigilationDate[l].day=Stu[i].date.day;
                        InvigilationDate[l].month=Stu[i].date.month;
                        InvigilationDate[l].year=Stu[i].date.year;

                        //(InvigilationDate[l].day!=Stu[i].date.day) && (InvigilationDate[l].month!=Stu[i].date.month) && (InvigilationDate[l].year!=Stu[i].date.year) && (Invigilators[l][1][0]!=Stu[i].CourseCode[0]) && (Invigilators[l][1][1]!=Stu[i].CourseCode[1])
                        fprintf(file1, "%d-%d-%d-%s-%s-%d-%s-%s\n", Stu[i].date.day, Stu[i].date.month, Stu[i].date.year, Stu[i].CourseCode, Stu[i].CourseName, NumberStudents, Halls[j++], Invigilators[l]);
                        l++;
                        if (j>MaxHalls) j=0;
                        if (l>34) l=0;    
                    }
                    else {
                        l++;
                        if (l>34) l=0;
                    }
                    k++;
                }
            }
            i++;
        }
    fclose(file);
    fclose(file1);
    }
}

void SortSchedule(DICTIONARY Stu[], int CourseCount){

    DICTIONARY temp;

    for (int i=0; i<CourseCount-1; i++){
        for (int j=0; j<CourseCount-i-1; j++){
            if ((Stu[j].date.day>Stu[j+1].date.day)) {
                temp=Stu[j];
                Stu[j]=Stu[j+1];
                Stu[j+1]=temp;
            }
        }
    }
}

void PrintExamSchedule(void){

    char Code[40], Name[40], *token, s[2]=" ";
    int day, month, year;
    char Departments[3][3]={"CS", "IT", "EE"};
    char filename[10];

    for (int i=1; i<7; i++){
        for (int j=0; j<3; j++){
            printf("\n\n\t\t\t YEAR %d SEMESTER %d", (i+1)/2, i);
            strcpy(filename, Departments[j]);
            if (j==0){
                printf("\n\n\t\t COMPUTER SCIENCE AND ENGINEERING");
            }
            else if (j==1){
                printf("\n\n\t\t      INFORMATION TECHNOLOGY");
            }
            else if (j==2){
                printf("\n\n\t\t ELECTRONICS AND COMMUNICATION ENGINEERING");
            }
            
            if (i==1){
                strcat(filename, "1a.txt");
                printf("\n\t\t\t RE-EXAMINATION");
            }
            else if (i==2){
                strcat(filename, "1.txt");
            }
            else if (i==3){
                strcat(filename, "2a.txt");
                printf("\n\t\t\t RE-EXAMINATION");
            }
            else if (i==4){
                strcat(filename, "2.txt");
            }
            else if (i==5){
                strcat(filename, "3a.txt");
                printf("\n\t\t\t RE-EXAMINATION");
            }
            else if (i==6){
                strcat(filename, "3.txt");
            }
            file=fopen(filename,"r");
    
            if (file==NULL){
                printf("\nCan't Open File");
            }
            else{
                printf("\n\t+-----------+--------+------------------------------------------+");
                printf("\n\t|   DATE    |  CODE  |     COURSE NAME   \t\t\t|");
                printf("\n\t+-----------+--------+------------------------------------------+");
                while (fscanf(file,"%d-%d-%d %s %s", &day, &month, &year, Code, Name)!=EOF){
                    if (strlen(Name)<=6){
                        printf("\n\t| %d-%d-%d | %s |\t%s \t\t\t\t\t|", day, month, year, Code, Name);
                    }
                    else if (strlen(Name) <= 14) {
                        printf("\n\t| %d-%d-%d | %s |\t%s \t\t\t\t|", day, month, year, Code, Name);
                    }
                    else if (strlen(Name) <= 22 && strlen(Name) > 14) {
                        printf("\n\t| %d-%d-%d | %s |\t%s \t\t\t|", day, month, year, Code, Name); 
                    }
                    else if ( strlen(Name) > 22 && strlen(Name) < 34) {
                        printf("\n\t| %d-%d-%d | %s |\t%s \t\t|", day, month, year, Code, Name);
                    }
                    else {
                        printf("\n\t| %d-%d-%d | %s |\t%s \t|", day, month, year, Code, Name);
                    }
                    printf("\n\t+-----------+--------+------------------------------------------+");
                }
            }
        fclose(file);
        }
    }
}

void PrintHallSchedule(void){
    file1=fopen("HallAllotment.txt","r");
    char temp[120];
    char day[2], month[2], year[4], studentsnum[2];
    char Code[40], Name[40], Hall[10], Invigilator[40], *token, s[2]=" ";
    printf("\n\n\t\t\t EXAMINATION VENUE\n\n");
    printf("\n\t+-----------+--------+------------------------------------------+------------------+--------------");
    printf("\n\t|   DATE    |  CODE  |     COURSE NAME   \t\t\t|   NUMBER OF STUDENTS  |    HALL NAME   |");
    printf("\n\t+-----------+--------+------------------------------------------+------------------+--------------");
    /*
    while (fscanf(file1, "%d-%d-%d-%s-%s-%d-%s-%s", &day, &month, &year, Code, Name, &studentsnum, Hall, Invigilator)!=EOF){
        printf("\n\t| %d-%d-%d | %s |\t%s \t\t\t| %d | %s    |", day, month, year, Code, Name, studentsnum, Hall);
        printf("\n\t+-----------+--------+------------------------------------------+------------------+--------------");
    }
    */

    while (fscanf(file,"%s",temp)!=EOF){
            int j=0;
            token=strtok(temp, s);
            
            while (token!=NULL){
                if (j==0) {
                    strcpy(day,token);
                }
                else if (j==1) {
                    strcpy(month,token);
                }
                else if (j==2) {
                    strcpy(year,token);
                }
                else if (j==3) {
                    strcpy(Code,token);
                }
                else if (j==4){
                    strcpy(Name, token);
                }
                else if (j==5){
                    strcpy(studentsnum, token);
                }
                else if (j==6){
                    strcpy(Hall, token);
                }
                else if (j==7){
                    strcpy(Invigilator,token);
                }
                j++;
                token=strtok(NULL,s);
            }

            printf("\n\t| %s-%s-%s | %s |\t%s \t\t\t| %s | %s    |", day, month, year, Code, Name, studentsnum, Hall);
            printf("\n\t+-----------+--------+------------------------------------------+------------------+--------------");
    }

    fclose(file);
}