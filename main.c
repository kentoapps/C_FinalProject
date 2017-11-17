//
//  main.c
//  file
//
//  Created by Alireza Davoodi on 2017-02-02.
//  Copyright © 2017 CICCC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CoursesFile "Courses.txt"
#define AccountsFile "Accounts.txt"
#define StudentsFile "Students.txt"
#define StudentsCoursesFile "StudentsCourses.txt"

#define BASE "/Users/kento/dev/learning/ciccc/c/FinalProject/sayaka/"

struct Student {
    char *studentID;
    char *name;
    char *gender;
    int grade;
    char *address;
    int admission_year;
    char **courses;
    int numberOfCourses;
};

struct Account {
    char *username;
    char *password;
};

struct Course {
    char *courseID;
    char *name;
};

struct StudentCourse {
    char *studentID;
    char *courseID;
    int mark;
};

//Global Variables
struct Student *listOfStudents;
struct Account *listOfAccounts;
struct Course *listOfCourses;
struct StudentCourse *listOfStudentCourses;
int numberOfStudents = 0;
int numberOfAccounts = 0;
int numberOfCourses = 0;
int numberOfStudentCourses = 0;

// Logged in Student data
struct Student myStudent;
struct Course *myCourseList;
struct StudentCourse *myStudentCourseList;
int myStudentCourseNum;
double myGPA = 0;
int myRank = 0;

char firstChar(char *line);

int strLength(char *line);

char *substring(char *line, int startIndex, int endIndex);

int getTheStartIndex(char *filename, char firstChar);

char **splitString(char *a_str, const char a_delim, int *numberOfComponents);

char **readFile(char *fileAddress, int *numberOfLines);

int numberOfItemsPerRecordInFile(char *fileName);

int convertToNumber(char *);

struct Student createAStudent(char *studentID, char *name, char *gender, int grade, char *address, int admission_year,
                              char *courses[], int numberOfCourses);

struct Student *getListOfStudentFromFile(char *fileAddress, char *fileName, int *numberOfStudents);

struct Account createAnAccount(char *username, char *password);

struct Account *getListOfAccountFromFile(char *address, char *name, int *pInt);

struct Course createACourse(char *courseId, char *name);

struct Course *getListOfCourseFromFile(char *address, char *name, int *numberOfCourses);

struct StudentCourse createAStudentCourse(char *studentID, char *courseID, int mark);

struct StudentCourse *getListOfStudentCourseFromFile(char *address, char *name, int *numberOfStudentCourses);

extern void printLogin();

extern void printWelcome();

extern void printErrorLogin();

extern void printMenu();

extern void printMyCertificate(char *name, char *studentId);

extern void printMyCourses();

extern void printMyTranscript();

extern void printMyGpa();

extern void printMyRanking();

extern void printCoursesList();

extern void printStudents();

void loadFiles();

void showMainMenu();

void showLogin();

void keepCurrentStudent(char *studentID);

char *getCourseName(char *courseID);

char *getMrMs(char *gender);

char *getHeShe(char *gender);

char *getheshe(char *gender);

int main(int argc, const char *argv[]) {
    loadFiles();

    showLogin();

    return 0;
}

void showLogin() {
    printLogin();

    char username[50];
    char password[50];
    scanf("%s", username);
    scanf("%s", password);

    for (int i = 0; i < numberOfAccounts; i++) {
        if (strcmp(listOfAccounts[i].username, username) == 0
            && strcmp(listOfAccounts[i].password, password) == 0) {
            keepCurrentStudent(username);
//            if (myStudent) {
//                printf("ERROR!");
//                return;
//            }
            printWelcome();
            sleep(2);
            showMainMenu();
            return;
        }
    }
    printErrorLogin();
    sleep(1);
    showLogin();
}

