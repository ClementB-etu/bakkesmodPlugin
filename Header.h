#pragma once
#pragma comment( lib, "bakkesmod.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include <iostream>  
#include<sstream> 


class TESTPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
protected: 
	std::shared_ptr<bool> touchMeasure;
public:
	virtual void onLoad();
	virtual void onUnload();
	virtual void BallHit();
	double old_speed_sq = -1.0;
	double cpt = 0;
};