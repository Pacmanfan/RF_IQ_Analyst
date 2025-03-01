# this script packs the Analyst application into an AppImage executable. This can be further packaged into a wpk
# this script requires linuxdeployqt and appimagetool to be installed and pathed correctly on the system
# I keep mine in /usr/local/bin and set up a soft link for both
# ex: 
# sudo ln -s /usr/local/bin/appimagetool-x86_64.AppImage /usr/local/bin/appimagetool
# sudo ln -s /usr/local/bin/linuxdeployqt-6-x86_64.AppImage /usr/local/bin/linuxdeployqt

baseapp=Analyst
packdir=$baseapp.appimage_build
appname=$baseapp.gui
appImageName=$baseapp.AppImage

### Check to see if pack directory exists ###
if [ ! -d ./$packdir ] 
then
    echo "Directory $packdir does not exist, creating..."     
    mkdir $packdir # remake the directory
else
    echo "Directory $packdir exists, cleaning..."     
    rm -r ./$packdir # remove the old directory
    mkdir $packdir # remake the directory
fi

## check to see if old AppImage exists
if [ -f "$appImageName" ]; then
    rm $appImageName #remove it
fi

cp $appname ./$packdir # copy the main executable into the directory
cp -r ./plugins ./$packdir/ # copy plugins into the package directory
cp -r ./classifiers ./$packdir/ # copy classifiers into the package directory
cp ./default.desktop ./$packdir/ # copy desktop file into the package directory
cp ./Analyst.png ./$packdir/ # copy icon file into the package directory
cd ./$packdir
linuxdeployqt ./$appname -appimage -bundle-non-qt-libs 
rm Analyst-x86_64.AppImage
cd ..
appimagetool ./$packdir ./$appImageName #generate the appimage
#rm -r ./$packdir # remove the directory

echo "Done!"