void keepCurrentStudent(char *studentID) {
    // Student
    for (int i = 0; i < numberOfStudents; ++i) {
        if (strcmp(listOfStudents[i].studentID, studentID) == 0)
            myStudent = listOfStudents[i];
    }
    // Course name
    int num = 0;
    myCourseList = (struct Course *) malloc(10 * sizeof(struct Course));
    for (int i = 0; i < myStudent.numberOfCourses; ++i) {
        for (int j = 0; j < numberOfCourses; ++j) {
            if (strcmp(myStudent.courses[i], listOfCourses[j].courseID) == 0) {
                myCourseList[num] = listOfCourses[j];
                num++;
            }
        }
    }
    // My Student course
    myStudentCourseNum = 0;
    myStudentCourseList = (struct StudentCourse *) malloc(10 * sizeof(struct StudentCourse));
        for (int i = 0; i < numberOfStudentCourses; ++i) {
            if (strcmp(myStudent.studentID, listOfStudentCourses[i].studentID) == 0) {
                myStudentCourseList[myStudentCourseNum] = listOfStudentCourses[i];
                myStudentCourseNum++;
            }
        }

    // GPA
    myGPA = 0;
    for (int k = 0; k < myStudentCourseNum; ++k) {
        myGPA += myStudentCourseList[k].mark;
    }
    myGPA /= myStudentCourseNum;

    // Rank
    myRank = 1;
    for (int l = 0; l < numberOfStudents; ++l) {
        if (strcmp(myStudent.studentID, listOfStudents[l].studentID) == 0) continue;
        int gpa = 0;
        int n = 0;
        struct Student s = listOfStudents[l];
        for (int i = 0; i < numberOfStudentCourses; ++i) {
            if (strcmp(s.studentID, listOfStudentCourses[i].studentID) == 0) {
                gpa += listOfStudentCourses[i].mark;
                n++;
            }
        }
        gpa /= n;
        if (myGPA < gpa) myRank++;
    }
}

void showMainMenu() {
    printMenu();
    int option;
    scanf("%d", &option);

    switch (option) {
        case 1:
            printMyCertificate(myStudent.name, myStudent.studentID);
            break;
        case 2:
            printMyCourses();
            break;
        case 3:
            printMyTranscript();
            break;
        case 4:
            printMyGpa();
            break;
        case 5:
            printMyRanking();
            break;
        case 6:
            printCoursesList();
            break;
        case 7:
            printStudents();
            break;
        case 8:
            printf("Log out!\n\n");
            sleep(1);
            showLogin();
            return;
        case 9:
            printf("Bye bye!\n");
            return;
    }
    sleep(2);
    showMainMenu();
}

void loadFiles() {
    //***************************************************************
    // Read the Students.txt file and create an array of Students
    //***************************************************************
    char *studentsFileName = StudentsFile;
    //You need to change this address to your address.
    char *studentsFileAddress = BASE StudentsFile;

    listOfStudents = getListOfStudentFromFile(studentsFileAddress, studentsFileName, &numberOfStudents);

//    for (int i = 0; i < numberOfStudents; i++) {
//        printf("%s\n", listOfStudents[i].name);
//        printf("%d\n", listOfStudents[i].numberOfCourses);
//        printf("%s\n", listOfStudents[i].address);
//        printf("%d\n", listOfStudents[i].grade);
//        printf("%d\n", listOfStudents[i].admission_year);
//
//        for (int j = 0; j < listOfStudents[i].numberOfCourses; j++) {
//            printf("\n%s", listOfStudents[i].courses[j]);
//        }
//
//        printf("\n============================\n");
//    }


    //***************************************************************
    // Read the Accounts.txt file and create an array of Accounts
    //***************************************************************
    char *accountsFileName = AccountsFile;
    //You need to change this address to your address.
    char *accountsFileAddress = BASE AccountsFile;

    listOfAccounts = getListOfAccountFromFile(accountsFileAddress, accountsFileName, &numberOfAccounts);

//    for (int i = 0; i < numberOfAccounts; i++) {
//        printf("%s\n", listOfAccounts[i].username);
//        printf("%s\n", listOfAccounts[i].password);
//        printf("\n============================\n");
//    }


    //***************************************************************
    // Read the Courses.txt file and create an array of Courses
    //***************************************************************
    char *coursesFileName = CoursesFile;
    //You need to change this address to your address.
    char *coursesFileAddress = BASE CoursesFile;

    listOfCourses = getListOfCourseFromFile(coursesFileAddress, coursesFileName, &numberOfCourses);

//    for (int i = 0; i < numberOfCourses; i++) {
//        printf("%s\n", listOfCourses[i].courseID);
//        printf("%s\n", listOfCourses[i].name);
//        printf("\n============================\n");
//    }


    //***************************************************************
    // Read the StudentCourses.txt file and create an array of StudentCourses
    //***************************************************************
    char *studentCoursesFileName = StudentsCoursesFile;
    //You need to change this address to your address.
    char *studentCoursesFileAddress = BASE StudentsCoursesFile;

    listOfStudentCourses = getListOfStudentCourseFromFile(studentCoursesFileAddress, studentCoursesFileName,
                                                          &numberOfStudentCourses);

//    for (int i = 0; i < numberOfStudentCourses; i++) {
//        printf("%s\n", listOfStudentCourses[i].studentID);
//        printf("%s\n", listOfStudentCourses[i].courseID);
//        printf("%d\n", listOfStudentCourses[i].mark);
//        printf("\n============================\n");
//    }

}


