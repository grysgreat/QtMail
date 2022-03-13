#include "Exception.h"
Exception::Exception(std::string s) {
		msg = s;
	}

void Exception::Print() {
		std::cout << "Exception: " << msg << std::endl;
	}

