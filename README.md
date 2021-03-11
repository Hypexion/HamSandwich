# HamSandwich

![Screenshots of game title screens](docs/titlescreens.png)

## Building

The recommended way to compile the games is [MinGW on Windows](#windows-mingw).
The following platforms also have various levels of support:

Platform | Toolchain | Status | Notes
-|-|-|-
Windows | MinGW | Primary | CI: [Appveyor](https://ci.appveyor.com/project/SpaceManiac/hamsandwich)
Linux | GCC | Primary | CI: [Appveyor](https://ci.appveyor.com/project/SpaceManiac/hamsandwich)
[Browser](#Emscripten) | Emscripten | Secondary | [Play now](https://spacemaniac.github.io/HamSandwich/)
Windows | MSVC | Secondary | CI: [Appveyor](https://ci.appveyor.com/project/SpaceManiac/hamsandwich)
Windows | Clang | Tertiary | No app icons
Linux | Clang | Tertiary
[Android](#Android) | NDK | Tertiary | Incomplete

### Windows (MinGW)

First-time setup:

1. Install MSYS2, an environment for compiling C++ code.
    1. Visit <https://www.msys2.org/> and download and run the latest "msys2-x86_64" installer.
    2. Choose a relatively short path with no spaces (say, `C:\msys64` or `D:\tools\msys2`).
    3. After installation finishes, run `pacman -Syu` in the console that opens.
    4. When asked to do so, close the console and reopen it from the Start Menu (MSYS2 64bit > MSYS2 MinGW 32-bit).
    5. Run `pacman -Syu` again.
2. Use `cd` to select the directory where HamSandwich will go.
    1. For example, if you want the code to go in `C:\projects\HamSandwich`, run `cd C:\projects`.
3. Run `pacman -S git` to install git, a tool used for source code collaboration.
4. Run `git clone https://github.com/SpaceManiac/HamSandwich` to download the code.
5. Run `cd HamSandwich` to enter the directory.

Compiling and running:

1. Run `./run` to see a list of games in the project, and use `./run <project>` to compile and play.
    1. For example, to run Supreme With Cheese, write `./run supreme`.
    2. To compile without running, write `make` or `make <project>`.
    3. The first time you try to run a game, you will be prompted to download
        its installer from <https://hamumu.itch.io/>;
        follow the instructions shown.
2. Run `git pull` to fetch changes which have been published here.

### Windows (MSVC)

1. Double-click `tools/msvc/Generate VS2019 Solution.bat`, **or**:
    1. Download dependencies by running `powershell tools/msvc/install-dependencies.ps1`.
    2. Run `build/premake5.exe vs2019` (or appropriate VS version) to generate the solution files.
2. Open and compile `build/msc-v142/HamSandwich.sln` in Visual Studio.
    1. For command-line builds, run `msbuild build/HamSandwich.sln /p:Configuration=debug /p:Platform=Win32`.
3. Use installers from <https://hamumu.itch.io/> to extract game assets to `build/game/<project>`.
4. Debug from within Visual Studio to launch a game.

### Linux

1. Install dependencies (handled automatically on Ubuntu, Arch):
    1. premake-5.0.0-alpha15-linux.tar.gz from <https://github.com/premake/premake-core/releases/tag/v5.0.0-alpha15>.
    2. 32-bit G++ (or Clang) toolchain.
    3. 32-bit SDL2, SDL2_mixer, and SDL2_image development packages.
    4. 7-Zip and Innoextract to extract game assets.
2. Use `make` and `./run` as described above to build and run the games.

### Emscripten

1. If on Windows, install and use MSYS2 according to the instructions above.
2. The [Emscripten SDK] will be installed automatically, or you can do so
   manually:
    1. `cd` to a convenient directory.
    2. `git clone https://github.com/emscripten-core/emsdk.git`
    3. `cd emsdk`
    4. `./emsdk install latest-upstream`
    5. `./emsdk activate latest-upstream`
    6. `source ./emsdk_env.sh`
    7. Return to the HamSandwich directory.
2. Run `./run <project> --web` to run the build and open the result in your
   browser.

Bundling assets:

1. Commit your assets to a subfolder in the repository of your choosing.
2. In the appropriate project's section in `premake5.lua`, add a line pointing
   to your assets: `assetdirs "your_asset_folder"`

Publishing on GitHub Pages:

1. Edit `.github/workflows/publish-pages.yml` file and change the
   `distribute-web.sh` line to include only the project or projects you wish to
   publish.
2. Push your changes to GitHub and wait for the build to be prepared.
3. In your GitHub repository's Settings > Options tab, GitHub Pages section,
   change the "Source" from "None" to "gh-pages" and click "Save".
4. Your site will be published at `https://yourusername.github.io/HamSandwich`
5. Future pushes will automatically update your site.

Publishing manually:

1. Run `tools/build/distribute-web.sh <project>`.
   1. You can supply multiple projects to build them together, or leave off
   1. You can leave off the project identifier
2. Upload the contents of `build/webroot/`.

[Emscripten SDK]: https://emscripten.org/docs/getting_started/downloads.html

### Android

1. If on Windows, install and use MSYS2 according to the instructions above.
2. Install Gradle and the Android SDK and set `ANDROID_HOME`.
    1. Example shell command: `export ANDROID_HOME='C:\Wherever you installed the Android SDK\'`
3. Run `./android <project>` to compile APKs.
    1. For example, to build Supreme With Cheese, write `./android supreme`
4. Run `./android --install <project>` to install to a connected Android device.
5. To view logs, run `./android --logcat`
