#ifndef TESTS_HPP
#define TESTS_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <sstream>
#include <tuple>
#include <chrono>
#include <time.h>
#include <sys/time.h>
#include <thread>

#include "hashMap.hpp"

using namespace std;

auto logic = [](bool in)
{
    if (in)
        return "True";
    return "False";
};
const string SEPERATOR(42, '#');

static void testInsertInt()
{
    HashMap<int, int> imap;
    int value = -1;

    imap.insert(10, 20);
    cout << "(10, 20) inserted" << endl;
    bool ret = imap.find(10, value);
    cout << "10 found: " << logic(ret) << ", value is: " << value << endl;
    value = -1;

    ret = imap.find(20, value);
    cout << "20 found: " << logic(ret) << ", value is: " << value << endl;
    value = -1;

    imap.insert(100, 200);
    cout << "(100, 200) inserted" << endl;
    imap.insert(1000, 2000);
    cout << "(1000, 2000) inserted" << endl;

    ret = imap.find(100, value);
    cout << "100 found: " << logic(ret) << ", value is: " << value << endl;
    value = -1;
    ret = imap.find(1000, value);
    cout << "1000 found: " << logic(ret) << ", value is: " << value << endl;
    value = -1;

    imap.erase(100);
    cout << "100 erased" << endl;
    ret = imap.find(100, value);
    cout << "100 found: " << logic(ret) << ", value is: " << value << endl;
    value = -1;
    ret = imap.find(1000, value);
    cout << "1000 found: " << logic(ret) << ", value is: " << value << endl;
}

static void testInsertString()
{
    HashMap<string, int> imap;
    int value = -1;

    imap.insert("hello", 200);
    cout << "(hello, 200) inserted" << endl;
    bool ret = imap.find("Hello", value);
    cout << "Hello found: " << logic(ret) << ", value is: " << value << endl;
    value = -1;

    ret = imap.find("hello", value);
    cout << "hello found: " << logic(ret) << ", value is: " << value << endl;
    value = -1;

    imap.insert("world", 2000);
    cout << "(world, 2000) inserted" << endl;
    imap.insert("Hello", 4000);
    cout << "(Hello, 4000) inserted" << endl;

    ret = imap.find("world", value);
    cout << "world found: " << logic(ret) << ", value is: " << value << endl;
    value = -1;
    ret = imap.find("fall", value);
    cout << "fall found: " << logic(ret) << ", value is: " << value << endl;
    value = -1;

    imap.erase("hello");
    cout << "hello erased" << endl;
    ret = imap.find("hello", value);
    cout << "hello found: " << logic(ret) << ", value is: " << value << endl;
    value = -1;
    ret = imap.find("Hello", value);
    cout << "Hello found: " << logic(ret) << ", value is: " << value << endl;
}

static void threadFunction1_StringKey(HashMap<string, int> &hashMap)
{
    stringstream ss;
    ss << "in thread 1"
       << "\n\n";
    cout << ss.str();

    hashMap.insert("ten", 1100);
    ss.str("");
    ss << "thread 1 - (ten, 1100) inserted" << endl;
    cout << ss.str();

    hashMap.insert("twenty", 1200);
    ss.str("");
    ss << "thread 1 - (twenty, 1200) inserted" << endl;
    cout << ss.str();

    hashMap.insert("fifteen", 1500);
    ss.str("");
    ss << "thread 1 - (fifteen, 1500) inserted" << endl;
    cout << ss.str();

    this_thread::sleep_for(chrono::seconds(1));

    int value = -1;
    bool ret = hashMap.find("twenty", value);
    ss.str("");
    ss << "thread 1 - twenty found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    value = -1;
    ret = hashMap.find("twentyFive", value);
    ss.str("");
    ss << "thread 1 - twentyFive found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    hashMap.insert("twenty", 12000);
    ss.str("");
    ss << "thread 1 - (twenty, 12000) inserted" << endl;
    cout << ss.str();

    hashMap.insert("twentyFiveHundred", 177777);
    ss.str("");
    ss << "thread 1 - (twentyFiveHundred, 177777) inserted" << endl;
    cout << ss.str();

    value = -1;
    ret = hashMap.find("twenty", value);
    ss.str("");
    ss << "thread 1 - twenty found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    hashMap.erase("twenty");
    ss.str("");
    ss << "thread 1 - twenty erased" << endl;
    cout << ss.str();

    this_thread::sleep_for(chrono::seconds(1));

    value = -1;
    ret = hashMap.find("twenty", value);
    ss.str("");
    ss << "thread 1 - twenty found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    hashMap.insert("twenty", 13000);
    ss.str("");
    ss << "thread 1 - (twenty, 13000) inserted" << endl;
    cout << ss.str();

    value = -1;
    ret = hashMap.find("twenty", value);
    ss.str("");
    ss << "thread 1 - twenty found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    hashMap.clear();
    ss.str("");
    ss << "thread 1 - hashMap cleared ..." << endl;
    cout << ss.str();

    value = -1;
    ret = hashMap.find("twenty", value);
    ss.str("");
    ss << "thread 1 - twenty found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    ss.str("");
    ss << "\nthread 1 exit ...\n\n";
    cout << ss.str();
}

