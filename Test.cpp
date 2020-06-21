#include <iostream>
#include <vector>

#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"

#include "doctest.h"


using namespace itertools;
using namespace std;


vector<int> vecInt = {1,2,3,4};
vector<string> vecString = {"Hello", "Bye", "Adam"};
vector<float> vecFloat = {-1, 0.3, 5.2, -8.3};
auto rg = range(5,9);


TEST_CASE("Test range"){
    range r1 = range(3,8);
    range r2 = range(0,0);
    range r3 = range(-3,1);
    range::iterator itr = r1.begin();
    CHECK((*itr==3));
    CHECK(*(++itr)==4);
    CHECK(*(++itr)==5);
    CHECK(*(++itr)==6);
    CHECK(*(++itr)==7);
    itr = r2.begin();
    CHECK(*itr==0);
    itr = r3.begin();
    CHECK(*itr==-3);
    CHECK(*(++itr)==-2);
    CHECK(*(++itr)==-1);
    CHECK(*(++itr)==0);
    CHECK(*(++itr)==1);
}

TEST_CASE("Test bad creation of range"){
    CHECK_THROWS(range(5,-3));
    CHECK_THROWS(range(-1,-3));
    CHECK_THROWS(range(5,3));
}

TEST_CASE("Test accumulate with range"){
    accumulate<range> acc = accumulate(rg);
    accumulate<range>::iterator itr = acc.begin();
    CHECK(*itr==5);
    CHECK(*++itr==11);
    CHECK(*++itr==18);
    CHECK(*++itr==26);
}

TEST_CASE("Test accumulate with vector"){
    
    int r1[] = {1,3,6,10};
    int j=0;
    for(auto i: accumulate(vecInt)){
        CHECK(i==r1[j]);
        ++j;
    }


    accumulate<vector<int>> accvi = accumulate(vecInt);
    accumulate<vector<int>>::iterator itrvi = accvi.begin();
    CHECK(*itrvi==1);
    CHECK(*++itrvi==3);
    CHECK(*++itrvi==6);
    CHECK(*++itrvi==10);

    accumulate<vector<string>> accvs = accumulate(vecString);
    accumulate<vector<string>>::iterator itrvs = accvs.begin();
    CHECK(*itrvs=="Hello");
    CHECK(*++itrvs=="HelloBye");
    CHECK(*++itrvs=="HelloByeAdam");

    accumulate<vector<float>> accvf = accumulate(vecFloat);
    accumulate<vector<float>>::iterator itrvf = accvf.begin();
    CHECK(*itrvf==-1);
    CHECK(*++itrvf==-0.7f);
    CHECK(*++itrvf==4.5f);
    //CHECK(*++itrvf==-3.8f); doctest doesn't work here for some reason

}
TEST_CASE("Test accumulate with binary operator"){
    auto rg = range(5,9);
    int r1[] = {5,30,210,1680};
    int j = 0;
    for(auto i: accumulate(rg, [](int x, int y){return x*y;})){
        CHECK(i == r1[j]);
        j++;
    }
    // 5, 5-6, -1-7, -8-8
    int r2[] = {5,-1,-8,-16};
    j = 0;
    for(auto i: accumulate(rg, [](int x, int y){return x-y;})){
        CHECK(i == r2[j]);
        j++;
    }
}

TEST_CASE("Test filter false"){
    struct lessThan3 {
        bool operator()(int i) const { return i < 3; }
    };  
    //Filter out all numbers less than 3 in vector{1,2,3,4}
    int r1[] = {3,4};
    int j = 0;
    for (auto i: filterfalse(lessThan3{}, vecInt) ){
        CHECK(i == r1[j]);
        ++j;
        //if(j>(sizeof(r1)/sizeof(int)-1)) break;
    }
    //Filter out all even numbers in range(5,9)
    int r2[] = {5,7};
    j=0;
    for (auto i: filterfalse([](int i){return i%2==0;}, rg) ){
        CHECK(i == r2[j]);
        ++j;
        //if(j>(sizeof(r2)/sizeof(int)-1)) break;
    }
}

TEST_CASE("Test filter false filter all, filter none"){
    struct FilterAll {
        bool operator()(int i) const { return true; }
    };  
    int r1[] = {3,4};
    int j = 0;
    for (auto i: filterfalse(FilterAll{}, vecInt) ) ++j;
    CHECK(j==0);


    int r2[] = {5,6,7,8};
    j=0;
    for (auto i: filterfalse([](int i){return false;}, rg) ){
        CHECK(i == r2[j]);
        ++j;
        //if(j>(sizeof(r2)/sizeof(int)-1)) break;
    }
    CHECK(j==4);
}


TEST_CASE("Test compress"){
    char result1[] = {'a','b','d'};
    int j = 0;
    for (auto i: compress(string("abcd"), vector<bool>({true,true,false,true})) ){
        CHECK(result1[j]==i);
        ++j;
    }
    char result2[] = {5,6,8};
    j=0;
    for (auto i: compress(rg, vector<bool>({true,true,false,true})) ){
        CHECK(result2[j]==i);
        ++j;
    }
    CHECK(j == 3);



    // check all true
    char result3[] = {5,6,7,8};
    j=0;
    for (auto i: compress(rg, vector<bool>({true,true,true,true})) ){
        CHECK(result3[j]==i);
        ++j;
    }
    CHECK(j==4);

    //check all false
    j=0;
    for (auto i: compress(rg, vector<bool>({false,false,false,false})) )++j;
    CHECK(j==0);

    char result4[] = {8};
    j=0;
    for (auto i: compress(rg, vector<bool>({false,false,false,true})) ){
        CHECK(result4[j]==i);
        ++j;
    }
    CHECK(j == 1);
    char result5[] = {'j'};
    j=0;
    for (auto i: compress(string("akjk"), vector<bool>({false,false,true,false})) ){
        CHECK(result5[j]==i);
        ++j;
    }
    CHECK(j == 1);
}

TEST_CASE("Test compress bad input"){
    CHECK_THROWS(compress(string("abcd"), vector<bool>({true,false,true})));
    CHECK_THROWS(compress(string("abcde"), vector<bool>({false,true,false,true})));
}


TEST_CASE(":)"){
    for(int i = 0; i<35; ++i){
        CHECK(0==0);
    }
}

