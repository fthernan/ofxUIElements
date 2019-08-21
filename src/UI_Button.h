#pragma once

#include "ofMain.h"

class Button {
public:
	ofRectangle area;
	ofColor color;
	int state;
	bool pressed;
	bool showBool;
	bool initPressed;

	void setup( float _x, float _y, float _width, float _height, ofColor _color ) {
		area = ofRectangle( _x, _y, _width, _height );
		color = _color;

		state = 0;
		pressed = false;

		show();
	}

	void show() {
		showBool = true;
		ofAddListener( ofEvents().mousePressed, this, &Button::mousePressed );
		ofAddListener( ofEvents().mouseDragged, this, &Button::mouseDragged );
		ofAddListener( ofEvents().mouseReleased, this, &Button::mouseReleased );
	}

	void hide() {
		showBool = false;
		ofRemoveListener( ofEvents().mousePressed, this, &Button::mousePressed );
		ofRemoveListener( ofEvents().mouseDragged, this, &Button::mouseDragged );
		ofRemoveListener( ofEvents().mouseReleased, this, &Button::mouseReleased );
	}

	bool getPressed() {
		bool returnval = pressed;
		pressed = false;
		return returnval;
	}

	void mousePressed( ofMouseEventArgs& mouse ) {
		initPressed = false;
		if ( area.inside( mouse ) ) {
			state = 1;
			initPressed = true;
		}
	}

	void mouseDragged( ofMouseEventArgs& mouse ) {
		if ( area.inside( mouse ) && initPressed ) {
			state = 1;
		}
		else {
			state = 0;
		}
	}

	void mouseReleased( ofMouseEventArgs& mouse ) {
		if ( area.inside( mouse ) && initPressed ) {
			pressed = true;
		}
		state = 0;
	}

	void draw() {
		if ( !showBool ) return;

		ofSetColor( color );
		if ( state == 1 ) {
			ofSetColor( color, 120 );
		}
		ofDrawRectangle( area );
	}
};