int getTheStartIndex(char *filename, char firstChar) {
    if (strcmp(filename, AccountsFile) == 0 && firstChar == '1') { //1User:”
        return 7;
    } else if (strcmp(filename, AccountsFile) == 0 && firstChar == '2') { //2Pass:”
        return 7;
    } else if (strcmp(filename, StudentsFile) == 0 && firstChar == '1') { //1studentID:”
        return 12;
    } else if (strcmp(filename, StudentsFile) == 0 && firstChar == '2') { //2name:”
        return 7;
    } else if (strcmp(filename, StudentsFile) == 0 && firstChar == '3') { //3gender:”
        return 9;
    } else if (strcmp(filename, StudentsFile) == 0 && firstChar == '4') { //4grade:”
        return 8;
    } else if (strcmp(filename, StudentsFile) == 0 && firstChar == '5') { //5address:“
        return 10;
    } else if (strcmp(filename, StudentsFile) == 0 && firstChar == '6') { //6admission_year:”
        return 17;
    } else if (strcmp(filename, StudentsFile) == 0 && firstChar == '7') { //7courses:”
        return 10;
    } else if (strcmp(filename, CoursesFile) == 0 && firstChar == '1') { //courseID
        return 11;
    } else if (strcmp(filename, CoursesFile) == 0 && firstChar == '2') { //name
        return 7;
    } else if (strcmp(filename, StudentsCoursesFile) == 0 && firstChar == '1') { //1studentID:"
        return 12;
    } else if (strcmp(filename, StudentsCoursesFile) == 0 && firstChar == '2') { //2courseID:"
        return 11;
    } else if (strcmp(filename, StudentsCoursesFile) == 0 && firstChar == '3') { //3mark:"
        return 7;
    } else {
        return 0;
    }
}


//This method gives the length of the string. [You don't need to know how it deos it exactly]
int strLength(char *line) {
    char c = '\n';
    int index = 0;

    int numberOfDoubleQuotes = 0;

    while (numberOfDoubleQuotes < 2) {
        c = *(line + index);
        index++;

        if (c == '"') {
            numberOfDoubleQuotes++;
        }
    }
    return index;
}


//This method gives the first character of a string. [You don't need to know how it does it exactly]
char firstChar(char *line) {
    return *line;
}


//This method gives the substring of a string given the start and end index. [You don't need to know how it deos it exactly]
char *substring(char *line, int startIndex, int endIndex) {
    int len = (endIndex - startIndex) + 1;

    char *substring;

    //substring = (char*) malloc((len+1)*sizeof(char));

    substring = (char *) malloc((len + 1) * sizeof(char));

    for (int i = 0; i <= len; i++) {
        substring[i] = '\0';
    }

    for (int i = 0; i < len; i++) {
        substring[i] = *(line + startIndex + i);

        substring[i] = line[startIndex + i];
        //*(substring+i) = *(line+startIndex+i);
    }

    substring[len + 1] = '\0';
    return substring;
}


