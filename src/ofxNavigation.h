#pragma once

#include "ofMain.h"
//#include "ofxNavigationEvent.h"

class ofxNavigation {
public:

    //setup
    ofxNavigation();
    void add(void * item);
    void remove(void * item);
    void remove(int index);

    //activations
    void activate(int index);
    void activate(void * item);
    void activateNextOnList(bool loop = false);
    void activatePreviousOnList(bool loop = false);
    void deactivate();

    //getters
    void * getPrevious();
    void * getCurrent();
    void * getNext();
	void * getItem(int index);
    int getIndex(void * item);

    //locker
    void lock();
    void unlock();
    bool isLocked();
    
    //vars
    vector<void*> items;
    int previousIndex;
    int currentIndex;
    int nextIndex;

    //events
    ofEvent<ofxNavigation> activateEvent;
    ofEvent<ofxNavigation> deactivateEvent;
    

private:
    
    //core
    void changeTo(int index);
    void updateVars();

	//extra
    bool locked;
	bool waitingDeactivate;
    
};
