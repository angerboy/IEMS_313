//
//  Course.cpp
//  Phase1
//
//  Created by Matthew Ehinger on 2/5/15.
//  Copyright (c) 2015 Matthew Ehinger. All rights reserved.
//

#include "Course.h"

Course::Course() {
    classID = -1;
}

//makes a new Course object
Course::Course(int ID, float hrs, int numDep, int earliest, int latest) {
    classID = ID;
    hrsPerWeek = hrs;
    numOfDependentCourses = numDep;
    earliestQuarter = earliest;
    latestQuarter = latest;
    quarterBeingTaken = -1;
}


//assigns a quarter index to this class
void Course::assignQuarter(int index) {
    quarterBeingTaken = index;
}

//returns number of hours per work for this class
float Course::getNumHours() {
    return hrsPerWeek;
}

//returns earliest quarter
int Course::getEarliestQuarter() {
    return earliestQuarter;
}

bool Course:: isAssigned() {
    return !(quarterBeingTaken == -1);
}

int Course::getClassId() {
    return classID;
}

bool Course::isEmpty() {
    if(classID == -1)
        return true;
    return false;
}

int Course::getNumDepCourse() {
    return numOfDependentCourses;
}

int Course::getQuarterAssigned() {
    return quarterBeingTaken;
}

vector<int> Course::getPrereqs() {
    return prereqs;
}

vector<int> Course::getDeps() {
    return dependents;
}

void Course::setPrereqs(vector<int>p) {
    prereqs = p;
}

void Course::setDeps(vector<int>d) {
    dependents = d;
}



