
Mem to myself for next update:

    Skinchanger write doesn't have to be always. It just needs to be writen once. After that add a check to see if the weapon id is different and if yes write again.

# Updates
- FOV Circle (You'll have to manually set the Game FOV in ESP section, cl_fovScale broke so idk how to get game's FOV automatically)
- FOV now scales with Scopes's zoom
- Fixed Sense
- Fixed Aimbot Prediction
- RCS
- Offsets fixes
- Bone Selection is now replaced with auto select best bone
- Removed Allow Target Switch because it somehow causes xap-client to crash
- Aim-Assist will no longer be activated while holding grenade

# Credits
arturzxc: for the features (ESP, Triggerbot, Aimbot) and X11Display's XTestFakeRelativeMotionEvent
Koelion (Braziliana): menu, aimbot calculations
unguhelvu : Seer-Styled ESP
unknowncheats: basic knowledge and offsets


# Installation
**1.Install dependencies**

    sudo apt-get install -y libudev-dev
    sudo apt install cmake xorg-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
    sudo apt-get install build-essential
    sudo apt-get install libx11-dev
    sudo apt-get install libxtst-dev

**2.Build glfw**

    git clone https://github.com/glfw/glfw.git
    cd glfw
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

**3. Clone repo**

    git clone https://github.com/Nexilist/xap-client.git
    cd xap-client

**4. Build and Run**

    mkdir build
    cd build
    cmake ..
    make
    sudo ./xapclient
    
**5. Press Strg +Insert to toggle the Menu (You can only interact with the Menu and the game when the menu is active).**
