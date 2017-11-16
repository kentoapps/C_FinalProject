//
// Created by Kento Uchida on 2017/11/15.
//
#include <stdio.h>

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
                   "************************************************************\n");
}

void printErrorLogin() {
    printf("************************************************************\n"
                   "Your account does not exist. Please try again!\n"
                   "************************************************************\n");
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

void printMyCertificate() {
    printf("Dear Sir/Madam,\n"
                   "This is to certify that Mr. Peter Brown with student id 7813007 is a student at grade 1 at CICCC. He was admitted to our college in 2011 and has taken 1 course(s). Currently he resides at 850 West Vancouver, Vancouver.\n"
                   "\n"
                   "If you have any question, please don’t hesitate to contact us.\n"
                   "Thanks,\n"
                   "Williams,\n");
}

void printMyCourses() {
    printf("Hi Mr. Peter Brown,\n"
                   "You have taken the following courses:\n"
                   "1) MADP101: Objective-C\n"
                   "2) MADP202: Project Management\n"
                   "3) MADP301: Java Programming\n"
                   "4) MADP401: Android Programming\n");
}

void printMyTranscript() {
    printf("Hi Mr. Peter Brown, Here is your transcript:\n"
                   "1) MADP101: Objective-C: 80\n"
                   "2) MADP202: Project Management: 45\n"
                   "3) MADP301: Java Programming: 64\n"
                   "4) MADP401: Android Programming: 70\n"
                   "YOUR GPA IS: 64.75\n");
}

void printMyGpa() {
    printf("Hi Mr. Peter Brown,\n"
                   "Your GPA is 64.75");
}

void printMyRanking() {
    printf("Hi Mr. Peter Brown,\n"
                   "Your GPA is 64.75 and therefore your rank is 3.\n");
}

void pringCoursesList() {
    printf("The following courses are offered in CICCC:\n"
                   "\n"
                   "1) MADP101: Objective-C\n"
                   "2) MADP102: Object-Oriented Programming\n"
                   "3) MADP201: Problem Solving\n"
                   "4) MADP202: Project Management\n"
                   "5) MADP301: Java Programming\n"
                   "6) MADP302: Web Development\n"
                   "7) MADP401: Android Programming\n"
                   "8) MADP402: iOS Applications\n");
}

void printStudents() {
    printf("There are 4 students in CICCC as following:\n"
                   "1) Peter Brown: 7813007\n"
                   "2) Joseph Rod: 812345\n"
                   "3) Cristina Li: 8012333\n"
                   "4) Adams Wang: 7812999\n");
}