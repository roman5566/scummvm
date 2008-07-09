/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef COMMON_VIRTUAL_KEYBOARD_H
#define COMMON_VIRTUAL_KEYBOARD_H

class OSystem;

#include "common/events.h"
#include "common/hashmap.h"
#include "common/hash-str.h"
#include "common/image-map.h"
#include "common/keyboard.h"
#include "common/str.h"
#include "graphics/surface.h"

namespace Common {

class VirtualKeyboardParser;



class VirtualKeyboard {

	/** Type of key event */
	enum EventType {
		kEventKey,
		kEventSwitchMode,
		kEventClose
	};

	struct Event {
		Common::String name;
		EventType type;
		void *data;
	};
	
	typedef Common::HashMap<Common::String, Event, Common::IgnoreCase_Hash, Common::IgnoreCase_EqualTo> EventMap; 

	struct Mode {
		Common::String     name;
		Common::String     resolution;
		Common::String     bitmapName;
		Graphics::Surface *image;
		Common::ImageMap   imageMap;
		EventMap           events;
		Mode() : image(0) {}
	};
	
	typedef Common::HashMap<Common::String, Mode, Common::IgnoreCase_Hash, Common::IgnoreCase_EqualTo> ModeMap;

	enum HorizontalAlignment {
		kAlignLeft,
		kAlignCentre,
		kAlignRight
	};

	enum VerticalAlignment {
		kAlignTop,
		kAlignMiddle,
		kAlignBottom
	};

public:
	VirtualKeyboard();
	virtual ~VirtualKeyboard();

	bool loadKeyboardPack(Common::String packName);
	void show();
	void hide();
	bool isDisplaying() { 
		return _displaying;
	}
	bool isLoaded() {
		return _loaded;
	}

	/**
	  * Get the next virtual key event in the event queue.
	  * @param event	point to an Event struct, which will be filled with the event data.
	  * @return true if an event was retrieved.
	  */
	bool pollEvent(Common::Event &event);

protected:
	OSystem	*_system;

	static const int SNAP_WIDTH = 10;
	
	friend class VirtualKeyboardParser;
	VirtualKeyboardParser *_parser;

	// TODO : sort order of all this stuff
	void reset();
	bool checkModeResolutions();
	void setDefaultPosition();
	void move(int16 x, int16 y);
	void switchMode(Mode *newMode);
	void switchMode(const Common::String& newMode);
	Common::String findArea(int16 x, int16 y);
	void processClick(const Common::String &area);
	void runLoop();
	void redraw();

	bool _loaded;
	bool _displaying;
	bool _needRedraw;
	bool _firstRun;

	ModeMap _modes;
	Mode *_initialMode;
	Mode *_currentMode;

	int16 _screenWidth, _screenHeight;
	Common::Rect _kbdBound;

	HorizontalAlignment  _hAlignment;
	VerticalAlignment    _vAlignment;

	Common::String _areaDown;
	Common::Point _dragPoint;
	bool _drag;

	Common::Array<Common::KeyState> _keyQueue;
	Common::KeyState *_keyDown;

};


} // End of namespace GUI


#endif
