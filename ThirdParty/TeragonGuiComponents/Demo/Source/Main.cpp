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

#include "../JuceLibraryCode/JuceHeader.h"
#include "TeragonGuiComponents.h"
#include "MainComponent.h"
#include "Resources.h"


namespace teragon {
//==============================================================================
class ComponentDemoApplication : public JUCEApplication
{
public:
    //==============================================================================
    ComponentDemoApplication() : JUCEApplication() {}

    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed()       { return true; }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        parameters.add(new FloatParameter("Float", 0, 100, 50));
        parameters.add(new IntegerParameter("Integer", 0, 100, 50));
        parameters.add(new DecibelParameter("Volume", -60, 6, 0));
        parameters.add(new FrequencyParameter("Frequency", 100, 20000, 700));
        parameters.add(new VoidParameter("Toggle Button"));
        parameters.add(new BooleanParameter("Push Button"));
        mainWindow = new MainWindow(parameters);

        // Normally, the audio process callback (ie, processBlock() for Juce
        // plugins, and processReplacing() for regular VSTs) should call
        // processRealtimeEvents(). The plugin must also call pause() and
        // resume() on the ConcurrentParameterSet so that events can be
        // applied when audio processing is not active. Since this demo app
        // doesn't have an audio callback, we simply pause the parameter set,
        // which will process all events immediately after scheduling them.
        parameters.pause();
    }

    void shutdown()
    {
        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow : public DocumentWindow
    {
    public:
        MainWindow(teragon::ConcurrentParameterSet &parameters) :
        DocumentWindow ("TeragonGuiComponent Demo", Colours::lightgrey, DocumentWindow::allButtons),
        parameters(parameters)
        {
            setContentOwned (new MainContentComponent(parameters, Resources::getCache()), true);
            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed()
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
        const ConcurrentParameterSet &parameters;
    };

private:
    ScopedPointer<MainWindow> mainWindow;
    ConcurrentParameterSet parameters;
};
} // namespace teragon

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (teragon::ComponentDemoApplication)
