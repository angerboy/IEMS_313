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

//returns aggregate of number of dependent courses + workload
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


void calculateAverageNumberOfHours(Quarter *quarterArr, int numQuarters) {
    float sum = 0;
    for(int i = 0; i < numQuarters; i++) {
        Quarter q = quarterArr[i];
        cout << "total hours: " << q.getTotalHours() << endl;
    }
}

bool isValidDest(Course c, int dest, Course * arr) {
    vector<int>p = c.getPrereqs();
    for(int i = 0; i < p.size(); i++) {
        int index = p[i];
        if(index == -1)
            break;
        Course t_c = arr[index];
        if(t_c.getQuarterAssigned() >= dest)
            return false;
    }
    
    vector<int>q = c.getDeps();
    for(int i = 0; i < q.size(); i++) {
        int index = q[i];
        if(index == -1)
            break;
        Course t_c = arr[index];
        if(t_c.getQuarterAssigned() <= dest)
            return false;
    }
    return true;
}

bool isValidSwap(Course c1, Course c2, Course * arr) {
    int c1_quarter = c1.getQuarterAssigned();
    int c2_quarter = c2.getQuarterAssigned();
    
    return (isValidDest(c1, c2_quarter, arr) && isValidDest(c2, c1_quarter, arr));
}

Course * constructVectorsForCourses(Course * arr) {
    static const int c1_p[] = {4}; //4 = Course 5 because arrays start at index 0
    static const int c1_d[] = {1,2,3};
    
    vector<int> c1P(c1_p, c1_p + sizeof(c1_p) / sizeof(c1_p[0]));
    vector<int> c1D(c1_d, c1_d + sizeof(c1_d) / sizeof(c1_d[0]));
    
    Course c1 = arr[0];
    c1.setPrereqs(c1P);
    c1.setDeps(c1D);
    arr[0] = c1;
    
    static const int c2_p[] = {0,4,5};
    static const int c2_d[] = {2};
    
    vector<int> c2P(c2_p, c2_p + sizeof(c2_p) / sizeof(c2_p[0]));
    vector<int> c2D(c2_d, c2_d + sizeof(c2_d) / sizeof(c2_d[0]));
    
    Course c2 = arr[1];
    c2.setPrereqs(c2P);
    c2.setDeps(c2D);
    arr[1] = c2;
    
    static const int c3_p[] = {1,4,5};
    static const int c3_d[] = {-1};
    
    vector<int> c3P(c3_p, c3_p + sizeof(c3_p) / sizeof(c3_p[0]));
    vector<int> c3D(c3_d, c3_d + sizeof(c3_d) / sizeof(c3_d[0]));
    
    Course c3 = arr[2];
    c3.setPrereqs(c3P);
    c3.setDeps(c3D);
    arr[2] = c3;
    
    static const int c4_p[] = {0};
    static const int c4_d[] = {-1};
    
    vector<int> c4P(c4_p, c4_p + sizeof(c4_p) / sizeof(c4_p[0]));
    vector<int> c4D(c4_d, c4_d + sizeof(c4_d) / sizeof(c4_d[0]));
    
    Course c4 = arr[3];
    c4.setPrereqs(c4P);
    c4.setDeps(c4D);
    arr[3] = c4;
    
    static const int c5_p[] = {6};
    static const int c5_d[] = {0,1,2,16,3,15};
    
    vector<int> c5P(c5_p, c5_p + sizeof(c5_p) / sizeof(c5_p[0]));
    vector<int> c5D(c5_d, c5_d + sizeof(c5_d) / sizeof(c5_d[0]));
    
    Course c5 = arr[4];
    c5.setPrereqs(c5P);
    c5.setDeps(c5D);
    arr[4] = c5;
    
    static const int c6_p[] = {8};
    static const int c6_d[] = {1,2,19};
    
    vector<int> c6P(c6_p, c6_p + sizeof(c6_p) / sizeof(c6_p[0]));
    vector<int> c6D(c6_d, c6_d + sizeof(c6_d) / sizeof(c6_d[0]));
    
    Course c6 = arr[5];
    c6.setPrereqs(c6P);
    c6.setDeps(c6D);
    arr[5] = c6;
    
    static const int c7_p[] = {-1};
    static const int c7_d[] = {0,1,2,3,4,15,16};
    
    vector<int> c7P(c7_p, c7_p + sizeof(c7_p) / sizeof(c7_p[0]));
    vector<int> c7D(c7_d, c7_d + sizeof(c7_d) / sizeof(c7_d[0]));
    
    Course c7 = arr[6];
    c7.setPrereqs(c7P);
    c7.setDeps(c7D);
    arr[6] = c7;
    
    static const int c8_p[] = {-1};
    static const int c8_d[] = {-1};
    
    vector<int> c8P(c8_p, c8_p + sizeof(c8_p) / sizeof(c8_p[0]));
    vector<int> c8D(c8_d, c8_d + sizeof(c8_d) / sizeof(c8_d[0]));
    
    Course c8 = arr[7];
    c8.setPrereqs(c8P);
    c8.setDeps(c8D);
    arr[7] = c8;
    
    static const int c9_p[] = {-1};
    static const int c9_d[] = {1,2,5,19};
    
    vector<int> c9P(c9_p, c9_p + sizeof(c9_p) / sizeof(c9_p[0]));
    vector<int> c9D(c9_d, c9_d + sizeof(c9_d) / sizeof(c9_d[0]));
    
    Course c9 = arr[8];
    c9.setPrereqs(c9P);
    c9.setDeps(c9D);
    arr[8] = c9;
    
    static const int c10_p[] = {-1};
    static const int c10_d[] = {10,11,12,17,18};
    
    vector<int> c10P(c10_p, c10_p + sizeof(c10_p) / sizeof(c10_p[0]));
    vector<int> c10D(c10_d, c10_d + sizeof(c10_d) / sizeof(c10_d[0]));
    
    Course c10 = arr[9];
    c10.setPrereqs(c10P);
    c10.setDeps(c10D);
    arr[9] = c10;
    
    static const int c11_p[] = {9};
    static const int c11_d[] = {17,18};
    
    vector<int> c11P(c11_p, c11_p + sizeof(c11_p) / sizeof(c11_p[0]));
    vector<int> c11D(c11_d, c11_d + sizeof(c11_d) / sizeof(c11_d[0]));
    
    Course c11 = arr[10];
    c11.setPrereqs(c11P);
    c11.setDeps(c11D);
    arr[10] = c11;
    
    static const int c12_p[] = {9,14};
    static const int c12_d[] = {12};
    
    vector<int> c12P(c12_p, c12_p + sizeof(c12_p) / sizeof(c12_p[0]));
    vector<int> c12D(c12_d, c12_d + sizeof(c12_d) / sizeof(c12_d[0]));
    
    Course c12 = arr[11];
    c12.setPrereqs(c12P);
    c12.setDeps(c12D);
    arr[11] = c12;
    
    static const int c13_p[] = {11};
    static const int c13_d[] = {-1};
    
    vector<int> c13P(c13_p, c13_p + sizeof(c13_p) / sizeof(c13_p[0]));
    vector<int> c13D(c13_d, c13_d + sizeof(c13_d) / sizeof(c13_d[0]));
    
    Course c13 = arr[12];
    c13.setPrereqs(c13P);
    c13.setDeps(c13D);
    arr[12] = c13;
    
    static const int c14_p[] = {-1};
    static const int c14_d[] = {11,12,14,15};
    
    vector<int> c14P(c14_p, c14_p + sizeof(c14_p) / sizeof(c14_p[0]));
    vector<int> c14D(c14_d, c14_d + sizeof(c14_d) / sizeof(c14_d[0]));
    
    Course c14 = arr[13];
    c14.setPrereqs(c14P);
    c14.setDeps(c14D);
    arr[13] = c14;
    
    static const int c15_p[] = {13};
    static const int c15_d[] ={11,12,15};
    
    vector<int> c15P(c15_p, c15_p + sizeof(c15_p) / sizeof(c15_p[0]));
    vector<int> c15D(c15_d, c15_d + sizeof(c15_d) / sizeof(c15_d[0]));
    
    Course c15 = arr[14];
    c15.setPrereqs(c15P);
    c15.setDeps(c15D);
    arr[14] = c15;
    
    static const int c16_p[] = {4,14};
    static const int c16_d[] = {-1};
    
    vector<int> c16P(c16_p, c16_p + sizeof(c16_p) / sizeof(c16_p[0]));
    vector<int> c16D(c16_d, c16_d + sizeof(c16_d) / sizeof(c16_d[0]));
    
    Course c16 = arr[15];
    c16.setPrereqs(c16P);
    c16.setDeps(c16D);
    arr[15] = c16;
    
    static const int c17_p[] = {4};
    static const int c17_d[] = {-1};
    
    vector<int> c17P(c17_p, c17_p + sizeof(c17_p) / sizeof(c17_p[0]));
    vector<int> c17D(c17_d, c17_d + sizeof(c17_d) / sizeof(c17_d[0]));
    
    Course c17 = arr[16];
    c17.setPrereqs(c17P);
    c17.setDeps(c17D);
    arr[16] = c17;
    
    static const int c18_p[] = {10};
    static const int c18_d[] = {-1};
    
    vector<int> c18P(c18_p, c18_p + sizeof(c18_p) / sizeof(c18_p[0]));
    vector<int> c18D(c18_d, c18_d + sizeof(c18_d) / sizeof(c18_d[0]));
    
    Course c18 = arr[17];
    c18.setPrereqs(c18P);
    c18.setDeps(c18D);
    arr[17] = c18;
    
    static const int c19_p[] = {10};
    static const int c19_d[] = {-1};
    
    vector<int> c19P(c19_p, c19_p + sizeof(c19_p) / sizeof(c19_p[0]));
    vector<int> c19D(c19_d, c19_d + sizeof(c19_d) / sizeof(c19_d[0]));
    
    Course c19 = arr[18];
    c19.setPrereqs(c19P);
    c19.setDeps(c19D);
    arr[18] = c19;
    
    static const int c20_p[] = {5};
    static const int c20_d[] = {-1};
    
    vector<int> c20P(c20_p, c20_p + sizeof(c20_p) / sizeof(c20_p[0]));
    vector<int> c20D(c20_d, c20_d + sizeof(c20_d) / sizeof(c20_d[0]));
    
    Course c20 = arr[19];
    c20.setPrereqs(c20P);
    c20.setDeps(c20D);
    arr[19] = c20;
    
    return arr;
    
}


