/* 
 * File:   main.cpp
 * Author: panchal
 *
 * Created on January 24, 2012, 3:44 PM
 */

#include <cstdlib>
#include <iostream>

#include <list>
#include <vector>
#include <string>

using namespace std;

/*
 * 
 */

std::string str1[] = {"ronaldo", "benzema", "pepe", "kaka", "ozil"};
std::string str2[] = {"messi", "villa", "iniesta", "marcelo", "khadira"};
int str1len = sizeof(str1)/sizeof(str1[0]);
int str2len = sizeof(str1)/sizeof(str1[0]);

template <typename T>
void merge(std::list<T> &list1, std::list<T> &list2, std::vector<T> &vec) {
    while (!list1.empty() && !list2.empty()) {
        if (list1.front() < list2.front()) {
            vec.push_back(list1.front());
            list1.pop_front();
        } else {
            vec.push_back(list2.front());
            list2.pop_front();
        }
    }

    while (!list1.empty()) {
        vec.push_back(list1.front());
        list1.pop_front();
    }

    while (!list2.empty()) {
        vec.push_back(list2.front());
        list2.pop_front();
    }
    
    int count = vec.size();
    while (count > 0) {
        std::cout << vec.front() << "\n" << std::endl;
        count--;
    }

}

int main(int argc, char** argv) {

    std::list<std::string> l1(str1, str1+str1len);
    std::list<std::string> l2(str2, str2+str2len);
    std::vector<std::string> v;
    merge(l1, l2, v);
    return 0;

}