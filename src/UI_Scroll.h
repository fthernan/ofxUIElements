#pragma once

#include "ofMain.h"
#include "ofxTweenzor.h"

#define MIN_DIFF 0.01f

class Scroll {
public:
	ofRectangle area;
	float maxScroll;
	float value;
	bool horizontal;
	bool enableBool;
	// ---
	float inertia;
	float initPos;
	float currentPos;
	float prevPos;
	bool bPressed;
	// ----
	ofRectangle savedViewport;

	void setup( float _x, float _y, float _width, float _height, float _maxScroll, bool _horizontal = false, float _init_value = 0 ) {
		area = ofRectangle( _x, _y, _width, _height );
		maxScroll = max( _maxScroll - _height, _height );
		value = _init_value;
		horizontal = _horizontal;
		inertia = 0;
		bPressed = false;

		enable();
	}

	void reset() {
		value = 0;
	}

	void begin() {
		float w = ofGetWidth();
		float h = ofGetHeight();
		savedViewport = ofGetCurrentViewport();
		ofViewport( area.x, area.y, area.width, area.height, false );
		ofPushMatrix();
		ofScale( w / area.width, h / area.height );
		ofTranslate( 0, getVal() );
	}

	void end() {
		ofPopMatrix();
		ofViewport( savedViewport );
	}

	void enable() {
		enableBool = true;
		ofAddListener( ofEvents().update, this, &Scroll::update );
		ofAddListener( ofEvents().mousePressed, this, &Scroll::mousePressed );
		ofAddListener( ofEvents().mouseDragged, this, &Scroll::mouseDragged );
		ofAddListener( ofEvents().mouseReleased, this, &Scroll::mouseReleased );
	}

	void disable() {
		enableBool = false;
		ofRemoveListener( ofEvents().update, this, &Scroll::update );
		ofRemoveListener( ofEvents().mousePressed, this, &Scroll::mousePressed );
		ofRemoveListener( ofEvents().mouseDragged, this, &Scroll::mouseDragged );
		ofRemoveListener( ofEvents().mouseReleased, this, &Scroll::mouseReleased );
	}

	void update( ofEventArgs &args ) {
		if ( initPos == -1 ) {
			// inertia
			value += inertia;
			inertia *= 0.85f;

			inertia = ( abs( inertia ) < MIN_DIFF ) ? 0 : inertia;

			if ( value > 0 ) {
				inertia *= 0.8f;
				value *= 0.8f;
			}
			if ( value < -maxScroll ) {
				inertia *= 0.8f;
				value = ( maxScroll + value ) * 0.8f - maxScroll;
			}
		}
	}

	bool getPressed() {
		bool returnValue = bPressed;
		bPressed = false;
		return returnValue;
	}

	float getVal() {
		float rValue = value;
		if ( initPos != -1 ) {
			rValue += currentPos - initPos;
		}
		return rValue;
	}

	void mouseDragged( ofMouseEventArgs& mouse ) {
		prevPos = currentPos;
		currentPos = horizontal ? mouse.x : mouse.y;
	}

	void mousePressed( ofMouseEventArgs& mouse ) {
		if ( area.inside( mouse ) ) {
			initPos = horizontal ? mouse.x : mouse.y;
			currentPos = initPos;
			prevPos = currentPos;
		}
		else {
			initPos = -1;
		}
	}

	void mouseReleased( ofMouseEventArgs& mouse ) {
		if ( initPos == -1 ) return;
		if ( initPos == ( horizontal ? mouse.x : mouse.y ) ) {
			bPressed = true;
		}
		value += currentPos - initPos;
		inertia = currentPos - prevPos;
		initPos = -1;
	}

	void drawArea( ofColor color = ofColor::white, float alpha = 128 ) {
		ofSetColor( color, alpha );
		ofDrawRectangle( area );
	}
};