Quarter * pickQuartersToExchangeClasses(Quarter * arr, int numQuarters, Course * arr2) {
    Quarter minQuarter, maxQuarter;
    
    float minWork = 10000.0;
    float maxWork = 0.0;
    
    int minQuarterIndex = -1;
    int maxQuarterIndex = -1;
    
    for(int i = 0; i < numQuarters; i++) {
        Quarter t_q = arr[i];
        if(t_q.getTotalHours() < minWork) {
            minWork = t_q.getTotalHours();
            minQuarter = t_q;
            minQuarterIndex = i;
        }
        else if(t_q.getTotalHours() > maxWork) {
            maxWork = t_q.getTotalHours();
            maxQuarter = t_q;
            maxQuarterIndex = i;
        }
    }
    Course c1 = minQuarter.returnLightestCourse();
    Course c2 = maxQuarter.returnHeaviestCourse();
    
    if(isValidSwap(c1, c2, arr2)) {
        //swap
        
        cout << "********* swapping courses ************" << endl;
        
        minQuarter.removeCourse(c1);
        minQuarter.assignClass(c2);
        maxQuarter.removeCourse(c2);
        maxQuarter.assignClass(c1);
        
        c1.assignQuarter(maxQuarter.getQuarterIndex());
        c2.assignQuarter(minQuarter.getQuarterIndex());
        
        arr[minQuarterIndex] = minQuarter;
        arr[maxQuarterIndex] = maxQuarter;
    }
    else {
        //if this does not work, iterate through all combinations starting with the heaviest and lightest courses from
        //the heaviest and lightest quarters
        
        
        
    }
    return arr;
}

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
    
    Course *arr2 = constructVectorsForCourses(arr);
    
    Quarter *qArr2 = assignClassesGreedily(arr2, qArr, 20, 5);
    iterateThroughAllQuarters(qArr2, 5);
    
    calculateAverageNumberOfHours(qArr2, 5);
    
    Quarter *qArr3 = pickQuartersToExchangeClasses(qArr2, 5, arr);
    iterateThroughAllQuarters(qArr3, 5);
    
    calculateAverageNumberOfHours(qArr2, 5);
    
    return 0;
}
