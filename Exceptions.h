#define EXCEPTIONS_H

#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#include <exception>


struct NoSuchElementException : public std::exception {
	const char* what() const throw() {
		return "The given semantic name was not found in the input layout!";
	}
};
