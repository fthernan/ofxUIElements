#pragma once

#include "ofMain.h"


class ToggleButtonImg {
public:
	ofRectangle area;
	ofColor on_color;
	ofColor over_color;
	ofImage img[2];
	int state;
	bool over;
	bool pressed;
	bool showBool;
	bool initPressed;

	void setup( float _x, float _y, float _width, float _height, string img_path_on, string img_path_off, ofColor _on_color = ofColor::white ) {
		setup( _x, _y, _width, _height, img_path_on, img_path_off, _on_color, ofColor( _on_color, 127 ) );
	}

	void setup( float _x, float _y, float _width, float _height, string img_path_on, string img_path_off, ofColor _on_color, ofColor _over_color ) {
		area = ofRectangle( _x, _y, _width, _height );
		img[0].load( img_path_on );
		img[1].load( img_path_off );

		over_color = _over_color;
		on_color = _on_color;

		state = 0;
		over = false;
		pressed = false;

		show();
	}

	void show() {
		showBool = true;
		ofAddListener( ofEvents().mousePressed, this, &ToggleButtonImg::mousePressed );
		ofAddListener( ofEvents().mouseDragged, this, &ToggleButtonImg::mouseDragged );
		ofAddListener( ofEvents().mouseReleased, this, &ToggleButtonImg::mouseReleased );
	}

	void hide() {
		showBool = false;
		ofRemoveListener( ofEvents().mousePressed, this, &ToggleButtonImg::mousePressed );
		ofRemoveListener( ofEvents().mouseDragged, this, &ToggleButtonImg::mouseDragged );
		ofRemoveListener( ofEvents().mouseReleased, this, &ToggleButtonImg::mouseReleased );
	}

	bool getPressed() {
		bool returnval = pressed;
		pressed = false;
		return returnval;
	}

	int getState() {
		return state;
	}

	void mousePressed( ofMouseEventArgs& mouse ) {
		initPressed = false;
		if ( area.inside( mouse ) ) {
			over = true;
			initPressed = true;
		}
	}

	void mouseDragged( ofMouseEventArgs& mouse ) {
		if ( area.inside( mouse ) && initPressed ) {
			over = true;
		}
		else {
			over = false;
		}
	}

	void mouseReleased( ofMouseEventArgs& mouse ) {
		if ( area.inside( mouse ) && initPressed ) {
			pressed = true;
			state = state == 1 ? 0 : 1;
		}
		over = false;
	}

	void draw() {
		if ( !showBool ) return;

		ofSetColor( on_color );
		if ( over ) {
			ofSetColor( over_color );
		}
		img[state].draw( area.x, area.y );
	}
};
