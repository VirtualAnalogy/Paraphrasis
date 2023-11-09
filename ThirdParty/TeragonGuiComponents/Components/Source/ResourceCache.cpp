/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
 */

#include "ResourceCache.h"
#include "PluginParameterComponent.h"

namespace teragon {

void ResourceCache::add(String name, const char* normalImage, const int normalImageSize,
                        const char* alternateImage, const int alternateImageSize,
                        const char* backgroundImage, const int backgroundImageSize) {
    Image normalImageCached = ImageCache::getFromMemory(normalImage, normalImageSize);

    Image alternateImageCached = Image();
    if(alternateImage != nullptr && alternateImageSize > 0) {
        alternateImageCached = ImageCache::getFromMemory(alternateImage, alternateImageSize);
    }

    Image backgroundImageCached = Image();
    if(backgroundImage != nullptr && backgroundImageSize != 0) {
        backgroundImageCached = ImageCache::getFromMemory(backgroundImage, backgroundImageSize);
    }

    ImageStates *imageStates = new ImageStates(normalImageCached,
                                               alternateImageCached,
                                               backgroundImageCached);
    String keyName = Parameter::makeSafeName(name.toStdString());
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
    String safeName = Parameter::makeSafeName(name.toStdString());
    return resources.contains(safeName) ? resources[safeName] : nullptr;
}

} // namespace teragon
