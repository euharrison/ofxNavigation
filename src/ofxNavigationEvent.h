#pragma once

#include "ofxNavigation.h"


class ofxNavigation;

class ofxNavigationEvent : public ofEventArgs {
public:
    ofxNavigation * nav;
	void * item;
};