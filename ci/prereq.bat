if not exist "prereq/deps/ffmpeg.marker " (
    mkdir prereq/deps
    pushd prereq

    wget -P ./ https://github.com/BtbN/FFmpeg-Builds/releases/download/autobuild-2020-11-10-12-44/ffmpeg-n4.3.1-25-g1936413eda-win64-gpl-shared-4.3.zip
    7z x -y ffmpeg-n4.3.1-25-g1936413eda-win64-gpl-shared-4.3.zip
    mv ffmpeg-n4.3.1-25-g1936413eda-win64-gpl-shared-4.3 deps/ffmpeg

    copy /y nul deps/ffmpeg.marker
    popd
)

if not exist "prereq/deps/tensorflow.marker " (
    mkdir prereq/deps
    pushd prereq

    wget -P ./ https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-cpu-windows-x86_64-1.15.0.zip
    7z x -y -odeps/tensorflow libtensorflow-cpu-windows-x86_64-1.15.0.zip

    copy /y nul deps/tensorflow.marker
    popd
)

if not exist "prereq/deps/boost.marker " (
    mkdir prereq/deps
    pushd prereq

    wget -P ./ https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.zip
    7z x -y boost_1_72_0.zip

    pushd boost_1_72_0
    call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
    bootstrap.bat
    b2 -j4 link=static threading=multi variant=release toolset=msvc-16.0 --build-type=minimal runtime-link=static --prefix=../deps/boost --build-dir=./boost.build/ --layout=tagged architecture=x86 address-model=64 install
    popd

    copy /y nul deps/boost.marker
    popd
)

if not exist "prereq/build.env" (
    mkdir prereq