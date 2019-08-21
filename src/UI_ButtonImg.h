#pragma once

#include "ofMain.h"


class ButtonImg {
public:
	ofRectangle area;
	ofColor on_color;
	ofColor over_color;
	ofImage img;
	int state;
	bool pressed;
	bool showBool;
	bool initPressed;

	void setup( float _x, float _y, float _width, float _height, string img_path, ofColor _on_color = ofColor::white ) {
		setup( _x, _y, _width, _height, img_path, _on_color, ofColor( _on_color, 127 ) );
	}

	void setup( float _x, float _y, float _width, float _height, string img_path, ofColor _on_color, ofColor _over_color ) {
		area = ofRectangle( _x, _y, _width, _height );
		img.load( img_path );

		over_color = _over_color;
		on_color = _on_color;

		state = 0;
		pressed = false;

		show();
	}

	void show() {
		showBool = true;
		ofAddListener( ofEvents().mousePressed, this, &ButtonImg::mousePressed );
		ofAddListener( ofEvents().mouseDragged, this, &ButtonImg::mouseDragged );
		ofAddListener( ofEvents().mouseReleased, this, &ButtonImg::mouseReleased );
	}

	void hide() {
		showBool = false;
		ofRemoveListener( ofEvents().mousePressed, this, &ButtonImg::mousePressed );
		ofRemoveListener( ofEvents().mouseDragged, this, &ButtonImg::mouseDragged );
		ofRemoveListener( ofEvents().mouseReleased, this, &ButtonImg::mouseReleased );
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

		ofSetColor( on_color );
		if ( state == 1 ) {
			ofSetColor( over_color );
		}
		img.draw( area.x, area.y );
	}
};
