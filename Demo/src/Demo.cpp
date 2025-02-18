#pragma once

#include <Phvika.h>

class Demo : public phv::Application
{
public:
	Demo()
	{

	}
	~Demo()
	{

	}

};

phv::Application* phv::CreateApplication()
{
	return new Demo();
}