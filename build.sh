#!/bin/sh

set -xe

Platform="web"

while getopts ":p:" opt; do
  case ${opt} in
    p )
      Platform=$OPTARG
      ;;
    \? )
      echo "Invalid Option: -$OPTARG" 1>&2
      exit 1
      ;;
    : )
      echo "Invalid Option: -$OPTARG requires an argument" 1>&2
      exit 1
      ;;
  esac
done
shift $((OPTIND -1))

if [ "$Platform" = "web" ] ; then
    echo "Building for web..."
    emcc -o ./web/main.html main.c -Os -Wall -Wextra $HOME/Documents/raylib/src/libraylib.a -I. -I$HOME/Documents/raylib/src/ -L. -L$HOME/Documents/raylib/src/ -s USE_GLFW=3 -s ASYNCIFY --shell-file $HOME/Documents/raylib/src/shell.html -DPLATFORM_WEB -s FORCE_FILESYSTEM=1 -s ALLOW_MEMORY_GROWTH=1 #--preload-file ./assets/zenzen.ogg
    emrun ./web/main.html
elif [ "$Platform" = "desktop" ] ; then
  echo "Building for desktop..."
  gcc -g ./*.c -o ./game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
  ./game
else
    echo "Invalid platform: $Platform"
    exit 1
fi


