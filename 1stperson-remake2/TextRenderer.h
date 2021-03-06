#ifndef TextRendererH
#define TextRendererH
#include <OgrePrerequisites.h>
#include <OgreColourValue.h>

namespace Ogre
{
	class OverlayManager;
	class Overlay;
	class OverlayContainer;
	class OverlaySystem;
}

class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer();

	void addTextBox(
		const std::string& ID,
		const std::string& text,
		Ogre::Real x, Ogre::Real y,
		Ogre::Real width, Ogre::Real height,
		const Ogre::ColourValue& color = Ogre::ColourValue(1.0, 1.0, 1.0, 1.0));

	void setPosition(const std::string& ID,float x,float y);
	void removeTextBox(const std::string& ID);
	void setText(const std::string& ID, const std::string& Text);
	void reset();

private:
	std::vector<std::string> txts;
	Ogre::OverlayManager*    _overlayMgr;
	Ogre::Overlay*           _overlay;
	Ogre::OverlayContainer*  _panel;
	Ogre::OverlaySystem * mOverlaySystem;
};

#endif