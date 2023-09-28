#!/bin/bash

DEVICE=denniz
VENDOR=oneplus

export originalPath=$(pwd)
export branch1="2by2/13"
export branch2="arrow/arrow-13.1"

if [ $(pwd) == "${ANDROID_BUILD_TOP}" ] ; then export originalPath=$(pwd)/device/$VENDOR/$DEVICE/patches/ ; fi

discardPatches() {
    cd $originalPath
    for i in $(ls -d */); do
        cd $originalPath
        path=$(tr _ / <<< "$i")
        cd ./../../../../"$path"
        
        git reset --hard $branch1 2>/dev/null || git reset --hard $branch2 2>/dev/null
    done
}

discardPatches

echo -e "\e[36m* Discard patches done!\e[m"

sleep 1