//This method splits the string and returns its components based on the delimeter. [You don't need to know how it deos it exactly]
char **splitString(char *a_str, const char a_delim, int *numberOfComponents) {
    char **result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    *numberOfComponents = (int) count;

    /* Add space for terminating null string so caller
     knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char *) * count);


    char *components[count];
    for (int i = 0; i < count; i++) {
        components[i] = '\0';
    }

    int counter = 0;
    if (result) {
        size_t idx = 0;
        char *token = strtok(a_str, delim);

        while (token) {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);

            counter++;

            components[counter] = token;
        }
        *(result + idx) = 0;
    }

    return result;
}

//This method reads the file given the address. [You don't need to know how it deos it exactly]
char **readFile(char *fileAddress, int *numberOfLines) {
    int lines_allocated = 128;
    int max_line_len = 100;

    /* Allocate lines of text */
    char **words = (char **) malloc(sizeof(char *) * lines_allocated);
    if (words == NULL) {
        fprintf(stderr, "Out of memory (1).\n");
        exit(1);
    }

    FILE *fp = fopen(fileAddress, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(2);
    }

    int i;
    for (i = 0; 1; i++) {
        int j;

        /* Have we gone over our line allocation? */
        if (i >= lines_allocated) {
            int new_size;

            /* Double our allocation and re-allocate */
            new_size = lines_allocated * 2;
            words = (char **) realloc(words, sizeof(char *) * new_size);
            if (words == NULL) {
                fprintf(stderr, "Out of memory.\n");
                exit(3);
            }
            lines_allocated = new_size;
        }
        /* Allocate space for the next line */
        words[i] = malloc(max_line_len);
        if (words[i] == NULL) {
            fprintf(stderr, "Out of memory (3).\n");
            exit(4);
        }
        if (fgets(words[i], max_line_len - 1, fp) == NULL)
            break;

        /* Get rid of CR or LF at end of line */
        for (j = (int) (strlen(words[i])) - 1; j >= 0 && (words[i][j] == '\n' || words[i][j] == '\r'); j--);
        words[i][j + 1] = '\0';
    }
    /* Close file */
    fclose(fp);

    (*numberOfLines) = i;

    return words;
}


//This method converts a string to a number. [You don't need to know how it deos it exactly]
int convertToNumber(char *string) {
    int number = atoi(string);
    return number;
}


//[You don't need to know how it deos it exactly]
int numberOfItemsPerRecordInFile(char *fileName) {
    if (strcmp(fileName, CoursesFile) == 0) {
        return 2;
    } else if (strcmp(fileName, AccountsFile) == 0) {
        return 2;
    } else if (strcmp(fileName, StudentsFile) == 0) {
        return 7;
    } else if (strcmp(fileName, StudentsCoursesFile) == 0) {
        return 3;
    } else {
        return 1;
    }
}


//This method creates a student using the input parameter. You might need to use this sample to create other entity types like course , ...
struct Student
createAStudent(char *studentID, char *name, char *gender, int grade, char *address, int admission_year, char *courses[],
               int numberOfCourses) {
    struct Student *student = (struct Student *) malloc(sizeof(struct Student));

    (*student).studentID = studentID;
    (*student).name = name;
    (*student).gender = gender;
    (*student).grade = grade;
    (*student).address = address;
    (*student).admission_year = admission_year;
    (*student).courses = courses;
    (*student).numberOfCourses = numberOfCourses;

    return *student;
}


//This is what you need to learn and repeat for other entities. This method reads the students in the file of students and return an array of students.
struct Student *getListOfStudentFromFile(char *fileAddress, char *fileName, int *numberOfStudents) {
    int numberOfStudentsReadFromFileSoFar = 0;

    int numberOfLinesInTheFile = 0;
    char **lines = readFile(fileAddress, &numberOfLinesInTheFile);

    int numberOfLinesPerRecord = numberOfItemsPerRecordInFile(fileName);

    int numberOfRecords = numberOfLinesInTheFile / numberOfLinesPerRecord;


    struct Student *listOfStudents = (struct Student *) malloc(numberOfRecords * sizeof(struct Student));

