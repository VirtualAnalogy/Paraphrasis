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

#include "../JuceLibraryCode/JuceHeader.h"
#include "TeragonGuiComponents.h"
#include "MainComponent.h"
#include "Resources.h"


namespace teragon {
//==============================================================================
class ComponentDemoApplication  : public JUCEApplication, public Timer
{
public:
    //==============================================================================
    ComponentDemoApplication() : JUCEApplication(), Timer() {}

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
        startTimer(33); // ~30fps
    }

    void shutdown()
    {
        mainWindow = nullptr; // (deletes our window)
        stopTimer();
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

    void timerCallback()
    {
        // Process the events from the parameter set. This should be called from
        // audio thread of a plugin, or otherwise in the "main" thread of your
        // application.
        parameters.processRealtimeEvents();
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow : public DocumentWindow
    {
    public:
        MainWindow(teragon::ThreadsafePluginParameterSet &parameters) :
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
        const ThreadsafePluginParameterSet &parameters;
    };

private:
    ScopedPointer<MainWindow> mainWindow;
    ThreadsafePluginParameterSet parameters;
};
} // namespace teragon

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (teragon::ComponentDemoApplication)
