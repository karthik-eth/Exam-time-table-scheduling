# Exam-time-table-scheduling

==== Examination Timetable Generator ====
Contributors:Karthik Vijayakumar, Mohith A, Keerthan V S
Version :6

==== Description ====

This Timetable Generator helps to generate a Examination schedules based on the 
type of Examination(Theory, Practical, Arrear) and generates a Timetable with Hall and Invigilator
allotment.

==== Courses.txt ====

This file contains the details about the course in the format
<CourseCode>-<CourseName>-<CourseTYPE>-<No of students registered for exam>
eg MA2271-Maths-Theory-240
    ==== Course code explanation ====
        The course code is of the format XX2abc
        XX is the identifier for department
        CS- CSE department
        IT- IT department
        EE- ECE department
        CI- common for cse and it 
        CE - common for cse and ECE
        IE- common for it and ECE
        Any other letter will be taken as common subject for all department of the particular year

        a is the identifier for semester
        1 for 1st semester
        5 for 5th semester


==== Arrears.txt====
Follows the same scheme as courses.
Generates separate Timetable for arrear Examinations


==== Invigilators.txt====
Contains the names of all the Invigilators along with their department
format:
    name-department
    eg. Mr John Doe-IT

==== Halls.txt ====
contains all the names of the Halls

==== Holidays.txt ====
all the holidays in the format of DD-MM-YYYY

Output Files:

XXb.txt (where XX is the dept code and b is a digit for year)

it is a text file with the Timetable for xx department and 'b' th year Examination

XXba.txt (where XX is the dept code and b is a digit for year)

it is a text file with the Timetable for xx department and 'b' th year Examination
for arrear Examination.

ex IT3.txt is the Timetable for IT DEPT 3rd year

==== HallAllotment.txt ====

it is a file which contains the hall allotment and Invigilator allotment
in the format

Date-SubjectCode-SubjectName-HallCapacity-HallName-Invigilator

Sample Test Case:


 ADD MORE COURSES TO EXISTING SUBJECTS FOR EXAMINATION (Yes/No) : No


                 REMOVE THE EXISTING COURSES AND ADD NEW SET OF COURSES FOR EXAMINATION (Yes/No) : No


                 ENTER THE BEGINNING DATE OF EXAMINATION : 14 08 2018


                 ENTER THE BEGINNING DAY OF EXAMINATION (0-Sunday, 1-Monday,....., 6-Saturday) : 1
                 (what day the BEGINNING date is )
                 

    
                 ADD MORE COURSES TO EXISTING SUBJECTS FOR EXAMINATION (Yes/No) : Yes

 Sample Input for adding new course
         Subject Code : CS2201

         Subject Name : FPSD

         Subject Type (Theory/Practical) : Theory

         Subject Strength (Number of enrollments) : 50

**IMPORTANT**
Give END TO STOP adding new course


         Subject Code : END

        After this the software will stop taking input for 
        new course and the prompt to remove all courses (or) continue
        with EXISTING courses will be asked.




















