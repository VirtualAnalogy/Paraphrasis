git remote add -f TeragonGuiComponents git://github.com/VirtualAnalogy/TeragonGuiComponents.git
git merge -s ours --no-commit TeragonGuiComponents/master
git read-tree --prefix=ThirdParty/TeragonGuiComponents -u TeragonGuiComponents/master
git commit -m "Subtree merged in ThirdParty/TeragonGuiComponents"

git remote add -f arduino-base64 git://github.com/VirtualAnalogy/arduino-base64.git
git merge -s ours --no-commit arduino-base64/master
git read-tree --prefix=ThirdParty/TeragonGuiComponents/Components/Plugin/arduino-base64/ -u arduino-base64/master
git commit -m "Subtree merged in ThirdParty/TeragonGuiComponents/Components/Plugin/arduino-base64"

git remote add -f PluginParameters git://github.com/virtualanalogy/PluginParameters.git
git merge -s ours --no-commit PluginParameters/master
git read-tree --prefix=ThirdParty/TeragonGuiComponents/Components/PluginParameters/ -u PluginParameters/master
git commit -m "Subtree merged in ThirdParty/TeragonGuiComponents/Components/PluginParameters/"

git remote add -f readerwriterqueue git://github.com/VirtualAnalogy/readerwriterqueue.git
git merge -s ours --no-commit readerwriterqueue/master
git read-tree --prefix=ThirdParty/TeragonGuiComponents/Components/PluginParameters/include/readerwriterqueue/ -u readerwriterqueue/master
git commit -m "Subtree merged in ThirdParty/TeragonGuiComponents/Component/PluginParameters/include/readerwriterqueue"

git remote add -f tinythreadpp git://github.com/VirtualAnalogy/tinythreadpp.git
git merge -s ours --no-commit tinythreadpp/master
git read-tree --prefix=ThirdParty/TeragonGuiComponents/Components/PluginParameters/include/tinythread/ -u tinythreadpp/master
git commit -m "Subtree merged in ThirdParty/TeragonGuiComponents/Components/PluginParameters/include/tinythread"
