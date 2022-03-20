if not exist "prereq/deps/ffmpeg.marker " (
    mkdir prereq/deps
    pushd prereq

    wget -P ./ https://github.com/BtbN/FFmpeg-Builds/releases/download/autobuild-2020-11-10-12-44/ffmpeg-n4.3.1-25-g1936413eda-win64-gpl-shared-4.3.zip
    7z x -y ffmpeg-n4.3.1-25