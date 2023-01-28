#pragma once
#ifndef APARAM_H
#define APARAM_H

#include <string>
#include <vector>

class Param
{

private:
	unsigned int sec = 0;
	std::vector<std::wstring> processes;
	int error_no = 0;
    // std::wstring path = ""

public:
	Param();
	~Param();
	Param(unsigned int, std::vector<std::wstring>& processes);
	unsigned int Second();
	std::vector<std::wstring>& Processes();
	bool SaveToDisk();
	int ErrorNo();
};


#endif
