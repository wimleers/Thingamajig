#!/bin/sh

echo "|-----------------------------------|"
echo "| Building Thingamajig for Mac OS X |"
echo "|-----------------------------------|"
echo "[1/4] Generating an Xcode project file ..."
rm -rf Thingamajig.app Thingamajig.dmg Thingamajig.xcodeproj build
hdiutil unmount -force -notimeout -quiet /Volumes/Thingamajig
qmake Thingamajig.pro

echo "[2/4] Building the project using the Release configuration ..."
xcodebuild -project Thingamajig.xcodeproj -configuration Release build clean > /dev/null

echo "[3/4] Copying the necessary Qt frameworks into the application bundle and package into a DMG..."
macdeployqt Thingamajig.app -dmg

echo "[4/4] Mounting & showing the DMG ..."
hdiutil attach ./Thingamajig.dmg > /dev/null
open /Volumes/Thingamajig

cd ..
echo "All done! ~/Desktop/Thingamajig.dmg is ready for release!"
