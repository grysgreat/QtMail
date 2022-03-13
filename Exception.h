#ifndef _EXCEPTION_

#define _EXCEPTION_

#include<string>
#include<iostream>

class Exception {

public:
    std::string msg;
	Exception(std::string s) ;
	void Print() ;
};
#endif