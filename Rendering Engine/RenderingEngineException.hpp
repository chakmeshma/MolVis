#pragma once

#include <exception>
#include <string>

class RenderingEngineException : public std::exception {
public:
	RenderingEngineException(const char* reason) : std::exception(reason) { }
};