static void threadFunction2_StringKey(HashMap<string, int> &hashMap)
{
    stringstream ss;
    ss << "in thread 2"
       << "\n\n";
    cout << ss.str();

    hashMap.insert("ten", 2100);
    ss.str("");
    ss << "thread 2 - (ten, 2100) inserted" << endl;
    cout << ss.str();

    hashMap.insert("twenty", 2200);
    ss.str("");
    ss << "thread 2 - (twenty, 2200) inserted" << endl;
    cout << ss.str();

    hashMap.insert("twentyFive", 22500);
    ss.str("");
    ss << "thread 2 - (twentyFive, 22500) inserted" << endl;
    cout << ss.str();

    this_thread::sleep_for(chrono::seconds(1));

    hashMap.insert("twentyFiveHundred", 23456);
    ss.str("");
    ss << "thread 2 - (twentyFiveHundred, 23456) inserted" << endl;
    cout << ss.str();

    hashMap.insert("sixteen", 216);
    ss.str("");
    ss << "thread 2 - (sixteen, 216) inserted" << endl;
    cout << ss.str();

    int value = -1;
    bool ret = hashMap.find("twenty", value);
    ss.str("");
    ss << "thread 2 - twenty found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    value = -1;
    ret = hashMap.find("twentyFive", value);
    ss.str("");
    ss << "thread 2 - twentyFive found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    hashMap.insert("twenty", 2999);
    ss.str("");
    ss << "thread 2 - (twenty, 2999) inserted" << endl;
    cout << ss.str();

    this_thread::sleep_for(chrono::seconds(1));

    value = -1;
    ret = hashMap.find("twenty", value);
    ss.str("");
    ss << "thread 2 - twenty found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    hashMap.erase("twenty");
    ss.str("");
    ss << "thread 2 - twenty erased" << endl;
    cout << ss.str();

    this_thread::sleep_for(chrono::seconds(1));

    value = -1;
    ret = hashMap.find("twenty", value);
    ss.str("");
    ss << "thread 2 - twenty found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    hashMap.insert("twenty", 28000);
    ss.str("");
    ss << "thread 2 - (twenty, 28000) inserted" << endl;
    cout << ss.str();

    this_thread::sleep_for(chrono::seconds(1));

    value = -1;
    ret = hashMap.find("twentyFiveHundred", value);
    ss.str("");
    ss << "thread 2 - twentyFiveHundred found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    value = -1;
    ret = hashMap.find("twenty", value);
    ss.str("");
    ss << "thread 2 - twenty found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    hashMap.clear();
    ss.str("");
    ss << "thread 2 - hashMap cleared ..." << endl;
    cout << ss.str();

    value = -1;
    ret = hashMap.find("twenty", value);
    ss.str("");
    ss << "thread 2 - twenty found: " << logic(ret) << ", value is: " << value << endl;
    cout << ss.str();

    ss.str("");
    ss << "\nthread 2 exit ...\n\n";
    cout << ss.str();
}

#endif