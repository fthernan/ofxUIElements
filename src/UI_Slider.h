#pragma once

#include "ofMain.h"

class Slider {
public:
	float x;
	float y;
	float width;
	float height;
	float value;
	bool enableBool;
	bool horizontal;
	// ---
	float initPos;
	ofVec2f initVec2f;
	float currentPos;
	float autoIncrementValue;
	bool autoIncrement;

	void setup( float _x, float _y, float _width, float _height, bool _horizontal = true, float _init_value = 0 ) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		value = mapToValue( _init_value );
		horizontal = _horizontal;
		autoIncrement = false;
		enable();
	}

	void enable() {
		enableBool = true;
		ofAddListener( ofEvents().mousePressed, this, &Slider::mousePressed );
		ofAddListener( ofEvents().mouseDragged, this, &Slider::mouseDragged );
		ofAddListener( ofEvents().mouseReleased, this, &Slider::mouseReleased );
	}

	void disable() {
		enableBool = false;
		ofRemoveListener( ofEvents().mousePressed, this, &Slider::mousePressed );
		ofAddListener( ofEvents().mouseDragged, this, &Slider::mouseDragged );
		ofRemoveListener( ofEvents().mouseReleased, this, &Slider::mouseReleased );
	}

	void setValue( float val ) {
		value = mapToValue( val );
	}

	void setAutoIncrement( float val ) {
		autoIncrement = true;
		autoIncrementValue = val;
	}

	void toggleAutoincrement() {
		autoIncrement = !autoIncrement;
	}

	float clampValue( float val ) {
		return ofClamp( val, horizontal ? x : y, horizontal ? x + width : y + height );
	}

	float mapToValue( float val ) {
		return ofMap( val, 0, 1, horizontal ? x : y, horizontal ? x + width : y + height );
	}

	float mapFromValue( float val ) {
		return ofMap( val, ( horizontal ? x : y ), ( horizontal ? x + width : y + height ), 0, 1, true );
	}

	float getVal() {
		float rValue = value;
		if ( initPos != -1 ) {
			rValue += currentPos - initPos;
		}

		if ( autoIncrement ) {
			value += autoIncrementValue;
		}

		rValue = clampValue( rValue );
		rValue = mapFromValue( rValue );
		return rValue;
	}

	void mouseDragged( ofMouseEventArgs& mouse ) {
		currentPos = horizontal ? mouse.x : mouse.y;
	}

	void mousePressed( ofMouseEventArgs& mouse ) {
		if ( mouse.x > x && mouse.x < x + width && mouse.y > y && mouse.y < y + height ) {
			initPos = horizontal ? mouse.x : mouse.y;
			//value = initPos;
			currentPos = initPos;
			initVec2f = mouse;
		}
		else {
			initPos = -1;
		}
	}

	void mouseReleased( ofMouseEventArgs& mouse ) {
		if ( initPos == -1 ) return;
		if ( initVec2f == mouse ) {
			// click
			value = horizontal ? mouse.x : mouse.y;
			value = clampValue( value );
		}
		else {
			value += currentPos - initPos;
			value = clampValue( value );
		}
		initPos = -1;
	}

	void drawArea( ofColor _color = ofColor::white ) {
		ofSetColor( _color, 160 );
		ofDrawRectangle( x, y, width, height );
	}
};
