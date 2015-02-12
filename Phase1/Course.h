//
//  Course.h
//  Phase1
//
//  Created by Matthew Ehinger on 2/5/15.
//  Copyright (c) 2015 Matthew Ehinger. All rights reserved.
//

#ifndef __Phase1__Course__
#define __Phase1__Course__

#include <stdio.h>

class Course {

    //number of hours of work per week for this class
    float hrsPerWeek;

    //number of courses that have this course as an acestor in the prereq "tree"
    int numOfDependentCourses;

    //earliest quarter you can take this class
    int earliestQuarter;

    //latest quarter you can take this class (based on the prereq tree)
    int latestQuarter;
    
    //index of quarter this class is being taken
    int quarterBeingTaken;
    
    //class id
    int classID;
    
public: //functions
    Course(); //default constructor
    Course(int ID, float hrs, int numDep, int earliest, int latest); //constructor
    void assignQuarter(int index);//assigns this class a quarter
    float getNumHours(); //gets number of hours a week this class entails
    int getEarliestQuarter(); //gets the earliest quarter you can take this class
    bool isAssigned(); //checks if class is assigned
    int getClassId(); //gets course id
    bool isEmpty(); //returns true if course is empty
    int getNumDepCourse(); //returns getter for numDepCourses
};


#endif /* defined(__Phase1__Course__) */
