//
//  main.cpp
//  Phase1
//
//  Created by Matthew Ehinger on 2/5/15.
//  Copyright (c) 2015 Matthew Ehinger. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include "Course.h"
#include "Quarter.h"

using namespace std;

void iterateThroughAllCourse(Course *arr, int num) {
    for(int i = 0; i < num; i++) {
        std::cout << arr[i].getNumHours() << std::endl;
    }
}

void iterateThroughAllQuarters(Quarter *arr, int numQuarters) {
    Course c1, c2, c3, c4;
    for(int i = 0; i < numQuarters; i++) {
        Quarter thisQuarter = arr[i];
        cout << "Quarter " << thisQuarter.getQuarterIndex() << endl;
        c1 = thisQuarter.getCourseOne();
        c2 = thisQuarter.getCourseTwo();
        c3 = thisQuarter.getCourseThree();
        c4 = thisQuarter.getCourseFour();
        
        string c1_s, c2_s, c3_s, c4_s;
        
        
        if(c1.isEmpty()) {
            c1_s = "Course not assigned";
        }
        else {
            c1_s = "C" + to_string(c1.getClassId());
        }
        
        if(c2.isEmpty()) {
            c2_s = "Course not assigned";
        }
        else {
            c2_s = "C" + to_string(c2.getClassId());
        }
        
        if(c3.isEmpty()) {
            c3_s = "Course not assigned";
        }
        else {
            c3_s = "C" + to_string(c3.getClassId());
        }
        
        if(c4.isEmpty()) {
            c4_s = "Course not assigned";
        }
        else {
            c4_s = "C" + to_string(c4.getClassId());
        }
        
        cout << "Class 1: " << c1_s << endl;
        cout << "Class 2: " << c2_s << endl;
        cout << "Class 3: " << c3_s << endl;
        cout << "Class 4: " << c4_s << endl;
        cout << "----------------------------------------" << endl;
    }
}


//void assignClassesToQuarters(Course *classArr, Quarter *quarterArr, int numClasses, int numQuarters) {
//    
//    
//    vector<Course>legalCourses;
//    int currentQuarter = 1;
//    
//    while(currentQuarter <= numQuarters) {
//        
//        Quarter thisQuarter = quarterArr[currentQuarter - 1]; //subtract one because arrays are 0 indexed
//        if(thisQuarter.isFull())
//            continue;
//        else {
//            
//            //finds all courses that can be taken this quarter
//            for(int i = 0;  i < numClasses; i++) {
//                if(classArr[i].getEarliestQuarter() <= currentQuarter)
//                    legalCourses.push_back(classArr[i]);
//            }
//            
//            
//            
//            
//            
//        }
//    }
//}

//int findBestAssignmentOfClassesToQuarter(Course *classArr, Quarter q, int numClasses) {
//    if(q.isFull())
//        return q.getTotalHours();
//    else {
//        for(int i = 0; i < numClasses; i++) {
//            Course thisCourse = classArr[i];
//            if(thisCourse.getEarliestQuarter() <= q.getQuarterIndex()) {
//                if(!thisCourse.isAssigned()) {
//                    classArr[i] = q.assignClass(thisCourse);
//                    findBestAssignmentOfClassesToQuarter(classArr, q, numClasses);
//                }
//            }
//        }
//        return -1;
//    }
//}

float returnTotalWorkHoursWithAssignment(vector<Course>courses, Quarter q) {
    if(q.isFull())
        return q.getTotalHours();
    else {
        Course thisCourse = courses.front();
        courses.erase(courses.begin());
        q.assignClass(thisCourse);
        return returnTotalWorkHoursWithAssignment(courses, q);
    }
    
}

void fillInEmptyCourses(Course *classArr, Quarter *quarterArr, int numClasses, int numQuarters) {
    for(int i = 0; i < numQuarters; i++) {
        Quarter thisQuarter = quarterArr[i];
        vector<Course>legalCourses;
        
        //find courses that could be assigned to this quarter
        for(int j = 0; j < numClasses; j++) {
            Course thisCourse = classArr[j];
            if(!thisCourse.isAssigned() && thisCourse.getEarliestQuarter() <= thisQuarter.getQuarterIndex()) {
                legalCourses.push_back(thisCourse);
            }
        }
        
        float optimalNumHours = 47.9;
        int optimalDecision;
        float bestDifferenceSoFar = 100000;
        
        for(int i = 0; i < legalCourses.size(); i++) {
            Course thisCourse = legalCourses[i];
            thisQuarter.assignClass(thisCourse);
            legalCourses.erase(legalCourses.begin() + i);
            float totalHours = returnTotalWorkHoursWithAssignment(legalCourses, thisQuarter);
            float tempDiff = fabs(totalHours - optimalNumHours);
            if(tempDiff < bestDifferenceSoFar) {
                bestDifferenceSoFar = tempDiff;
                optimalDecision = i;
            }
        }
        
    }
}

int returnMinOfVector(vector<Course>vec) {
    int min = -1;
    float minSoFar = 1000;
    for(int i = 0; i < vec.size(); i++) {
        Course c = vec[i];
        if(c.getNumDepCourse() < minSoFar) {
            minSoFar = c.getNumDepCourse();
            min = i;
        }
    }
    
    return min;
}

Course * overwriteCourseInArray(Course * arr, Course c, int numCourses) {
    for(int i = 0; i < numCourses; i++) {
        Course c2 = arr[i];
        if(c2.getClassId() == c.getClassId()) {
            arr[i] = c;
            break;
        }
    }
    return arr;
}

