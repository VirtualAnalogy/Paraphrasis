/*
  ==============================================================================

    ImageCache.h
    Created: 28 Sep 2013 3:47:45pm
    Author:  nik

  ==============================================================================
*/

#ifndef IMAGECACHE_H_INCLUDED
#define IMAGECACHE_H_INCLUDED

#include "JuceHeader.h"

namespace teragon {

class ResourceCache {
public:
    class ImageStates {
    public:
        ImageStates(Image normal = Image::null, Image alternate = Image::null,
                    Image background = Image::null) :
            normal(normal), alternate(alternate), background(background) {}
        virtual ~ImageStates() {}

    public:
        Image normal;
        Image alternate;
        Image background;
    };
public:
    ResourceCache() {}
    virtual ~ResourceCache();

    virtual void add(String name, const char* normalImage, const int normalImageSize,
                     const char* alternateImage = nullptr, const int alternateImageSize = 0,
                     const char* backgroundImage = nullptr, const int backgroundImageSize = 0);

    virtual ImageStates get(const String &name) const;
    virtual ImageStates operator[](const String &name) const { return get(name); }

private:
    typedef juce::HashMap<String, ImageStates> ResourceMap;
    ResourceMap resources;
};

}

#endif  // IMAGECACHE_H_INCLUDED
