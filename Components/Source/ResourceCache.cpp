/*
  ==============================================================================

    ImageCache.cpp
    Created: 28 Sep 2013 3:47:45pm
    Author:  nik

  ==============================================================================
*/

#include "ResourceCache.h"
#include "PluginParameter.h"

namespace teragon {

void ResourceCache::add(String name, const char* normalImage, const int normalImageSize,
                        const char* alternateImage, const int alternateImageSize,
                        const char* backgroundImage, const int backgroundImageSize) {
    Image normalImageCached = ImageCache::getFromMemory(normalImage, normalImageSize);
    Image alternateImageCached = Image::null;
    if(alternateImage != nullptr && alternateImageSize > 0) {
        alternateImageCached = ImageCache::getFromMemory(alternateImage, alternateImageSize);
    }
    Image backgroundImageCached = Image::null;
    if(backgroundImage != nullptr && backgroundImageSize != 0) {
        backgroundImageCached = ImageCache::getFromMemory(backgroundImage, backgroundImageSize);
    }
    ImageStates *imageStates = new ImageStates(normalImageCached,
                                               alternateImageCached,
                                               backgroundImageCached);
    String keyName = PluginParameter::makeSafeName(name.toStdString());
    resources.set(keyName, imageStates);
}

ResourceCache::~ResourceCache() {
    ResourceMap::Iterator i(resources);
    while(i.next()) {
        delete i.getValue();
    }
    resources.clear();
    juce::ImageCache::releaseUnusedImages();
}

ResourceCache::ImageStates* ResourceCache::get(const String& name) const {
    String safeName = PluginParameter::makeSafeName(name.toStdString());
    return resources.contains(safeName) ? resources[safeName] : nullptr;
}

} // namespace teragon
