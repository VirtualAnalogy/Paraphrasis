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

#ifndef IMAGECACHE_H_INCLUDED
#define IMAGECACHE_H_INCLUDED

#include "JuceHeader.h"

namespace teragon {

/**
* This class provides storage for image resources. In order to make editing
* plugins efficient in Introjucer, all graphics are saved as resources in
* the Resources class and cached here. Each image can have three states:
* normal, alternate, and background.
*
* Usually you want to create a ResourceCache with the Resources::getCache()
* method, and passing the associated pointer to the GUI Component. Note that
* you must delete the ResourceCache created from this call when the GUI
* is destructed or closed, otherwise memory will be leaked.
*/
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

    virtual ImageStates* get(const String &name) const;
    virtual ImageStates* operator[](const String &name) const { return get(name); }

private:
    typedef juce::HashMap<String, ImageStates*> ResourceMap;
    ResourceMap resources;
};

} // namespace teragon

#endif  // IMAGECACHE_H_INCLUDED
