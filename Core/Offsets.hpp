#pragma once
#include "../Core/GlowMode.hpp"
#include "../Utils/Color.hpp"

// Core    
constexpr long OFF_REGION = 0x140000000;                      //[Static]->Region
constexpr long OFF_LEVEL = 0x16966f0;                         //[Miscellaneous]->LevelName
constexpr long OFF_LOCAL_PLAYER = 0x211fac8;                  //[Miscellaneous]->LocalPlayer
constexpr long OFF_ENTITY_LIST = 0x1d71858;                   //[Miscellaneous]->cl_entitylist

constexpr long OFF_NAME_LIST = 0xc275bf0;                     //[Miscellaneous]->NameList
constexpr long OFF_NAME_INDEX = 0x38;                         //nameIndex
constexpr long OFFSET_TIME_BASE = 0x20b8;                     //m_currentFramePlayer.timeBase

// HUD
constexpr long OFF_VIEWRENDER = 0x7389d40;                    //[Miscellaneous]->ViewRenderer
constexpr long OFF_VIEWMATRIX = 0x11a350;                     //[Miscellaneous]->ViewMatrix

// Player
constexpr long OFF_HEALTH = 0x036c;                           //[RecvTable.DT_Player]->m_iHealth
constexpr long OFF_MAXHEALTH = 0x04a8;                        //[RecvTable.DT_Player]->m_iMaxHealth
constexpr long OFF_SHIELD = 0x01a0;                           //[RecvTable.DT_TitanSoul]->m_shieldHealth
constexpr long OFF_MAXSHIELD = 0x01a4;                        //[RecvTable.DT_TitanSoul]->m_shieldHealthMax

constexpr long OFF_INATTACK = 0x0738af90;                     //[Buttons]->in_attack;
constexpr long OFF_INJUMP = 0x0738b0a0;                       //[Buttons]->in_jump;

constexpr long OFF_CAMERAORIGIN = 0x1f00;                     //[Miscellaneous]->CPlayer!camera_origin
constexpr long OFF_STUDIOHDR = 0x1020;                        //[Miscellaneous]->CBaseAnimating!m_pStudioHdr
constexpr long OFF_BONES = 0x0dd0 + 0x48;                     //m_nForceBone

constexpr long OFF_LOCAL_ORIGIN = 0x0188;                     //[DataMap.C_BaseEntity]->m_localOrigin
constexpr long OFF_ABSVELOCITY = 0x0170;                      //[DataMap.C_BaseEntity]->m_vecAbsVelocity

constexpr long OFF_ZOOMING = 0x1c01;                          //[RecvTable.DT_Player]->m_bZooming
constexpr long OFF_TEAM_NUMBER = 0x037c;                      //[RecvTable.DT_BaseEntity]->m_iTeamNum
constexpr long OFF_NAME = 0x04b9;                             //[RecvTable.DT_BaseEntity]->m_iName
constexpr long OFF_SIGNIFIER_NAME = 0x04b0;                   //[RecvTable.DT_BaseEntity]->m_iSignifierName
constexpr long OFF_LIFE_STATE = 0x06c8;                       //[RecvTable.DT_Player]->m_lifeState
constexpr long OFF_BLEEDOUT_STATE = 0x2710;                   //[RecvTable.DT_Player]->m_bleedoutState  
constexpr long OFF_LAST_VISIBLE_TIME = 0x19bd + 0x3;          //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3
constexpr long OFF_LAST_AIMEDAT_TIME = 0x19bd + 0x3 + 0x8;    //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 + 0x8
constexpr long OFF_VIEW_ANGLES = 0x2564 - 0x14;               //[DataMap.C_Player]-> m_ammoPoolCapacity - 0x14
constexpr long OFF_PUNCH_ANGLES = 0x2468;                     //[DataMap.C_Player]->m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
constexpr long OFF_YAW = 0x226c - 0x8;                        //m_currentFramePlayer.m_ammoPoolCount - 0x8

// Weapon 
constexpr long OFF_WEAPON_HANDLE = 0x1964;                    //[RecvTable.DT_Player]->m_latestPrimaryWeapons
constexpr long OFF_OFFHAND_WEAPON = 0x1974;                   //m_latestNonOffhandWeapons
constexpr long OFF_CURRENTZOOMFOV = 0x1600 + 0x00b8;          //m_playerData + m_curZoomFOV
constexpr long OFF_TARGETZOOMFOV = 0x1600 + 0x00bc;           //m_playerData + m_targetZoomFOV
constexpr long OFF_WEAPON_INDEX = 0x1798;                     //[RecvTable.DT_WeaponX]->m_weaponNameIndex
constexpr long OFF_PROJECTILESCALE = 0x04e4;                  //projectile_gravity_scale + BASE
constexpr long OFF_PROJECTILESPEED = 0x04dc;                  //projectile_launch_speed + BASE
constexpr long OFF_SKIN = 0x0d88;                             //m_nSkin

// Glow
constexpr long OFF_GLOW_ENABLE = 0x294;                       //Script_Highlight_GetCurrentContext
constexpr long OFF_GLOW_THROUGH_WALL = 0x278;                 //Script_Highlight_SetVisibilityType
constexpr long OFF_GLOW_FIX = 0x270;
constexpr long OFF_GLOW_HIGHLIGHT_ID = 0x298;                 //[DT_HighlightSettings].m_highlightServerActiveStates
constexpr long OFF_GLOW_HIGHLIGHTS = 0xb5cc530;               //HighlightSettings

//skins
bool skin_state = false;

// inventory manager
bool inv_debug = false;
constexpr long m_inventory = 0x18f8;                          //[RecvTable.DT_Player]->m_inventory

//Thirdperson

bool thirdPerson = false;
constexpr long m_hThirdPersonEnt = 0x36bc;
constexpr long thirdperson_override = 0x01d00750;             //Offset hat den selben Namen und ist einzigartig
constexpr long m_thirdPersonShoulderView = 0x36c0;            //Offset hat den selben Namen und ist einzigartig

//BunnyHop

bool hopelHase = false;

//Glow shit

//Visible Glow
GlowMode VisibleMode = { 2, 103, 96, 127 };
Color VisibleColor = { 0.0f, 1.0f, 30.0f };
float VisibleColorTemp[4] = {};

//Invisible Glow
GlowMode InvisibleMode = { 2, 103, 96, 100 };
Color InvisibleColor = { 3.0f, 2.0f, 12.0f };
float InvisibleColorTemp[4] = {};

//Knocked Glow
GlowMode KnockedMode = { 2, 103, 96, 127 };
Color KnockedColor = { 1, 1, 0.35 };
float KnockedColorTemp[4] = {};

//Locked Glow
GlowMode LockedOnMode = { 136, 103, 32, 127 };
Color LockedOnColor = { 14.0f, 0.75f, 0.75f };
float LockedOnColorTemp[4] = {};