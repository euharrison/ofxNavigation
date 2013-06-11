#pragma once

#include "ofxNavigation.h"


//--------------------------------------------------------------
// setup

ofxNavigation::ofxNavigation() {
	previousIndex = -1;
	currentIndex = -1;
	nextIndex = -1;
	locked = false;
}

void ofxNavigation::add(void * item) {
	items.push_back(item);
}

void ofxNavigation::remove(void * item) {
	remove(getIndex(item));
}

void ofxNavigation::remove(int index) {
    if (currentIndex == index) {
        deactivate();
    }
	items.erase(items.begin()+(index-1));
}


//--------------------------------------------------------------
// activations

void ofxNavigation::activate(int index) {
	changeTo(index);
}

void ofxNavigation::activate(void * item) {
	changeTo(getIndex(item));
}

void ofxNavigation::activateNextOnList(bool loop) {
	if (currentIndex > -1 && currentIndex+1 < items.size()) {
		changeTo(currentIndex+1);
	} else if (loop) {
		changeTo(0);
	}
}

void ofxNavigation::activatePreviousOnList(bool loop) {
	if (currentIndex > 0 && currentIndex-1 < items.size()) {
		changeTo(currentIndex-1);
	} else if (loop) {
		changeTo(items.size()-1);
	}
}

void ofxNavigation::deactivate() {
	changeTo(-1);
}


//--------------------------------------------------------------
// getters

void * ofxNavigation::getPrevious() {
	return getItem(previousIndex);
}

void * ofxNavigation::getCurrent() {
	return getItem(currentIndex);
}

void * ofxNavigation::getNext() {
	return getItem(nextIndex);
}

void * ofxNavigation::getItem(int index) {
	return (index > -1 && index < items.size()) ? items[index] : NULL;
}

int ofxNavigation::getIndex(void * item) {
	for (int i = 0; i < items.size(); i++) {
		if (items[i] == item) return i;
	}
	return -1;
}


//--------------------------------------------------------------
// locker

void ofxNavigation::lock() {
    locked = true;
}

void ofxNavigation::unlock() {
	locked = false;
    if (!waitingDeactivate && nextIndex > -1) {
        updateVars();
		ofNotifyEvent(activateEvent, *this);
    }
}

bool ofxNavigation::isLocked() {
    return locked;
}


//--------------------------------------------------------------
// core

void ofxNavigation::changeTo(int newIndex) {
    if (locked) return;
    
    //only deactivate
    if (newIndex == -1 && currentIndex > -1) {
		ofNotifyEvent(deactivateEvent, *this);
        updateVars();
    }
    else if (newIndex != currentIndex) {
        
        //only activate
        if (currentIndex == -1) {
            nextIndex = newIndex;
            updateVars();
			ofNotifyEvent(activateEvent, *this);
        }
        
        //deactivate and activate
        else {
            nextIndex = newIndex;
			waitingDeactivate = true;
			ofNotifyEvent(deactivateEvent, *this);
			waitingDeactivate = false;

            //if the someone call lock() when deactivate
			//it means that nav need to wait
			//so wait someone call unlock() to procced
            if (!locked && nextIndex > -1) {
                updateVars();
				ofNotifyEvent(activateEvent, *this);
            }
        }
    }
}

void ofxNavigation::updateVars() {
	previousIndex = currentIndex;
    currentIndex = nextIndex;
    nextIndex = -1;
}