    for (int k = 0; k < numberOfRecords; k++) {
        char *studentID = NULL;
        char *name = NULL;
        char *gender = NULL;
        int grade = 0;
        char *address = NULL;
        int admission_year = 0;
        char **courses = NULL;

        int numberOfCourses = 0;

        for (int i = 0; i < numberOfLinesPerRecord; i++) {
            int indexOfLine = k * numberOfLinesPerRecord + i;

            if (lines[indexOfLine] != NULL) {
                //printf("\n%s\n", lines[indexOfLine]);
                char firstCharacter = firstChar(lines[indexOfLine]);

                int lineLength = strLength(lines[indexOfLine]);

                int startIndex = getTheStartIndex(fileName, firstChar(lines[indexOfLine]));

                if (firstCharacter == '1') {
                    studentID = substring(lines[indexOfLine], startIndex, lineLength - 2);
                } else if (firstCharacter == '2') {
                    name = substring(lines[indexOfLine], startIndex, lineLength - 2);
                } else if (firstCharacter == '3') {
                    gender = substring(lines[indexOfLine], startIndex, lineLength - 2);
                } else if (firstCharacter == '4') {
                    char *gradeStr = substring(lines[indexOfLine], startIndex, lineLength - 2);

                    grade = convertToNumber(gradeStr);
                } else if (firstCharacter == '5') {
                    address = substring(lines[indexOfLine], startIndex, lineLength - 2);
                } else if (firstCharacter == '6') {
                    char *admissionYearStr = substring(lines[indexOfLine], startIndex, lineLength - 2);
                    admission_year = convertToNumber(admissionYearStr);
                } else if (firstCharacter == '7') {
                    int numberOfComponents = 0;
                    char *coursesStr = substring(lines[indexOfLine], startIndex, lineLength - 2);
                    courses = splitString(coursesStr, ',', &numberOfComponents);

                    numberOfCourses = numberOfComponents;
                }
            }//end of if
        }//end of second for

        struct Student student = createAStudent(studentID, name, gender, grade, address, admission_year, courses,
                                                numberOfCourses);
        listOfStudents[numberOfStudentsReadFromFileSoFar] = student;

        numberOfStudentsReadFromFileSoFar++;
    }//end of first for

    *numberOfStudents = numberOfStudentsReadFromFileSoFar;
    return listOfStudents;
}

//This method creates a student using the input parameter. You might need to use this sample to create other entity types like course , ...
struct Account createAnAccount(char *username, char *password) {
    struct Account *account = (struct Account *) malloc(sizeof(struct Account));

    account->username = username;
    account->password = password;

    return *account;
}

struct Account *getListOfAccountFromFile(char *fileAddress, char *fileName, int *numberOfAccounts) {
    int numberOfAccountsReadFromFileSoFar = 0;

    int numberOfLinesInTheFile = 0;
    char **lines = readFile(fileAddress, &numberOfLinesInTheFile);

    int numberOfLinesPerRecord = numberOfItemsPerRecordInFile(fileName);

    int numberOfRecords = numberOfLinesInTheFile / numberOfLinesPerRecord;

    struct Account *listOfAccounts = (struct Account *) malloc(numberOfRecords * sizeof(struct Account));

    for (int k = 0; k < numberOfRecords; k++) {
        char *username = NULL;
        char *password = NULL;

        for (int i = 0; i < numberOfLinesPerRecord; i++) {
            int indexOfLine = k * numberOfLinesPerRecord + i;

            if (lines[indexOfLine] != NULL) {
                //printf("\n%s\n", lines[indexOfLine]);
                char firstCharacter = firstChar(lines[indexOfLine]);

                int lineLength = strLength(lines[indexOfLine]);

                int startIndex = getTheStartIndex(fileName, firstChar(lines[indexOfLine]));

                if (firstCharacter == '1') {
                    username = substring(lines[indexOfLine], startIndex, lineLength - 2);
                } else if (firstCharacter == '2') {
                    password = substring(lines[indexOfLine], startIndex, lineLength - 2);
                }
            }//end of if
        }//end of second for

        struct Account account = createAnAccount(username, password);
        listOfAccounts[numberOfAccountsReadFromFileSoFar] = account;

        numberOfAccountsReadFromFileSoFar++;
    }//end of first for

    *numberOfAccounts = numberOfAccountsReadFromFileSoFar;
    return listOfAccounts;
}

struct Course createACourse(char *courseId, char *name) {
    struct Course *course = (struct Course *) malloc(sizeof(struct Course));

    course->courseID = courseId;
    course->name = name;
    return *course;
}