Quarter * assignClassesGreedily(Course *classArr, Quarter *quarterArr, int numClasses, int numQuarters) {
    for(int i = 0; i < numQuarters; i++) {
        Quarter thisQuarter = quarterArr[i];
        
        vector<Course>legalCourses;
        
        //find courses that could be assigned to this quarter
        for(int j = 0; j < numClasses; j++) {
            Course thisCourse = classArr[j];
            if(!thisCourse.isAssigned() && thisCourse.getEarliestQuarter() <= thisQuarter.getQuarterIndex()) {
                legalCourses.push_back(thisCourse);
            }
        }
        
        while(legalCourses.size() > 4) {
            int min = returnMinOfVector(legalCourses);
            legalCourses.erase(legalCourses.begin() + min);
        }
        
        for(int j = 0; j < legalCourses.size(); j++) {
            Course c = legalCourses[j];
            c = thisQuarter.assignClass(c);
            classArr = overwriteCourseInArray(classArr, c, numClasses);
        }
        quarterArr[i] = thisQuarter;
    }
    
    return quarterArr;
}







//this functions assigns courses to quarters based on the earliest possible quarter that you can take the course
Quarter * assignClassesBasedOnEarliestTaken(Course *classArr, Quarter *quarterArr, int numClasses, int numQuarters) {
    //this is the return array that stores all of the quarters
    Quarter *returnArr = new Quarter[numQuarters];
    
    //Outer loop to iterate through the quarters. Starts at the last quarter
    for(int i = numQuarters - 1; i >= 0; i--) {
        
        //the current quarter
        Quarter thisQuarter = quarterArr[i];
        int currentQuarterIndex = i+1;
        
        //inner loop iterates through all of the courses
        for(int j = 0; j < numClasses; j++) {
            
            //current course in the iteration
            Course thisCourse = classArr[j];
            
            //checks if the course can be taken in this quarter and if the course is not already assigned
            if(thisCourse.getEarliestQuarter() == currentQuarterIndex && !thisCourse.isAssigned()) {
                
                //checks if the quarter is already full
                if(!thisQuarter.isFull()) {
                    
                    //assigns the course to this quarter
                    thisCourse = thisQuarter.assignClass(thisCourse);
                    classArr[j] = thisCourse;
                }
            }
        }
        returnArr[i] = thisQuarter;
    }
    
    //returns the updated quarter array
    return returnArr;
}


////assigns classes to the last quarter that can be taken at earliest during the last quarter
//Quarter assignClassesToLastQuarter(Course *classArr, Quarter *quarterArr, int numClasses, int numQuarters) {
//    //gets the last quarter
//    Quarter lastQuarter = quarterArr[numQuarters - 1];
//    
//    //iterates through all classes
//    for(int i = 0; i < numClasses; i++) {
//        Course thisCourse = classArr[i];
//        
//        //checks if the earliest you can take this course is the last quarter and if the course has not already been assigned
//        if(thisCourse.getEarliestQuarter() == numQuarters && !thisCourse.isAssigned()) {
//            if(!lastQuarter.isFull()) {
//                lastQuarter.assignClass(thisCourse);
//            }
//            else {
//                cout << "invalid course scheduling: can not assign course" << endl;
//            }
//        }
//    }
//    
//    return lastQuarter;
//}


int main(int argc, const char * argv[]) {
    
    //create the course objects
    Course C01 = Course(1 , 10.0 , 3, 3, 0);
    Course C02 = Course(2 , 22.5 , 1, 4, 0);
    Course C03 = Course(3 , 7.0  , 0, 5, 0);
    Course C04 = Course(4 , 15.0 , 0, 4, 0);
    Course C05 = Course(5 , 5.5  , 6, 2, 0);
    Course C06 = Course(6 , 9.0  , 3, 2, 0);
    Course C07 = Course(7 , 22.0 , 6, 1, 0);
    Course C08 = Course(8 , 19.0 , 0, 1, 0);
    Course C09 = Course(9 , 7.5  , 4, 1, 0);
    Course C10 = Course(10, 5.5  , 4, 1, 0);
    Course C11 = Course(11, 9.5  , 2, 2, 0);
    Course C12 = Course(12, 9.5  , 1, 3, 0);
    Course C13 = Course(13, 5.5  , 0, 4, 0);
    Course C14 = Course(14, 6.0  , 1, 1, 0);
    Course C15 = Course(15, 16.5 , 3, 2, 0);
    Course C16 = Course(16, 25.5 , 0, 3, 0);
    Course C17 = Course(17, 14.5 , 0, 3, 0);
    Course C18 = Course(18, 6.5  , 0, 3, 0);
    Course C19 = Course(19, 10.5 , 0, 3, 0);
    Course C20 = Course(20, 12.5 , 0, 3, 0);
    
    //create the quarter objects
    Quarter q1 = Quarter(1);
    Quarter q2 = Quarter(2);
    Quarter q3 = Quarter(3);
    Quarter q4 = Quarter(4);
    Quarter q5 = Quarter(5);
    
    //arrays of courses
    Course arr[] = {C01, C02, C03, C04, C05, C06, C07, C08, C09,
        C10, C11, C12, C13, C14, C15, C16, C17, C18, C19, C20};
    
    //arrays of quarters
    Quarter qArr[] = {q1, q2, q3, q4, q5};
    
    //Quarter *qArr2 = assignClassesBasedOnEarliestTaken(arr, qArr, 20, 5);
    //iterateThroughAllQuarters(qArr2, 5);
    
    
    Quarter *qArr2 = assignClassesGreedily(arr, qArr, 20, 5);
    iterateThroughAllQuarters(qArr2, 5);
    
    return 0;
}
