//
//  Quarter.cpp
//  Phase1
//
//  Created by Matthew Ehinger on 2/5/15.
//  Copyright (c) 2015 Matthew Ehinger. All rights reserved.
//

#include "Quarter.h"

Quarter::Quarter() {
    quarterIndex = -1;
}

// makes a new Quarter object with index 'index'
Quarter::Quarter(int index) {
    quarterIndex = index;
    totalNumHours = 0;
    numCourses = 0;
}

/* method to assign a new class to this course
 returns true if the assignment is succesful
 returns false if the quarter is full */
Course Quarter::assignClass(Course newCourse) {
    if(numCourses == 0) {
        classOne = newCourse;
        numCourses++;
        totalNumHours = totalNumHours + newCourse.getNumHours();
        newCourse.assignQuarter(quarterIndex);
        return newCourse;
    }
    else if(numCourses == 1) {
        classTwo = newCourse;
        numCourses++;
        totalNumHours = totalNumHours + newCourse.getNumHours();
        newCourse.assignQuarter(quarterIndex);
        return newCourse;
    }
    else if(numCourses == 2) {
        classThree = newCourse;
        numCourses++;
        totalNumHours = totalNumHours + newCourse.getNumHours();
        newCourse.assignQuarter(quarterIndex);
        return newCourse;
    }
    else if(numCourses == 3) {
        classFour = newCourse;
        numCourses++;
        totalNumHours = totalNumHours + newCourse.getNumHours();
        newCourse.assignQuarter(quarterIndex);
        return newCourse;
    }
    else
        return newCourse;
}

float Quarter::getTotalHours() {
    return totalNumHours;
}

//checks if the quarter is full
bool Quarter::isFull() {
    return (numCourses == 4);
}

//returns the index of the quarter
int Quarter::getQuarterIndex() {
    return quarterIndex;
}

Course Quarter::getCourseOne() {
    return classOne;
}

Course Quarter::getCourseTwo() {
    return classTwo;
}

Course Quarter::getCourseThree() {
    return classThree;
}

Course Quarter::getCourseFour() {
    return classFour;
}
