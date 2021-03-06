# C++ RPG game project

[![codecov](https://codecov.io/gh/lefticus/cpp_weekly_game_project/branch/master/graph/badge.svg)](https://codecov.io/gh/lefticus/cpp_weekly_game_project)

[![Build Status](https://travis-ci.org/lefticus/cpp_weekly_game_project.svg?branch=master)](https://travis-ci.org/lefticus/cpp_weekly_game_project)

[![Build status](https://ci.appveyor.com/api/projects/status/ro4lbfoa7n0sy74c/branch/master?svg=true)](https://ci.appveyor.com/project/lefticus/cpp-weekly-game-project/branch/master)

This implementation is based on the C++ weekly series of @lefticus: https://www.youtube.com/playlist?list=PLs3KjaCtOwSZ-74ryhrQQkqr8kZW50_mZ
This implementation is based on a fork of https://github.com/lefticus/cpp_starter_project

# Pre-requisites
- CMake 3.15+ version installed (Ubuntu has currently the version 3.10)
https://anglehit.com/how-to-install-the-latest-version-of-cmake-via-command-line/
- Open SSL Development package 
 sudo apt-get install libssl-dev
- PyPI package installer
sudo apt install python-pip
- Conan C/C++ package manager
pip install conan
Note: some problems may still happen to Conan installation, so a symbolic link may have to be created manually:
sudo ln -s ~/.local/bin/conan /usr/local/bin/conan
- X11 RandR extension library
sudo apt install libxrandr-dev
- libudev development files
sudo apt install libudev-dev
- C Compiler Cache
sudo apt install ccache
- Clang tool
sudo apt install clang-format
sudo apt install clang-tidy