struct Course *getListOfCourseFromFile(char *fileAddress, char *fileName, int *numberOfCourses) {
    int numberOfCoursesReadFromFileSoFar = 0;

    int numberOfLinesInTheFile = 0;
    char **lines = readFile(fileAddress, &numberOfLinesInTheFile);

    int numberOfLinesPerRecord = numberOfItemsPerRecordInFile(fileName);

    int numberOfRecords = numberOfLinesInTheFile / numberOfLinesPerRecord;

    struct Course *listOfCourses = (struct Course *) malloc(numberOfRecords * sizeof(struct Course));

    for (int k = 0; k < numberOfRecords; k++) {
        char *courseID = NULL;
        char *name = NULL;

        for (int i = 0; i < numberOfLinesPerRecord; i++) {
            int indexOfLine = k * numberOfLinesPerRecord + i;

            if (lines[indexOfLine] != NULL) {
                //printf("\n%s\n", lines[indexOfLine]);
                char firstCharacter = firstChar(lines[indexOfLine]);

                int lineLength = strLength(lines[indexOfLine]);

                int startIndex = getTheStartIndex(fileName, firstChar(lines[indexOfLine]));

                if (firstCharacter == '1') {
                    courseID = substring(lines[indexOfLine], startIndex, lineLength - 2);
                } else if (firstCharacter == '2') {
                    name = substring(lines[indexOfLine], startIndex, lineLength - 2);
                }
            }//end of if
        }//end of second for

        struct Course course = createACourse(courseID, name);
        listOfCourses[numberOfCoursesReadFromFileSoFar] = course;

        numberOfCoursesReadFromFileSoFar++;
    }//end of first for

    *numberOfCourses = numberOfCoursesReadFromFileSoFar;
    return listOfCourses;
}

struct StudentCourse createAStudentCourse(char *studentID, char *courseID, int mark) {
    struct StudentCourse *course = (struct StudentCourse *) malloc(sizeof(struct StudentCourse));

    course->studentID = studentID;
    course->courseID = courseID;
    course->mark = mark;
    return *course;
}

struct StudentCourse *getListOfStudentCourseFromFile(char *fileAddress, char *fileName, int *numberOfStudentCourses) {
    int numberOfCoursesReadFromFileSoFar = 0;

    int numberOfLinesInTheFile = 0;
    char **lines = readFile(fileAddress, &numberOfLinesInTheFile);

    int numberOfLinesPerRecord = numberOfItemsPerRecordInFile(fileName);

    int numberOfRecords = numberOfLinesInTheFile / numberOfLinesPerRecord;

    struct StudentCourse *listOfStudentCourses = (struct StudentCourse *) malloc(
            numberOfRecords * sizeof(struct StudentCourse));

    for (int k = 0; k < numberOfRecords; k++) {
        char *studentID = NULL;
        char *courseID = NULL;
        int mark;

        for (int i = 0; i < numberOfLinesPerRecord; i++) {
            int indexOfLine = k * numberOfLinesPerRecord + i;

            if (lines[indexOfLine] != NULL) {
                //printf("\n%s\n", lines[indexOfLine]);
                char firstCharacter = firstChar(lines[indexOfLine]);

                int lineLength = strLength(lines[indexOfLine]);

                int startIndex = getTheStartIndex(fileName, firstChar(lines[indexOfLine]));

                if (firstCharacter == '1') {
                    studentID = substring(lines[indexOfLine], startIndex, lineLength - 2);
                } else if (firstCharacter == '2') {
                    courseID = substring(lines[indexOfLine], startIndex, lineLength - 2);
                } else if (firstCharacter == '3') {
                    char *markStr = substring(lines[indexOfLine], startIndex, lineLength - 2);
                    mark = convertToNumber(markStr);
                }
            }//end of if
        }//end of second for

        struct StudentCourse course = createAStudentCourse(studentID, courseID, mark);
        listOfStudentCourses[numberOfCoursesReadFromFileSoFar] = course;

        numberOfCoursesReadFromFileSoFar++;
    }//end of first for

    *numberOfStudentCourses = numberOfCoursesReadFromFileSoFar;
    return listOfStudentCourses;
}

