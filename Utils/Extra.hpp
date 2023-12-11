#pragma once
#include "../Core/Offsets.hpp"
#include "Memory.hpp"
#include "../Core/LocalPlayer.hpp"
#include "XDisplay.hpp"
    
XDisplay *X11DisplayExtra = new XDisplay();
Display *display = XOpenDisplay(nullptr);

void SkinChange()
    {
        long LocalPlayerPtr = Memory::Read<long>(OFF_REGION + OFF_LOCAL_PLAYER);
        bool IsDead = (Memory::Read<short>(LocalPlayerPtr + OFF_LIFE_STATE) > 0);
        if (IsDead) return;

        //pointer to all weapons
        long weaponHandle = Memory::Read<long>(LocalPlayerPtr + OFF_WEAPON_HANDLE);
        long weaponHandleMasked = weaponHandle & 0xffff;
        if (weaponHandle == 0){
            std::cout << "No weapons\n";
            return;
        }
        else
        {
            //std::cout << "you got some weapons\n" << weaponHandle << std::endl;
        }

        //Viewmodel of the weapon currently held
        long wephandle = Memory::Read<long>(LocalPlayerPtr + OFF_WEAPON_HANDLE);
        wephandle &= 0xffff;
        if (wephandle == 0){
            return;
        }
        else{

            std::cout << "Current Weapon:[" << wephandle << "]\n";

        }

        //weapon entity of the weapon currently held
        long wep_entity = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + (weaponHandleMasked << 5));
        if (wep_entity == 0){
            return;
        }
        else{

            std::cout << "Current wep_entity:[" << wep_entity << "]\n";

        }

        std::map<int, std::vector<int>> weaponSkinMap;
        //Light ammo weapons
        weaponSkinMap[104] = { 6 };    //WEAPON_P2020 
        weaponSkinMap[80] = { 6 };     //WEAPON_RE45 
        weaponSkinMap[79] = { 11 };    //WEAPON_ALTERNATOR 
        weaponSkinMap[103] = { 2 };    //WEAPON_R99  
        weaponSkinMap[0] = { 10 };     //WEAPON_R301   
        weaponSkinMap[105] = { 2 };    //WEAPON_SPITFIRE 
        weaponSkinMap[88] = { 5 };     //WEAPON_G7 
        //Heavy ammo weapons
        weaponSkinMap[111] = { 10};    //Car-SMG 
        weaponSkinMap[20] = { 6 };     //Rampage 
        weaponSkinMap[110] = { 9 };    //3030  110
        weaponSkinMap[89] = {10 };     //WEAPON_HEMLOCK  
        weaponSkinMap[87] = { 8 };     //FlatLine  
        //Energy ammo weapons
        weaponSkinMap[112] = { 8 };    //WEAPON_NEMESIS  
        weaponSkinMap[109] = { 9 };    //WEAPON_VOLT 
        weaponSkinMap[106] = { 7 };    //WEAPON_TRIPLE_TAKE 
        weaponSkinMap[92] = { 3 };     //WEAPON_LSTAR 
        weaponSkinMap[83] = { 5 };     //WEAPON_DEVOTION 
        weaponSkinMap[85] = { 8 };     //WEAPON_HAVOC 
        //Sniper ammo weapons
        weaponSkinMap[1] = { 5 };      //WEAPON_SENTINEL 
        weaponSkinMap[82] = { 8 };     //WEAPON_CHARGE_RIFLE 
        weaponSkinMap[84] = { 7 };     //WEAPON_LONGBOW 
        //Shotgun ammo weapons
        weaponSkinMap[95] = { 5 };     //WEAPON_MOZAMBIQUE 
        weaponSkinMap[86] = { 8 };     //WEAPON_EVA8 
        weaponSkinMap[102] = { 7 };    //WEAPON_PEACEKEEPER 
        weaponSkinMap[94] = { 5 };     //WEAPON_MASTIFF 
        //Legendary ammo weapons
        weaponSkinMap[108] = { 5 };    //WEAPON_WINGMAN 
        weaponSkinMap[101] = { 7 };    //WEAPON_PROWLER
        weaponSkinMap[2] = { 3 };      //WEAPON_BOCEK
        weaponSkinMap[91] = { 6 };     //WEAPON_KRABER
        weaponSkinMap[158] = { 3 };    //WEAPON_THROWING_KNIFE
        weaponSkinMap[212] = { 2 };    //WEAPON_THERMITE_GRENADE 
       
        //What weapon are we curently holding
        int waponIndex = Memory::Read<int>(wep_entity + OFF_WEAPON_INDEX);
        //if we dont hold any weapon we dont have it in our Map. therefore its 0
        if (weaponSkinMap.count(waponIndex) == 0){
            std::cout << "No weapon\n";
            return;
        }
        else{

            std::cout << "Current weapon Index:[" << waponIndex << "]\n";

        }

        //skin of the weapon currently "somewhere"
        if (waponIndex == 112 | waponIndex == 2){
            std::cout << "Return because of invalid weapon\n";
            return;
        }
        int skinID = weaponSkinMap[waponIndex][0];

        long SkinAddr = LocalPlayerPtr + OFF_SKIN;
        long weaponSkin = wep_entity + OFF_SKIN;
        Memory::Write<int>(SkinAddr, skinID+1);
        Memory::Write<int>(weaponSkin, skinID);
        
    };

void Inventory_debug(){

    long LocalPlayerPtr = Memory::Read<long>(OFF_REGION + OFF_LOCAL_PLAYER);

    uintptr_t inv_pointer = Memory::Read<uintptr_t>(LocalPlayerPtr + m_inventory);
    std::cout << "Inventorypointer:[" << inv_pointer << "]\n";
}

void ThirdPerson(){
    
    long LocalPlayerPtr = Memory::Read<long>(OFF_REGION + OFF_LOCAL_PLAYER);
    if (thirdPerson){
        
        int over = Memory::Read<int>(LocalPlayerPtr + thirdperson_override + 0x6c);
        std::cout << thirdPerson << std::endl;

        Memory::Write<int>(OFF_REGION + thirdperson_override + 0x6c, 1);
    	Memory::Write<int>(LocalPlayerPtr + m_thirdPersonShoulderView, 1);
//------------------------------------------------------------------------------------------

    }
    if(!thirdPerson){
        Memory::Write<int>(LocalPlayerPtr + thirdperson_override + 0x6c, -1);
    	Memory::Write<int>(LocalPlayerPtr + m_thirdPersonShoulderView, 0);
    }
}

KeyCode spaceKey = XKeysymToKeycode(display, XK_space);

/*void BunnyHop() {
    if (X11DisplayExtra->KeyDown(spaceKey)) {
        // Spacebar is pressed
        XTestFakeButtonEvent(display, spaceKey, True, 0);
        usleep(15000);
        XTestFakeButtonEvent(display, spaceKey, False, 0);
        XFlush(display);
    }
}
*/

void update(){
    if(skin_state){
        SkinChange();
    }
    if(inv_debug){
        Inventory_debug();
    }
    if (thirdPerson){
        ThirdPerson();
    }
    /*if(hopelHase){
        BunnyHop();
    }*/
}