#pragma once

#include "ofMain.h"

class ButtonText {
public:
	ofRectangle area;
	ofColor color;
	ofColor color2;
	int state;
	bool pressed;
	bool showBool;
	bool initPressed;
	ofTrueTypeFont	font;
	string text;

	void setup( float _x, float _y, string _text, int _fontSize, ofColor _color, ofColor _color2 ) {
		color = _color;
		color2 = _color2;
		text = _text;

		state = 0;
		pressed = false;

		font.load( "fonts/FlyingPanels.ttf", _fontSize );

		float height = font.getLineHeight();
		float width = font.stringWidth( text );

		area = ofRectangle( _x, _y - height, width, height );

		show();
	}

	void show() {
		showBool = true;
		ofAddListener( ofEvents().mousePressed, this, &ButtonText::mousePressed );
		ofAddListener( ofEvents().mouseDragged, this, &ButtonText::mouseDragged );
		ofAddListener( ofEvents().mouseReleased, this, &ButtonText::mouseReleased );
	}

	void hide() {
		showBool = false;
		ofRemoveListener( ofEvents().mousePressed, this, &ButtonText::mousePressed );
		ofRemoveListener( ofEvents().mouseDragged, this, &ButtonText::mouseDragged );
		ofRemoveListener( ofEvents().mouseReleased, this, &ButtonText::mouseReleased );
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

	void drawArea() {
		if ( !showBool ) return;

		ofSetColor( color );
		if ( state == 1 ) {
			//ofSetColor( color, 120 );
			ofSetColor( color2 );
		}
		ofDrawRectangle( area );
	}

	void draw() {
		if ( !showBool ) return;

		ofSetColor( color );
		if ( state == 1 ) {
			//ofSetColor( color, 120 );
			ofSetColor( color2 );
		}
		font.drawString( text, area.x, area.y + area.height );
	}
};
