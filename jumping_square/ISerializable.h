#pragma once
#include <string>


class ISerializable
{
public:
	virtual std::string ToString() = 0;

	// Example ->    "class=string;pos=float,float;side=float,float;speed=float,float;p1=int,int;p2=int,int;color=char,char,char;time_step=int;args=string"

};