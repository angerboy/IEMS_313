//
//  Quarter.h
//  Phase1
//
//  Created by Matthew Ehinger on 2/5/15.
//  Copyright (c) 2015 Matthew Ehinger. All rights reserved.
//

#ifndef __Phase1__Quarter__
#define __Phase1__Quarter__

#include <stdio.h>
#include "Course.h"

class Quarter {
    //index of the quarter (1 indexed)
    int quarterIndex;
    
    //first class being taken this quarter
    Course classOne;
    
    //second class being taken this quarter
    Course classTwo;
    
    //third class being taken this quarter
    Course classThree;
    
    //fourth class being taken this quarter
    Course classFour;
    
    //number of classes assigned to this quarter
    int numCourses;
    
    //total number of hours per week
    float totalNumHours;
    
public: //functions
    //default constructor
    Quarter();
    
    //constructor with index
    Quarter(int index);
    
    //assigns a new class to this quarter
    Course assignClass(Course newClass);
    
    //returns true if it is full, false otherwise
    bool isFull();
    
    //returns the index of the quarter
    int getQuarterIndex();
    
    //return totalNumberOfHours
    int getTotalHours();
    
    //returns course 1
    Course getCourseOne();
    
    //returns course 2
    Course getCourseTwo();
    
    //returns course 3
    Course getCourseThree();
    
    //returns course 4
    Course getCourseFour();
    
};



#endif /* defined(__Phase1__Quarter__) */