void printLogin() {
    printf("************************************************************\n"
                   "Please enter your account to login:\n"
                   "************************************************************\n"
                   "Username:\n"
                   "Password:\n");
}

void printWelcome() {
    printf("************************************************************\n"
                   "Welcome to Cornerstone International College of Canada.\n"
                   "************************************************************\n\n");
}

void printErrorLogin() {
    printf("************************************************************\n"
                   "Your account does not exist. Please try again!\n"
                   "************************************************************\n\n");
}

void printMenu() {
    printf("************************************************************\n"
                   "Select from the options:\n"
                   "************************************************************\n"
                   "—-[1] Print my enrolment certificate\n"
                   "—-[2] Print my courses\n"
                   "—-[3] Print my transcript\n"
                   "—-[4] Print my GPA\n"
                   "—-[5] Print my ranking among all students in the college\n"
                   "—-[6] List all available courses\n"
                   "—-[7] List all students\n"
                   "-—[8] Logout\n"
                   "-—[9] Exit\n"
                   "************************************************************\n"
                   "Enter the number corresponding to each item to proceed:\n");
}

void printMyCertificate(char *name, char *studentId) {
    printf("Dear Sir/Madam,\n"
                   "This is to certify that %s %s with student id %s is a student at grade %d at CICCC.\n"
                   "%s was admitted to our college in %d and has taken %d course(s). Currently %s resides at %s.\n"
                   "\n"
                   "If you have any question, please don’t hesitate to contact us.\n"
                   "Thanks,\n"
                   "Williams,\n\n",
           getMrMs(myStudent.gender),
           name,
           studentId,
           myStudent.grade,
           getHeShe(myStudent.gender),
           myStudent.admission_year,
           myStudent.numberOfCourses,
           getheshe(myStudent.gender),
           myStudent.address);
}

char *getMrMs(char *gender) {
    if (strcmp(gender, "male") == 0)
        return "Mr.";
    else
        return "Ms.";
}

char *getHeShe(char *gender) {
    if (strcmp(gender, "male") == 0)
        return "He";
    else
        return "She";
}

char *getheshe(char *gender) {
    if (strcmp(gender, "male") == 0)
        return "he";
    else
        return "she";
}

void printMyCourses() {
    printf("Hi %s %s,\n"
                   "You have taken the following courses:\n", getMrMs(myStudent.gender), myStudent.name);
    for (int i = 0; i < myStudent.numberOfCourses; ++i) {
        printf("%d) %s: %s\n", i + 1, myCourseList[i].courseID, myCourseList[i].name);
    }
    puts("");
}

void printMyTranscript() {
    printf("Hi %s %s, Here is your transcript:\n", getMrMs(myStudent.gender), myStudent.name);
    for (int i = 0; i < myStudentCourseNum; ++i) {
        struct StudentCourse c = myStudentCourseList[i];
        printf("%d) %s: %s: %d\n", i+1, myStudentCourseList[i].courseID, getCourseName(c.courseID), c.mark);
    }
    puts("");
}

char *getCourseName(char *courseID) {
    for (int i = 0; i < numberOfCourses; ++i) {
        if (strcmp(listOfCourses[i].courseID, courseID) == 0)
            return listOfCourses[i].name;
    }
    return NULL;
}

void printMyGpa() {
    printf("Hi %s %s,\n"
                   "Your GPA is %f\n\n", getMrMs(myStudent.gender), myStudent.name, myGPA);
}

void printMyRanking() {
    printf("Hi %s %s,\n"
                   "Your GPA is %f and therefore your rank is %d.\n\n",
           getMrMs(myStudent.gender), myStudent.name, myGPA, myRank);
}

void printCoursesList() {
    printf("The following courses are offered in CICCC:\n");
    for (int i = 0; i < numberOfCourses; ++i) {
        printf("%d) %s: %s\n", i + 1, listOfCourses[i].courseID, listOfCourses[i].name);
    }
    puts("");
}

void printStudents() {
    printf("There are %d students in CICCC as following:\n", numberOfStudents);
    for (int i = 0; i < numberOfStudents; ++i) {
        printf("%d) %s: %s\n", i + 1, listOfStudents[i].name, listOfStudents[i].studentID);
    }
    puts("");
}