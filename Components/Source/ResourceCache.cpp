/*
Copyright (c) 2013 Teragon Audio. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include "ResourceCache.h"
#include "PluginParameterComponent.h"

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
