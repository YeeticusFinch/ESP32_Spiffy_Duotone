//#include <ArduinoOTA.h>
//#include <WiFi.h>
//#include <ESPmDNS.h>
//#include <WiFiUdp.h> //Dont do this, not needed

#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>
#include "SPIFFS.h"

//#include <WS2812_ESP_RMT.h>

//#include <Adafruit_NeoPixel.h>
#include <BluetoothSerial.h>
//#include <time.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define FORMAT_SPIFFS_IF_FAILED true

BluetoothSerial SerialBT;

//////////////////////////// HEY WEIRDO!!! THIS IS IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int mOffset = 0; //choose this one if you have a Lolin32
//int mOffset = -800; //Choose this one if you have a TTGO

const int NUMPIXELS = 15;
//ESPRMTLED FastLED = ESPRMTLED(NUMPIXELS, 18, RMT_CHANNEL_0);

//Adafruit_NeoPixel FastLED = Adafruit_NeoPixel(15, 18, NEO_GRB + NEO_KHZ800);

//struct tm *timeinfo; //Some random line required for storing time, not sure why

const int songCount = 96;
String songs = "0) The Following Theme\n1) Stranger Things Title Screen\n2) Sonata in C 3rd Movement\n3) Doctor Who Theme\n4) Skyrim Title Screen\n5) Cello Concerto\n6) Secunda\n7) Evil Morty\n8) Ward\n9) Love the Way You Lie Skylit Drive Remix\n10) Spooky Scary Skeletons\n11) Seven Nation Army\n12) Goodbye Moonmen\n13) All Star but its so Beautiful\n14) Crab Rave\n15) Happy Birthday\n16) Natural\n17) Heathens\n18) Rick and Morty Intro\n19) Waterloo\n20) Take on Me\n21) Despacito\n22) Interstellar Firstep\n23) Overwatch Theme\n24) Control\n25) A Cruel Angel's Thesis Neon Genesis\n26) Soviet National Anthem\n27) Beastars OP\n28) Stairway to Heaven\n29) Memelovania\n30) Imagine Communism\n31) Sweeeeet Child O' Mine\n32) Kiss of Death\n33) The Game is On, Sherlock\n34) Bohemian Rhapsody\n35) Fade\n36) For Whom the Bell Tolls\n37) Cantina\n38) The Force Awakens - Rey's Theme\n39) Marble Machine - Wintergatan\n40) O Fortuna\n41) Crazy Train\n42) Thunderstruck\n43) Charol of the Bells\n44) Thomas the Dank Engine\n45) Højt fra træets grønne top\n46) Teeth\n47) Maple Leaf Rag\n48) A Cruel Angel's Meme\n49) The Other Side of Paradise\n50) InSaNiTy\n51) Ghost Fight\n52) I Am The Doctor\n53) Old Town Road\n54) Senorita\n55) Dance Monkey\n56) YMCA\n57) The Swan\n58) Sweet but Psycho\n59) Dear Society\n60) ﻿Uragirimono No Requiem (JoJo)\n61) Giorno's Theme (JoJo)\n62) A Butterflies Wings (JoJo Rabit)\n63) Every Girl's A Super Girl (JoJo)\n64) Clair De Lune\n65)Jazz In Paris\n66) Cohen's Masterpiece (Bioshock)\n67) Out Of The Black\n68) Moonage DayDream\n69) Space Oddity\n70) Changes\n71) Teeth A\n72) Teeth B\n73) Seven Nation Army A\n74) 7 Nation Army B\n75) Great War - Sabaton\n76) Hyatt A\n77) Hyatt B\n78) Hyatt C\n79) Cohen A\n80) Cohen B\n81) Cohen C\n82) RWBY\n83) Criminal\n84) Crystal Dolphin A\n85) Crystal Dolphin B\n86) Brass Knob\n87) Bang A\n88) Bang B\n89) Bang C\n90) Crab Rave A\n91) Crab Rave B\n92) Crab Rave C\n93) Russian Crab Rave\n94) Gourmet Race A\n95) Gourmet Race B";
String fileNames[] = {
  "/TheFollowingTheme.txt",
  "/StrangerThingsTitleScreen.txt",
  "/SonatainC3rdMovement.txt",
  "/DoctorWhoTheme.txt",
  "/Dragonborn.txt",
  "/CelloConcerto.txt",
  "/Secunda.txt",
  "/EvilMorty.txt",
  "/Ward.txt",
  "/LovetheWayYouLie.txt",
  "/SpookyScarySkeletons.txt",
  "/7NationArmy.txt",
  "/GoodbyeMoonmen.txt",
  "/AllStar.txt",
  "/CrabRave.txt",
  "/HappyBirthday.txt",
  "/Natural.txt",
  "/Heathens.txt",
  "/RickandMorty.txt",
  "/Waterloo.txt",
  "/TakeOnMe.txt",
  "/Despacito.txt",
  "/Firstep.txt",
  "/OverwatchTheme.txt",
  "/Control.txt",
  "/ACruelAngelsThesis.txt",
  "/USSRAnthem.txt",
  "/Beasters.txt",
  "/StairwaytoHeaven.txt",
  "/Memelovania.txt",
  "/ImagineCommunism.txt",
  "/SweetChildofMine.txt",
  "/KissofDeath.txt",
  "/Sherlock.txt",
  "/BohemianRapsody.txt",
  "/Fade.txt",
  "/ForWhomtheBellTolls.txt",
  "/Cantina.txt",
  "/ReysTheme.txt",
  "/MarbleMachine.txt",
  "/Fortuna.txt",
  "/CrazyTrain.txt",
  "/Thunderstruck.txt",
  "/CharolofBells.txt",
  "/ThomastheDankEngine.txt",
  "/DanishChristmas.txt",
  "/Teeth.txt",
  "/MapleLeafRag.txt",
  "/CruelAngelsMeme.txt",
  "/TheOtherSideofParadise.txt",
  "/Insanity.txt",
  "/GhostFight.txt",
  "/IAmTheDoctor.txt",
  "/OldTownRoad.txt",
  "/Senorita.txt",
  "/DanceMonkey.txt",
  "/YMCA.txt",
  "/Swan.txt",
  "/SweetbutPsycho.txt",
  "/DearSociety.txt",
  "/Traitor.txt",
  "/Giorno.txt",
  "/Butterfly.txt",
  "/SuperGirl.txt",
  "/clair.txt",
  "/JazzInParis.txt",
  "/Cohen.txt",
  "/Outofblack.txt",
  "/MoonageDaydream.txt",
  "/SpaceOddity.txt",
  "/Changes.txt",
  "/TeethA.txt",
  "/TeethB.txt",
  "/7NationA.txt",
  "/7NationB.txt",
  "/GreatWar.txt",
  "/HyattA.txt",
  "/HyattB.txt",
  "/HyattC.txt",
  "/CohenA.txt",
  "/CohenB.txt",
  "/CohenC.txt",
  "/theDay.txt",
  "/Criminal.txt",
  "/CrystalA.txt",
  "/CrystalB.txt",
  "/BrassKnob.txt",
  "/BangA.txt",
  "/BangB.txt",
  "/BangC.txt",
  "/CrabA.txt",
  "/CrabB.txt",
  "/CrabC.txt",
  "/RussianCrab.txt",
  "/GourmetA.txt",
  "/GourmetB.txt",
};

String newFeatures = "What's new?\n- Gave up on the changelog";
int hourMod = 0;
int minuteMod = 0;
long millisMod = 0;
long playAt = -1;
const int yeetSize = 16384;
char (*(yeet[])) = {(char *)malloc(yeetSize), (char *)malloc(yeetSize), (char *)malloc(yeetSize), (char *)malloc(yeetSize)}; //YEEET

File file;

int table[] = { 
//0,  1,    2,    3,    4,    5,    6,  7,   8,   9,  10,  11,  12,   13,   14,  15, 16,  17,  18,  19, 20,   21,   22,  23, 24,   25,   26, 27,  28,  29,  30,  31, 32,  33,  34,   35,  36,  37, 38, 39,  40,   41, 42,   43, 44, 45, 46,  47,  48,  49,   50, 51,  52,  53,  54,  55,  56,  57,   58,  59,  60,  61,  62,  63,   64, 65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,
  0, -2, 1760, 1397, 1568, 1319, 1175, 55, 440, 349, 392, 330, 294, 1480, 1109, 988, 47, 370, 278, 247, -7, 6000, 1000, 500, -5, 8000, 2000, -4, 110, 131, 175, 165, 92, 147, 139, -228, 196, 262, 82, 98, 123, -240, -6, 4000, 73, 41, 62, 659, 587, 494, 1500, -3, 784, 698, 523, 554, 880, 740, 1047, 831, 622, 466, 415, 311, 1245, -8, -16, -12, -32, -14, -22, -28, -10, -60, 220, 185, 208, -68, 12000, 3000, -11, -9, -96, -49, -18, 117, 156, 65, 49, 933, 668, 334, 2004, 1336, 501, 167, 77, 59, 233, 664, 332, 1328, 996, 1992, 83, 166, 2093, 1865, 1661, 408, -58, 816, 204, -62, -31, 136, 102, -128, 51, 612, 33, 37, 39, 31, 52, 104, 116, 87, 44, 1600, 800, 400, 200, 600, -30, -36, -46, 1112, 834, 2224, 556, -20, -24, -82, 417, -57, -230, -224, -17, 1560, 390, 780, 585, 195, 1170, -13, 3120, -64, -15, 2340, -136, 932, 1200, 3951, 277, 2637, 3136, 2349, 1976, 2489, 2960, 3520, 381, 127, 254, 1016, 508, 1524, 762, 2032, -19, 828, 621, 414, 207, 1656, 3312, 1242, 276, 2484, 1449, 69, 1248, 416, 1664, 832, -79, 3328, 1872, 624, 312, 468, 1092, 936, -21, 2496, 61, 124, -51, -26, -52, 240, 120, 480, 250, 2400, 300, 150, -48, 450, 900, 225, 75, 1800, 182, 91, 728, 364, 1456, 546, -100, 4186, 3729, 3322, 2794, 2217, 1056, 176, 1408, 528, 704, 352, 1232, -124, 356, 178, 1424, 
};

int table2[] = {
  0, -2, 294, 370, 494, 587, 554, 466, 659, 740, 330, 440, 392, -5, -4, -3, -6, 784, 880, -9, -15, -13, 1175, 1109, 988, 1319, 1568, 1760, 1480, 2016, 84, -8, 1344, 504, 336, 1008, 168, 672, 224, -7, -12, -10, 2688, 185, 196, 220, 233, 123, 247, 98, 73, 147, 110, 62, 2704, 1352, 507, 338, 169, 2028, -24, -256, 676, 1014, -68, -225, 523, 175, 87, 49, 1047, 1976, 2093, 1397, 698, 262, 2637, 2349, 349, 165, 131, 5760, 1920, 3840, 960, 1440, 480, 360, 240, -1140, -64, -75, 932, 4, 8, 16, 320, -222, 160, -96, -52, -84, -16, 15360, 55, 82, 65, 44, 41, 1992, 996, -160, 5976, 2988, -41, -43, 3984, 7968, -51, -28, 332, -33, 498, -72, -38, 249, -128, 1494, 15936, 1245, 831, 1500, 250, 500, 1000, 125, 750, 2000, 375, 278, -17, 92, 104, -112, 415, 311, 208, 622, 1750, 139, 156, 117, 77, -32, -26, 933, 116, 69, 720, 60, 930, 450, 120, -124, 52, 59, 1800, -31, 420, 1600, 50, 100, -18, 400, 800, 600, 200, 1200, 29, 39, 37, 33, 2400, -14, 3200, 56, 112, 896, -19, 448, -11, -23, -65, 28, 4000, 3000, 8000, 6000, -21, -22, 875, -30, 1661, 1865, 2217, 2489, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 277, 124, 248, 31, 496, 372, 992, 93, 1984, 744, 47, 35, 46, 61, 428, 856, 642, 214, 3424, 1284, 1712, 2568, -78, 216, -190, 432, 648, 1296, 1512, 1728, 324, 54, 864, 108, -34, 27, -27, 288, -39, 7000
};

int table3[] = {
  0, 294, 440, 415, 466, 392, 587, -2, 554, 659, 698, 880, 784, -3, 831, 933, 1175, 1109, 1319, 1397, 1760, 1568, 1047, 494, 988, 1480, 1661, 349, 330, 740, 370, 1984, 248, -4, 124, 496, 992, 1488, -6, 62, 744, -32, 868, -33, -12, -9, 73, 147, 55, 98, 196, 82, 87, 110, 116, 165, 175, 139, 220, 247, 278, 104, 123, 185, 208, 92, 500, 250, -8, -62, 1000, -34, -18, -19, -29, -46, 750, 125, 2000, -5, 311, 233, 262, 131, 277, 77, 65, 59, 69, -7, 523, 622, 2976, 372, 1116, 186, -10, 2232, 558, -11, -26, -16, 156, -48, -14, 93, -20, -17, -44, 932, 1245, 1865, 2489, 2217, -28, 668, 334, 167, -15, 2672, -128, 1336, -88, -13, 2004, -104, 1976, 7968, 1992, 5976, 3984, 996, 498, -65, 747, 664, 1328, 1494, 41, 49, 47, 44, 117, 8016, 6012, 4008, 501, 1002, -129, 3006, 375, -24, -25, -30, 329, 288, 108, 18, 144, 576, 1152, 2304, 216, 36, 432, 864, 192, 72, 384, 96, 61, 39, 52, 264, 528, 2112, 1056, 132, 66, 198, 33, 99, 396, 1584, -39, 176, -258, -56, -54, -112, -115, 4000, 6000, 1692, 846, 2538, 423, -480, 224, 448, 896, -57, 672, 336, 112, 168, 56, 1344, -50, -37, 226, 452, 904, -586, 113, 339, -133, -221, 31, 912, 456, 228, 114, -570, 342, -22, 684, 1824, 1368, -64, 171, 37, 1808, 678, -161, -340, 1026, 1032, 688, 172, 43, 344, 3000, 1500, -73, -31, 428, 214, 856, 642, 107, 1712, 
};

int table4[] = {
  //0, -2, 415, 622, 523, 392, 466, 494, 659, -3, 831, 988, 1661, -7, 1245, 1397, 1047, 933, 698, 784, 1175, 1109, 554, 349, 740, 440, 311, 300, 150, -5, 600, -16, 1200, -8, -6, -4, -9, -12, 450, -14, 77, 104, 208, 110, 116, 277, 82, 52, 124, 247, 294, 329, 147, 165, 98, 123, 131, 92, 87, 233, 262, 370, 65, 69, 73, 59, 196, 139, -17, -36, -79, -84, -76, 587, -11, 880, 1568, 960, 720, 480, 240, 60, 930, 120, 360, 420, -10, -124, 1920, 1440, 156, 175, 3720, -31, 330, 278, 220, 856, 428, 1284, 214, 642, -15, -40, 1712, -38, 321, 107, 185, 117, 8000, 4000, 3000, 375, 250, 1000, 2000, -88, -24, 62, 1500, 500, 6000, -32, 264, 132, 528, 396, 198, 66, 1056, 176, 55, 46, 39, 49, 266, 133, 532, 1760, 2093, 1976, 1865, 1480, 1319, 368, 184, 552, 276, -28, 1472, 736, 1104, -384, -13, -30, 2208, -26, 644, 2576, -62, -256, -238, 932, 868, 434, 651, 217, 1302, 1736, 516, 258, 387, 129, 1032, 774, 520, 260, 195, 780, 2080, 306, 153, 612, 459, 1224, 918, 1836, 2448, -65, -23, -20, -22, 1914, 638, 1276, 319, 957, 320, -270, 80, 640, 1280, 350, 1808, 452, 226, 113, 904, 339, -42, 704, 352, 1408, 88, -64, 2816, 1232, 2112, 58, 41, 47, 130, 230, 115, 920, 690, 345, 460, 1840, 2944, 732, 1464, 2196, 2928, 366, 840, -312, -439, -257, -192, 
  0, -2, 415, 622, 523, 392, 466, 494, 659, -3, 831, 988, 1661, -7, 1245, 1397, 1047, 933, 698, 784, 1175, 1109, 554, 349, 740, 440, 311, 300, 150, -5, 600, -16, 1200, -8, -6, -4, -9, -12, 450, -14, 77, 104, 208, 110, 116, 277, 82, 52, 124, 247, 294, 329, 147, 165, 98, 123, 131, 92, 87, 233, 262, 370, 65, 69, 73, 59, 196, 139, -17, -36, -79, -84, -76, 587, -11, 880, 1568, 960, 720, 480, 240, 60, 930, 120, 360, 420, -10, -124, 1920, 1440, 156, 175, 3720, -31, 330, 278, 220, 856, 428, 1284, 214, 642, -15, -40, 1712, -38, 321, 107, 185, 117, 8000, 4000, 3000, 375, 250, 1000, 2000, -88, -24, 62, 1500, 500, 6000, -32, 264, 132, 528, 396, 198, 66, 1056, 176, 55, 46, 39, 49, 266, 133, 532, 1760, 2093, 1976, 1865, 1480, 1319, 368, 184, 552, 276, -28, 1472, 736, 1104, -384, -13, -30, 2208, -26, 644, 2576, -62, -256, -238, 932, 868, 434, 651, 217, 1302, 1736, 516, 258, 387, 129, 1032, 774, 520, 260, 195, 780, 2080, 306, 153, 612, 459, 1224, 918, 1836, 2448, -65, -23, -20, -22, 1914, 638, 1276, 319, 957, 320, -270, 80, 640, 1280, 350, 1808, 452, 226, 113, 904, 339, -42, 704, 352, 1408, 88, -64, 2816, 1232, 2112, 58, 41, 47, 130, 230, 115, 920, 690, 345, 460, 1840, 2944, 732, 1464, 2196, 2928, 366, 840, -312, -439, -257, -192, 828, 1656, 414, 138, 207, 37, 834, 1668, 1112, 556, 417, -57, -120, 
};

int table5[] = {
  //0, -3, 330, 440, 523, 659, 622, 494, 587, -2, 466, 554, 698, 415, 220, 262, 880, 831, 784, 740, 294, 165, 110, 98, 87, 82, 349, 175, 370, -6, 247, 392, 988, 1047, 1175, 1319, 1397, 8000, 750, 250, 1000, 2000, -8, 500, -4, -9, 1500, 6000, 375, 4000, -18, 125, 156, 147, 139, 131, 123, 116, 104, 73, 92, 55, 65, 77, 208, 52, 62, 311, 44, -48, -28, -34, -66, -19, -10, 233, 277, 329, 933, 1760, 2093, 2794, 1865, 1109, 1661, 1480, 1245, 2217, 185, 1976, 2637, 2960, 2349, 3729, 2489, 320, 240, 480, 1280, 640, 1920, 192, -15, -12, 3840, 360, 212, 428, -5, 59, 69, 196, 46, 124, 61, 332, 249, 498, 664, 1328, 1992, 3984, 5976, -90, -14, 756, 189, 378, 567, 1134, -7, -16, -17, -38, -36, -55, -24, -176, 3, 37, 49, 41, 188, 376, 752, 564, -258, -132, -45, 94, -192, -144, 856, 214, 642, 107, -26, 1712, 117, 278, 932, 1568, 252, 504, 1008, 2016, 4032, 3024, 1512, 126, 3528, 336, 3000, 2144, 268, -40, 1072, 134, 536, 804, -73, 1608, -11, -32, 402, -78, 67, 201, 33, -43, 1876, 1728, 216, 432, 864, -13, 648, -64, -72, 
  //0, -3, 330, 440, 523, 659, 622, 494, 587, -2, 466, 554, 698, 415, 220, 262, 880, 831, 784, 740, 294, 165, 110, 98, 87, 82, 349, 175, 370, -6, 247, 392, 988, 1047, 1175, 1319, 1397, 8000, 750, 250, 1000, 2000, -8, 500, -4, -9, 1500, 6000, 375, 4000, -18, 125, 156, 147, 139, 131, 123, 116, 104, 73, 92, 55, 65, 77, 208, 52, 62, 311, 44, -48, -28, -34, -66, -19, -10, 233, 277, 329, 933, 1760, 2093, 2794, 1865, 1109, 1661, 1480, 1245, 2217, 185, 1976, 2637, 2960, 2349, 3729, 2489, 320, 240, 480, 1280, 640, 1920, 192, -15, -12, 3840, 360, 212, 428, -5, 59, 69, 196, 46, 124, 61, 332, 249, 498, 664, 1328, 1992, 3984, 5976, -90, -14, 756, 189, 378, 567, 1134, -7, -16, -17, -38, -36, -55, -24, -176, 3, 37, 49, 41, 188, 376, 752, 564, -258, -132, -45, 94, -192, -144, 856, 214, 642, 107, -26, 1712, 117, 278, 932, 1568, 252, 504, 1008, 2016, 4032, 3024, 1512, 126, 3528, 336, 3000, 2144, 268, -40, 1072, 134, 536, 804, -73, 1608, -11, -32, 402, -78, 67, 201, 33, -43, 1876, 1728, 216, 432, 864, -13, 648, -64, -72, 3951, 3136, 3520, 2032, 508, 1016, 254, 1524, 381, 762, 127, -22, -20, 47, 31, 58, 
  //0, -3, 330, 440, 523, 659, 622, 494, 587, -2, 466, 554, 698, 415, 220, 262, 880, 831, 784, 740, 294, 165, 110, 98, 87, 82, 349, 175, 370, -6, 247, 392, 988, 1047, 1175, 1319, 1397, 8000, 750, 250, 1000, 2000, -8, 500, -4, -9, 1500, 6000, 375, 4000, -18, 125, 156, 147, 139, 131, 123, 116, 104, 73, 92, 55, 65, 77, 208, 52, 62, 311, 44, -48, -28, -34, -66, -19, -10, 233, 277, 329, 933, 1760, 2093, 2794, 1865, 1109, 1661, 1480, 1245, 2217, 185, 1976, 2637, 2960, 2349, 3729, 2489, 320, 240, 480, 1280, 640, 1920, 192, -15, -12, 3840, 360, 212, 428, -5, 59, 69, 196, 46, 124, 61, 332, 249, 498, 664, 1328, 1992, 3984, 5976, -90, -14, 756, 189, 378, 567, 1134, -7, -16, -17, -38, -36, -55, -24, -176, 3, 37, 49, 41, 188, 376, 752, 564, -258, -132, -45, 94, -192, -144, 856, 214, 642, 107, -26, 1712, 117, 278, 932, 1568, 252, 504, 1008, 2016, 4032, 3024, 1512, 126, 3528, 336, 3000, 2144, 268, -40, 1072, 134, 536, 804, -73, 1608, -11, -32, 402, -78, 67, 201, 33, -43, 1876, 1728, 216, 432, 864, -13, 648, -64, -72, 3951, 3136, 3520, 2032, 508, 1016, 254, 1524, 381, 762, 127, -22, -20, 47, 31, 58, 248, 496, 992, 1984, 1488, 372, 744, 667, 333, 308, -160, -30, -124, 
  0, -3, 330, 440, 523, 659, 622, 494, 587, -2, 466, 554, 698, 415, 220, 262, 880, 831, 784, 740, 294, 165, 110, 98, 87, 82, 349, 175, 370, -6, 247, 392, 988, 1047, 1175, 1319, 1397, 8000, 750, 250, 1000, 2000, -8, 500, -4, -9, 1500, 6000, 375, 4000, -18, 125, 156, 147, 139, 131, 123, 116, 104, 73, 92, 55, 65, 77, 208, 52, 62, 311, 44, -48, -28, -34, -66, -19, -10, 233, 277, 329, 933, 1760, 2093, 2794, 1865, 1109, 1661, 1480, 1245, 2217, 185, 1976, 2637, 2960, 2349, 3729, 2489, 320, 240, 480, 1280, 640, 1920, 192, -15, -12, 3840, 360, 212, 428, -5, 59, 69, 196, 46, 124, 61, 332, 249, 498, 664, 1328, 1992, 3984, 5976, -90, -14, 756, 189, 378, 567, 1134, -7, -16, -17, -38, -36, -55, -24, -176, 3, 37, 49, 41, 188, 376, 752, 564, -258, -132, -45, 94, -192, -144, 856, 214, 642, 107, -26, 1712, 117, 278, 932, 1568, 252, 504, 1008, 2016, 4032, 3024, 1512, 126, 3528, 336, 3000, 2144, 268, -40, 1072, 134, 536, 804, -73, 1608, -11, -32, 402, -78, 67, 201, 33, -43, 1876, 1728, 216, 432, 864, -13, 648, -64, -72, 3951, 3136, 3520, 2032, 508, 1016, 254, 1524, 381, 762, 127, -22, -20, 47, 31, 58, 248, 496, 992, 1984, 1488, 372, 744, 667, 333, 308, -160, -30, -124, 3322, 4978, 4435, 1125, 75, -212, -216, -168, 4186, 5588, 4699, 7459, -180, -140, 
};

int table6[] = {
  //73, -3, 87, 82, 110, 131, 123, 0, 440, -2, 392, 349, 330, 294, 587, 466, 523, 659, 262, -7, -6, 220, -4, 698, 147, 175, 165, 880, 784, 1047, 1175, 1397, 933, 1319, 1109, 233, 247, 196, -12, 116, 98, 1760, 250, -48, 500, -5, 1000, 750, 2000, 1500, 125, -35, 35, -8, -11, 63, 375, 83, -24, -9, 37, 44, 41, -32, -28, -16, -15, 139, 55, 554, 59, 277, 208, 185, 156, -19, -13, -92, -62, -61, -191, -60, -162, -14, -78, -66, 494, 740, 988, 4000, -10, -256, 3000, 2250, 6000, 4500, -33, 106, 188, 1125, -189, 831, 300, 1200, 900, 450, 150, 600, 1800, 400, 2400, 622, 311, 415, 370, 8000, 104, 1712, 856, 214, 428, 642, -23, 124, 107, -30, 65, -64, 
  //73, -3, 87, 82, 110, 131, 123, 0, 440, -2, 392, 349, 330, 294, 587, 466, 523, 659, 262, -7, -6, 220, -4, 698, 147, 175, 165, 880, 784, 1047, 1175, 1397, 933, 1319, 1109, 233, 247, 196, -12, 116, 98, 1760, 250, -48, 500, -5, 1000, 750, 2000, 1500, 125, -35, 35, -8, -11, 63, 375, 83, -24, -9, 37, 44, 41, -32, -28, -16, -15, 139, 55, 554, 59, 277, 208, 185, 156, -19, -13, -92, -62, -61, -191, -60, -162, -14, -78, -66, 494, 740, 988, 4000, -10, -256, 3000, 2250, 6000, 4500, -33, 106, 188, 1125, -189, 831, 300, 1200, 900, 450, 150, 600, 1800, 400, 2400, 622, 311, 415, 370, 8000, 104, 1712, 856, 214, 428, 642, -23, 124, 107, -30, 65, -64, 932, 1568, 92, 376, 94, 752, 1504, 47, 1128, 282, 49, 29, 117, 58, 33, 
  73, -3, 87, 82, 110, 131, 123, 0, 440, -2, 392, 349, 330, 294, 587, 466, 523, 659, 262, -7, -6, 220, -4, 698, 147, 175, 165, 880, 784, 1047, 1175, 1397, 933, 1319, 1109, 233, 247, 196, -12, 116, 98, 1760, 250, -48, 500, -5, 1000, 750, 2000, 1500, 125, -35, 35, -8, -11, 63, 375, 83, -24, -9, 37, 44, 41, -32, -28, -16, -15, 139, 55, 554, 59, 277, 208, 185, 156, -19, -13, -92, -62, -61, -191, -60, -162, -14, -78, -66, 494, 740, 988, 4000, -10, -256, 3000, 2250, 6000, 4500, -33, 106, 188, 1125, -189, 831, 300, 1200, 900, 450, 150, 600, 1800, 400, 2400, 622, 311, 415, 370, 8000, 104, 1712, 856, 214, 428, 642, -23, 124, 107, -30, 65, -64, 932, 1568, 92, 376, 94, 752, 1504, 47, 1128, 282, 49, 29, 117, 58, 33, 2093, 1245, 1865, 1976, 324, 162, 648, 486, 81, -18, -126, -124, 77, 
};

short hist[songCount];

boolean compressed = true;
boolean compressedBase = true;

int *tempMelody = NULL;
int *tempRhythmn = NULL;
int tempMelLength = 0;
int tempRhyLength = 0;

int *tempMelodyBase = NULL;
int *tempRhythmnBase = NULL;
int tempMelLengthBase = 0;
int tempRhyLengthBase = 0;

boolean playing = false;

int trebleTime = 0;
unsigned long trebleStamp = 0;
int baseTime = 0;
unsigned long baseStamp = 0;

float tmod = 0.2f;
float yeetDur = 0.5f;

int tin = 0;
int bin = 0;

int songNumber = 15;

boolean posa = false;

char storedColors[] = {120, 20, 0, 70, 70, 0, 0, 20, 120, 0, 150, 10}; //can store 4 colors

boolean repeat = false;
boolean shuffle = false;

int fancySize = -1;
int fancySizeBase = -1;

int getSize(int n) {
  return fancySize;
}



hw_timer_t * timer = NULL;
hw_timer_t * timer2 = NULL;
hw_timer_t * timer3 = NULL;

uint8_t pin1;
uint8_t channel1;

uint8_t pin2;
uint8_t channel2;

int buzzer1 = 4;
int buzzer2 = 25;

int brightness = 30;
int lightSpeed = 10;
int lightMode = 0;
void IRAM_ATTR onTimer(){
  //Serial.println("Yeet, we got an interrupt");
  ledcWrite(channel1, 0);
  //noTone(pin1, channel1);
}
void IRAM_ATTR onTimer2(){
  //Serial.println("Yeet, we got an interrupt");
  ledcWrite(channel2, 0);
  //noTone(pin2, channel2);
}
void IRAM_ATTR onTimer3() {
  playAt = -1;
  playing = true;
}

int jj[15];

CRGB leds[NUMPIXELS];


void yeetFile() {

  File root = SPIFFS.open("/");
 
  File yeetFile = root.openNextFile();

  bool fancyYoinkBool = false;
 
  while(yeetFile){
 
      Serial.print("FILE: ");
      Serial.println(yeetFile.name());
      const char* supaTemp = yeetFile.name();
      if (supaTemp[0] == '/' && supaTemp[1] == 'i' && supaTemp[2] == 'n' && supaTemp[3] == 'i' && supaTemp[4] == 't') {
        Serial.println("YYYOOOOIIINNNK");
        SPIFFS.remove("/init.txt");
        
        fancyYoinkBool = true;
        break;
      }

      
      yeetFile = root.openNextFile();
  }

  if (fancyYoinkBool == false) {
        shufSelect();
        shuffle = true;
        playing = true;
   }
  
  
}

void newYeetFile() {
  File yeetFile = SPIFFS.open("/init.txt", FILE_WRITE);
  yeetFile.print("YOINK");
}

String btName;

void setup() {

  
  ////////////////////////////////////////////////////////////HEY WEIRDO, THIS IS IMPORTANT, CHOOSE THE BLUETOOTH NAME OF YOUR WATCH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //btName = "Garrett's Faaaancy Runestone!!!";
  btName = "YEETICUS";
  //btName = "yeeticus2";
  //btName = "Osman's Fancy Non-Rodent Watch";
  //btName = "Clare's Fanciest Yeeter Watch";
  SerialBT.begin(btName);
  Serial.begin(74880);

  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("SPIFFS Mount Failed");
        return;
  }
  

  for (int i = 0; i < songCount; i++) {
    hist[i] = i;
  }
  
  for (int i = 0; i < NUMPIXELS; i++) {
    jj[i] = i*6;
  }

  yeetFile();
  
  //FastLED.begin();
  FastLED.setBrightness(100);
  FastLED.addLeds<WS2811, 18, GRB>(leds, NUMPIXELS).setCorrection( TypicalLEDStrip );
  
  FastLED.clear();
  
  FastLED.show();
  //songNumber = 8;
  // put your setup code here, to run once:
  
  Serial.println("Yeet");
  ledcAttachPin(buzzer1, 1);
  ledcAttachPin(buzzer2, 9);

  delay(200);
  
  tone(buzzer2, 1000, 150, 1, 1);
  delay(50);
  tone(buzzer1, 2000, 100, 0, 0);
  delay(100);
  tone(buzzer1, 3000, 50, 0, 0);
  tone(buzzer2, 500, 100, 1, 1);
  delay(50);
  tone(buzzer1, 3500, 100, 0, 0);
  delay(500);

  newYeetFile();
  
}


boolean lights = false;

int minutes = 0;
int sec = 0;
int hour = 0;
int day = 0;
int month = 0;
unsigned int loopCount = 0;
boolean holdAction = false;
void loop() {
  // put your main code here, to run repeatedly:
  /*if (WiFi.status() == WL_CONNECTED) {
    ArduinoOTA.handle();
  }
  if (WiFi.status() == WL_CONNECTED && millis() > 10000) {
    ArduinoOTA.end();
    WiFi.mode(WIFI_OFF);
    SerialBT.begin("YEETICUS");
    tone(buzzer2, 500, 100, 1, 1);
    delay(50);
    tone(buzzer1, 3500, 100, 0, 0);
    delay(500);
  }*/
  while (holdAction) {
    fancyInputStuffs();
  }
  fancyInputStuffs();

  if (posa) {
    binaryTime();
    timeStuff();
    delay(5000);
  } else {
    /*if (playAt != -1 && playAt <= millis()+millisMod) {
      //Serial.print(millis()+millisMod);
      //Serial.print(">=");
      //Serial.println(playAt);
      playAt = -1;
      playing = true;
    }*/
    if (loopCount > 2000) {
      timeStuff();
      loopCount = 0;
      //Serial.println("YeetTime");
    }
    if (playing) {
      if (fancySize == -1 || fancySizeBase == -1) {
        readFile();
      }
      decomPlay();
      decomPlayBase();
    }
    if (millis()%lightSpeed==0) {
      lightStuffs();
    }
    loopCount++;
  }

  //yield();
  
  //play();
  
}

void readFile() { //Streams a song from Yoink into Yeet

  Serial.print("Reading file: ");
  Serial.println(getYeetSong(songNumber));
  file = SPIFFS.open(getYeetSong(songNumber), FILE_READ);
  if (!file) {
    Serial.println("open failed");
  }
  // Rewind file so test data is not appended.
  file.seek(0);

  int i = 0;        // First array index.
  int j = 0;        // Second array index
  size_t n;         // Length of returned field with delimiter.
  char str[20];     // Must hold longest field with delimiter and zero byte.
  char delim = 0;   // Delimiter from previous line. Start with no delimiter.
  //Ok now its time to start the reeeeeeeading
  while (true) {
    n = readField(str, sizeof(str), ",\n");

    // Read error or at EOF.
    if (n == 0) {
      break;
    }
    // Advance indices based on previous delimiter.
    if (delim == '\n') {
      // previous delimiter was endl so start a new row.
      Serial.println("Finished Line");
      if (i == 0) {
        fancySize = j + 1;
        Serial.print("fancySize=");
        Serial.println(fancySize);
      } else if (i == 2) {
        fancySizeBase = j + 1;
      }
      if (++i >= 5) {
        Serial.println("too many lines");
      }
      if (j != (yeetSize - 1)) {
        Serial.println("missing field");
      }
      j = 0;
    } else if (delim == ',') {
      // previous delimiter was comma so advance column.
      if (++j >= yeetSize) {
        Serial.println("too many fields");
      }
    }
    // Save delimiter.
    delim = str[n-1];

    if (delim != ',' && delim != '\n' && delim != 0) {
      Serial.println("extra data in field");
    }
    if (delim == 0 && file.available() != 0) {
      Serial.println("read error or long line");
    }
    
    str[n-1] = '\0';
    yeet[i][j] = (char)atoi(str);
    //Serial.print("Added char:");
    //Serial.println(yeet[i][j]);
    
  }

  file.close();

  Serial.print("We got a file of length ");
  Serial.print(fancySize);
  //Serial.print(": ");
  //for (int ii = 0; ii < fancySize; ii++) {
  //  Serial.print(yeet[0][ii]);
  //  Serial.print(", ");
  //}
  Serial.println();
  
}

size_t readField(char* str2, size_t size, char* delim) {
  char ch;
  size_t n = 0;
  while ((n + 1) < size && file.available()) {
    ch = file.read();
    // Delete CR.
    if (ch == '\r' || ch == ' ' || ch == 0) {
      continue;
    }
    str2[n++] = ch;
    if (strchr(delim, ch)) {
        break;
    }
  }
  str2[n] = '\0';
  return n;
}

String getYeetSong(int superFancyNumber) {
  return fileNames[superFancyNumber];
}

void binaryTime() { //Taken straight from my watch

  int s = sec;
  int m = minutes;
  int h = hour;
  int r = 0;
  int g = 0;
  int b = 0;
  FastLED.clear();
  int i = 0;

  while (i < 6)
  {
    r = 0;
    g = 0;
    b = 0;
    if (binaryCheck(h, i) == 1)
    {
      b += 255;
    }
    if (binaryCheck(s, i) == 1)
    {
      r += 255;
    }
    if (binaryCheck(m, i) == 1)
    {
      g += 255;
    }

    if (r>255) r=255;
    if (g>255) g=255;
    if (b>255) b=255;
    if (posa) SetPixelColor(i, 0, 0, b);
    SetPixelColor((NUMPIXELS - 1 - i), 0, g, 0);
    if (!posa) SetPixelColor(i, r, 0, b);
    i++;

  }
  
  FastLED.show();
}

int binaryCheck(int n, int i) { //Taken straight from my watch, litterally forgot how it works
  int result = 0;
  i = pow(2, i);

  if ((n & i) != 0) //Ok i remember now, pretty simple
  {
    result = 1;
  }

  return result;
}
void timeStuff() {
  
  sec = (millis()/1000)%60;
  minutes = (millis()/60000)%60 + minuteMod;
  hour = ((millis()/3600000) + hourMod) % 12;
  
                                   //REEEEEEEEEEEEEEEEEEEEEEEEE Idiodic Stuffz
     
      while (minutes >= 60) {
        //yield();
        minutes -= 60;
        hour++;
      }/* 
      if ((month < 3 || month > 11) || (month == 3 && day < 10) || (month == 11 && day > 3)) { //Daylight savings, nobody likes you
        hour-=1;
      }
      hour %= 12;
      */
}

void lightStuffs() {
  if (lights) {
    switch (lightMode) {
      case 0:
        rainbow();
        break;
      case 1:
        for (int i = 0; i < NUMPIXELS; i++) {
          //yield();
          SetPixelColor(i, 255, 255, 255);
        }
        
        FastLED.show();
        break;
      case 2:
        binaryTime();
        break;
      case 3: //Epilepsy
      {
        FastLED.clear();
        int rr = 0;
        int rg = 0;
        int rb = 0;
        if (random(0, 2) == 0) {
          rr = random(0, 255);
          rg = random(0, 255);
          rb = random(0, 255);
        }
        for (int i = 0; i < NUMPIXELS; i++) {
          //yield();
          SetPixelColor(i, rr, rg, rb);
        }
        FastLED.show();
      }
        break;
        
      case 4: //Disco
        for (int i = 0; i < NUMPIXELS; i++) {
          //yield();
          SetPixelColor(i, random(0, 255), random(0, 255), random(0, 255));
        }
        FastLED.show();
        break;
      case 5: //Solid Color
        for (int i = 0; i < NUMPIXELS; i++) {
          //yield();
          SetPixelColor(i, storedColors[0], storedColors[1], storedColors[2]);
        }
        FastLED.show();
        break;
      case 6: //Fag
        theBestFlag();
        break;
      case 7: //Audio Spectrum (code elsewhere)
        break;
    }
  }
}
int flagPos = 15;
void theBestFlag() {
  FastLED.clear();
  for (int i = 0; i < 3; i++) {
    if (flagPos+i < 15 && flagPos+i >= 0) SetPixelColor(flagPos+i, storedColors[0], storedColors[1], storedColors[2]);
  }
  for (int i = 0; i < 3; i++) {
    if (flagPos+i+3 < 15 && flagPos+i+3 >= 0) SetPixelColor(flagPos+i+3, storedColors[3], storedColors[4], storedColors[5]);
  }
  for (int i = 0; i < 3; i++) {
    if (flagPos+i+6 < 15 && flagPos+i+6 >= 0) SetPixelColor(flagPos+i+6, storedColors[6], storedColors[7], storedColors[8]);
  }
  flagPos--;
  if (flagPos <= -15) {
    flagPos = 15;
  }
  FastLED.show();
}

//Variables for decomPlay
int freq1 = 0; //Frequency to be played
int dur1 = 0; //Duration to be played
int repFreq1 = -1; 
int repDur1 = -1;
int fin = 0; //Treble frequency index
int din = 0; //Treble duration index
boolean decodedTreble = false;

void decomPlay() {
  int temp;
  
  if (decodedTreble == false && fin < fancySize) {
    if (repFreq1 == 0) {
      repFreq1 = -1;
      fin++;
      Serial.println("Stopped Repeating");
    }
    
    Serial.print("repFreq1 = ");
    Serial.println(repFreq1);
    if (repFreq1 < 1) {
      temp = tableValue(yeet[0][fin]);
      Serial.print("temp = ");
      Serial.println(temp);
     
      
      if (temp >= 0) {
        freq1 = temp;
        fin++;
      } else {
        repFreq1 = abs(temp)-1;
      }
    }
    if (repDur1 == 0) {
      repDur1 = -1;
      din++;
    }
    if (repDur1 < 1) {
      temp = 0;
      temp = tableValue(yeet[1][din]);
      
      Serial.print("durtemp = ");
      Serial.println(temp);
      if (temp >= 0) {
        dur1 = temp;
        din++;
      } else {
        repDur1 = abs(temp)-1;
      }
    }
    decodedTreble = true;
  }
  if (fin < fancySize) {
    yeetNoteTreble(freq1, max((int)(dur1*tmod), 1));
  }
}

//Variables for decomPlayBase
int freq1b = 0; //Frequency to be played
int dur1b = 0; //Duration to be played
int repFreq1b = -1; 
int repDur1b = -1;
int finb = 0; //Treble frequency index
int dinb = 0; //Treble duration index
boolean decodedBase = false;

void decomPlayBase() {
  int temp;
  if ((repeat || shuffle) && fin >= fancySize && finb >= fancySizeBase && millis()%1000<100) { //Yeeeeticus Reeeepeticus
    freq1 = 0; 
    dur1 = 0; 
    repFreq1 = -1; 
    repDur1 = -1;
    fin = 0; 
    din = 0; 
    decodedTreble = false;
    
    freq1b = 0; 
    dur1b = 0; 
    repFreq1b = -1; 
    repDur1b = -1;
    finb = 0; 
    dinb = 0; 
    decodedBase = false;
    if (shuffle) {
      if (repeat)
        setSong(random(0, songCount));
      else {
        shufSelect();
      }
    }
  }
  if (decodedBase == false  && finb < fancySizeBase) {
    if (repFreq1b == 0) {
      repFreq1b = -1;
      finb++;
    }
    
    Serial.print("repFreq1b = ");
    Serial.println(repFreq1b);
    if (repFreq1b < 1) {
      temp = tableValue(yeet[2][finb]);
      Serial.print("tempb = ");
      Serial.println(temp);
     
      
      if (temp >= 0) {
        freq1b = temp;
        finb++;
      } else {
        repFreq1b = abs(temp)-1;
      }
    }
    if (repDur1b == 0) {
      repDur1b = -1;
      dinb++;
    }
    if (repDur1b < 1) {
      temp = tableValue(yeet[3][dinb]);
      
      Serial.print("reptempb = ");
      Serial.println(temp);
      if (temp >= 0) {
        dur1b = temp;
        dinb++;
      } else {
        repDur1b = abs(temp)-1;
      }
    }
    decodedBase = true;
  }
  if (finb < fancySizeBase) {
    yeetNoteBase(freq1b*2, max((int)(dur1b*tmod), 1));
  }
}

int tableValue(char fancyChar) {
    if (songNumber < 21)
      return table[(int)fancyChar];
    else if (songNumber < 33)
      return table2[(int)fancyChar];
    else if (songNumber < 47)
      return table3[(int)fancyChar];
    else if (songNumber < 65)
      return table4[(int)fancyChar];
    else if (songNumber < 82)
      return table5[(int)fancyChar];
    else
      return table6[(int)fancyChar];
}


void yeetNoteTreble(int freq, int dur) {
  //dur *= tmod;
  
  if (songNumber == 6) {
    dur = (int)(dur*0.994011976+0.5);
  }
  else if (songNumber == 7) {
    freq *= 2;
    dur = (int)(dur*0.9803921569+0.5);
  }
  else if (songNumber == 21) {
    dur = (int)(dur*0.9940828402+0.5);
  }
  else if (songNumber == 22) {
    dur = (int)(dur*0.9638554217+0.5);
  }
  else if (songNumber == 36) {
    dur = (int)(dur*1.0060240964+0.5);
  } 
  else if (songNumber == 42) {
    dur = (int)(dur*0.9912280702+0.5);
  }
  else if (songNumber == 62) {
    dur = (int)(dur*0.9945652174+0.5);
  }
  else if (songNumber == 67) {
    freq *= 2;
    dur = (int)(dur*0.9947089947+0.5);
  }
  else if (songNumber == 69) {
    dur = (int)(dur*0.9920634921+0.5);
  }
  else if (songNumber == 75) {
    dur = (int)(dur*1.008064516+0.5);
  }
  if (trebleTime == 0 || millis() - trebleStamp >= trebleTime) {  
    decodedTreble = false;
    trebleStamp = millis();
    trebleTime = dur;
    if (freq > 0) {
      tone(buzzer1, freq, max((int)(dur*yeetDur), 1), 0, 0);
    }
    /*Serial.println();
    //Serial.print("Free Memory = ");
    //Serial.print(freeMemory());
    Serial.print(" Treble Playing: ");
    Serial.print(freq);
    Serial.print(" for ");
    Serial.print(dur);
    Serial.print(" tin = ");
    Serial.println(tin);*/
    tin++;
    if (repFreq1 > 0) {
      repFreq1--;
    }
    if (repDur1 > 0) {
      repDur1--;
    }
    if (lightMode == 7) {
      onTheSpectrum(true);
    }
  }
}

void yeetNoteBase(int freqb, int dur) {
  //dur *= tmod;
  
  if (songNumber == 7 || songNumber == 67) {
    freqb *=2;
  }
  else if (songNumber == 38) {
    dur = (int)(dur*1.0909090909+0.5);
  }
  else if (songNumber == 40) {
    dur = (int)(dur*2.3640661939+0.5);
  }
  else if (songNumber == 41) {
    dur = (int)(dur*0.9911504425+0.5);
  }
  else if (songNumber == 43) {
    dur = (int)(dur*0.9941860465+0.5);
  } 
  else if (songNumber == 51) {
    dur = (int)(dur*0.992481203+0.5);
  }
  else if (songNumber == 54) {
    dur = (int)(dur*0.9923076923+0.5);
  }
  else if (songNumber == 57) {
    dur = (int)(dur*0.996875+0.5);
  }
  else if (songNumber == 59) {
    freqb = (int)(freqb*0.25f + 0.5);
  } else if (songNumber == 64) {
    dur = (int)(dur*0.9928057554+0.5);
  }
  if (baseTime == 0 || millis() - baseStamp >= baseTime) {
    decodedBase = false;
    baseStamp = millis();
    baseTime = dur;
    if (freqb > 0) {
      tone(buzzer2, freqb, max((int)(dur*yeetDur), 1), 1, 1);
    }
    /*Serial.println();
    Serial.print("Base Playing: ");
    Serial.print(freqb);
    Serial.print(" for ");
    Serial.println(dur);*/
    bin++;
    if (repFreq1b > 0) {
      repFreq1b--;
    }
    if (repDur1b > 0) {
      repDur1b--;
    }
    if (lightMode == 7) {
      onTheSpectrum(false);
    }
  }
  
}
//Ccclears from a to b, inclusive on both sides cause we live in a society
void ccclear(int a, int b) { // [a, b]
  for (int i = a; i <= b; i++) {
    SetPixelColor(i, 0, 0, 0);
  }
}

int getColor(int i, int c) { //i = color index, c = rgb value (c=0-->red, c=1-->green, c=2-->blue)
  return storedColors[3*i+c];
}

// Just a fair warning, I wrote this method while watching Rick and Morty Season 4 Episode 1
void onTheSpectrum(boolean pestControl) { //freq1 = treble, freq1b = base

  int abrahamanito = freq1/78; //Yes yes yyiieeeesss
  int benbenbenben = freq1%128; //Cool benben stones
  int siJamaisJOublieLesNuitsQueJaiPasseesLesGuitaresElectriquesRappelleMoiQuiJeSuisPourquoiJeSuisEnVieSiJamaisJOublieLesJambeAMonCouSiUnJourJeFuisRappelleMoiQuiJeSuisCeQueJMEtaisPromis = freq1b/78;
  int niceOneLobsterRick = freq1b%128;
  //FastLED.clear(); //YEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEET
  int i = 0; //Ok we saaaaaaaaane
  int r = 0, g = 0, b = 0; //two lines cause why the heck not
  boolean yeeticus;
  if (pestControl) {
    ccclear(0, 6);
  while (i < 7) { //EEEEEPIIIIIC
    yeeticus = false;
    r = 0; g = 0; b = 0; //YA ITS ONE LINE!!! DEAL WITH IT!!!
    if (binaryCheck(abrahamanito, i) == 1) {
      r+=getColor(0, 0);
      g+=getColor(0, 1);
      b+=getColor(0, 2);
    }
    if (binaryCheck(benbenbenben, i) == 1) {
      r+=getColor(1, 0);
      g+=getColor(1, 1);
      b+=getColor(1, 2);
    }
    

    if (yeeticus) {
      // Oh boi, its time to gggegegegegegeget some randomness!
      r += random(-21, 21); //42 is the answer to life, the universe, and everything
      g += random(-21, 21); //Does that mean 21 is just "life" and "univ"? or is it "li-univ-every"? or what about "fe-erse-thing"? Aha! Fierce Thing!
      b += random(-21, 21); //Wait what?, 21 - -21 = 42? Conspiracy?
    }
    r = max(0, min(255, r)); // According to Mr. Shelby: "The 'min' method is very good at setting max values, and vice versa"
    g = max(0, min(255, g));
    b = max(0, min(255, b));
    SetPixelColor(i, r, g, b);
    i++; //Lol, i forgot this originally
  }
  } else {
    ccclear(7, 14);
  while (i < 7) {
    yeeticus = false;
    r = 0; g = 0; 
    b = 0; //YA ITS TWO LINES NOW!!! DEAL WITH IT!!!
    
    //No i did not copy paste this name, I retyped it from memory
    if (binaryCheck(siJamaisJOublieLesNuitsQueJaiPasseesLesGuitaresElectriquesRappelleMoiQuiJeSuisPourquoiJeSuisEnVieSiJamaisJOublieLesJambeAMonCouSiUnJourJeFuisRappelleMoiQuiJeSuisCeQueJMEtaisPromis, i) == 1) {
      r+=getColor(2, 0);
      g+=getColor(2, 1);
      b+=getColor(2, 2);
    }
    //Ok fine, i did copy paste it
    //I shoulda done butcher pete
    
    if (binaryCheck(niceOneLobsterRick, i) == 1) {
      r+=getColor(3, 0);
      g+=getColor(3, 1);
      b+=getColor(3, 2);
    }

    if (yeeticus) {//Pete and Reeeeeeeeeeeeepeat are one a boat!!!!! Such idiots, shoulda taken a SPACESHIP SPACESHIP SPACESHIP SPACESHIP SPACESHIP!!!
      // Oh boi, its time to gggegegegegegeget some randomness!
      r += random(-21, 21); //42 is the answer to life, the universe, and everything
      g += random(-21, 21); //Does that mean 21 is just "life" and "univ"? or is it "li-univ-every"? or what about "fe-erse-thing"? Aha! Fierce Thing!
      b += random(-21, 21); //Wait what?, 21 - -21 = 42? Conspiracy?
    }

    r = max(0, min(255, r)); // According to Mr. Shelby: "The 'min' method is very good at setting max values, and vice versa"
    g = max(0, min(255, g));
    b = max(0, min(255, b));

    SetPixelColor(NUMPIXELS-1-i, r, g, b); //YEEETICUS
    i++;
  }
  }
  FastLED.show();
}

void tone(uint8_t pin, unsigned int frequency, unsigned long duration, uint8_t channel, unsigned int yeeter)
{   
  if (channel == 0) {
    channel = 1;
  } else if (channel == 1) {
    channel = 9;
  }
    if (ledcRead(channel)) {
        log_e("Tone channel %d is already in use", ledcRead(channel));
        Serial.println("REEEEEEEEEEE");
        return;
    }

    Serial.println();
    Serial.print("Channel ");
    Serial.print(channel);
    Serial.print(" playing at ");
    Serial.print(frequency);
    Serial.print(" for ");
    Serial.print(duration);
    Serial.println(" ms");
    ledcWriteTone(channel, frequency); 
    if (duration) {
      if (yeeter == 0) {
         timer = timerBegin(0, 80, true);
         timerAttachInterrupt(timer, &onTimer, true);
         timerAlarmWrite(timer, 1000*duration, false);
         timerAlarmEnable(timer);
         pin1 = pin;
         channel1 = channel;
      }
      else if (yeeter == 1) {
         timer2 = timerBegin(1, 80, true);
         timerAttachInterrupt(timer2, &onTimer2, true);
         timerAlarmWrite(timer2, 1000*duration, false);
         timerAlarmEnable(timer2);
         pin2 = pin;
         channel2 = channel;
      }
    }   
    //yield();
}

void IRAM_ATTR noTone(uint8_t pin, uint8_t channel)
{
    //ledcDetachPin(pin);
    ledcWrite(channel, 0);
}

String MACadd = "AA:BB:CC:11:22:33";      // I was told that I needed both of these lines???????
uint8_t address[6]  = {0xAA, 0xBB, 0xCC, 0x11, 0x22, 0x33};

void fancyInputStuffs() {
  if (SerialBT.available()) {
    String input = "";
    while (SerialBT.available()) {
      input += (char)SerialBT.read();
      //yield();
    }
    input.trim();
    Serial.print("Input = ");
    Serial.println(input);
    //uint8_t *buf;
    
    if (input.equals("?") || input.equals("help")) {
      SerialBT.println("Commands:\nbright# -- sets the brightness (# is a percent)\nplay --> plays the current song\nstop --> stops all music\np --> toggles pause\nsongs --> lists all available songs\nsn# --> substitute the desired song number for '#', it will switch to the song of that number\nrwd --> rewinds the song\nl# --> sets the light mode\nlm --> lists the light modes\nlights --> toggles lights on/off\nls# --> sets speed of lights\ntime#:# --> sets the time\nposa --> activites power saver mode (time is displayed, LEDs updated every few seconds)\ngetTime --> returns the current time\nc#:r,g,b --> store an rgb value\nlsc --> list stored colors\nrep --> toggle repeat\nshuf --> toggle shuffle\nrand --> plays a random song\nnew --> lists all the new features\nvo# --> set volume to #\noms# <device 1> <device 2>--> initiates orchestra mode, device names must be surrounded by < >, just like in HTML, # should be substituted with the song number (only for master)");
    }
    else if (input.equals("new")) {
      SerialBT.println(newFeatures);
    }
    else if (input.equals("rand")) {
      SerialBT.println("Playing a random song");
      shufSelect();
    }
    else if (input.equals("rep")) {
      repeat = !repeat;
      SerialBT.print("repeat = ");
      SerialBT.println(repeat);
    }
    else if (input.equals("shuf")) {
      shuffle = !shuffle;
      SerialBT.print("shuffle = ");
      SerialBT.println(shuffle);
    }
    else if (input.equals("stop")) {
      SerialBT.println("Stopping Music");
      playing = false;
    }
    else if (input.equals("play")) {
      SerialBT.println("Starting/Resuming Music");
      playing = true;
    }
    else if (input.equals("p")) {
      playing = !playing;
      SerialBT.print("Play Music = ");
      SerialBT.println(playing);// -775   -983
      SerialBT.println(millis()+millisMod); // 24112464 24113239   24173835 24174818
    }
    else if (input.substring(0, 4).equals("schp")) {
      SerialBT.print("Playing soon");
      playAt = input.substring(4).toInt();
      
      timer3 = timerBegin(0, 80, true);
      timerAttachInterrupt(timer3, &onTimer3, true);
      timerAlarmWrite(timer3, (playAt-millis()-millisMod)*1000, false);
      timerAlarmEnable(timer3);
    }
    else if (input.equals("songs")) {
      SerialBT.println(songs);
    }
    else if (input.substring(0, 2).equals("sn")) {
      setSong(input.substring(2).toInt());
      
      SerialBT.print("Switched song number to ");
      SerialBT.println(songNumber);
    }
    else if (input.equals("rwd")) {
      setSong(songNumber);
    }
    else if (input.equals("lm")) {
      SerialBT.println("Light Modes:\n0) Rainbow\n1) Flashlight\n2) Time\n3) Epilepsy\n4) Disco\n5) Solid Color (uses color in slot 0)\n6) Flag (uses 3 stored colors)\n7) Audio Spectrum (uses 4 stored colors)");
    }
    else if (input.equals("lights")) {
      lights = !lights;
      if (lights) {
        FastLED.setBrightness(brightness);
      }
      else {
        FastLED.setBrightness(0);
      }
      FastLED.clear();
      
      FastLED.show();
      SerialBT.print("Lights = ");
      SerialBT.println(lights);
    }
    else if (input.substring(0, 6).equals("bright")) {
      brightness = max( min((int)input.substring(6).toInt(), 100), 0 ); //brightness must be inbetween 0 and 100
      FastLED.setBrightness(brightness);
      SerialBT.print("brightness = ");
      SerialBT.println(brightness);
    }
    else if (input.equals("posa")) {
      posa = !posa;
      if (posa) {
        FastLED.setBrightness(brightness/10);
      } else {
        FastLED.setBrightness(brightness);
      }
      SerialBT.print("power saver = ");
      SerialBT.println(posa);
    }
    else if (input.equals("gettime") || input.equals("getTime")) {
      SerialBT.print("hour = ");
      SerialBT.print(hour);
      SerialBT.print(" minutes = ");
      SerialBT.println(minutes);
    }
    else if (input.equals("lsc")) {
      SerialBT.println("Stored Colors");
      for (int i = 0; i < 4; i++) {
        SerialBT.print(storedColors[i*3]);
        SerialBT.print(", ");
        SerialBT.print(storedColors[i*3+1]);
        SerialBT.print(", ");
        SerialBT.println(storedColors[i*3+2]);
      }
    }
    else if (input.substring(0, 4).equals("time")) {
      hourMod = input.substring(4, input.indexOf(':')).toInt() - hour;
      minuteMod = input.substring(input.indexOf(':')+1).toInt() - minutes;
      SerialBT.print("hour = ");
      SerialBT.print(hour + hourMod);
      SerialBT.print(" minutes = ");
      SerialBT.println(minutes + minuteMod);
    }
    else if (input.equalsIgnoreCase("ha")) {
      holdAction = true;
      while (!SerialBT.available()) {
        delay(20);
      }
      input = "";
      while (SerialBT.available()) {
        input += (char)SerialBT.read();
        //yield();
      }
      input.trim();
      if (input.substring(0, 5).equals("etime")) {
        millisMod = input.substring(5).toInt() - millis() + mOffset;
        holdAction = false;
        Serial.println("yeet");
      }
      
    }
    else if (input.substring(0, 5).equals("etime")) {
      millisMod = input.substring(5).toInt() - millis() + mOffset;
      holdAction = false;
    }
    else if (input.substring(0, 2).equals("ls")) {
      lightSpeed = input.substring(2).toInt();
      SerialBT.print("lightSpeed = ");
      SerialBT.println(lightSpeed);
    }
    else if (input.charAt(0) == 'l') {
      lightMode = input.substring(1).toInt();
      SerialBT.print("lightMode = ");
      SerialBT.println(lightMode);
    }
    else if (input.charAt(0) == 'v' && input.charAt(1) == 'o') {
      int volume = input.substring(2).toInt();
      SerialBT.print("volume = ");
      SerialBT.println(volume);
      
    }
    else if (input.charAt(0) == 'c') { // c1:4,240,34
      int n = input.substring(1, 2).toInt();
      int r = input.substring(3, input.indexOf(',')).toInt();
      int g = input.substring(input.indexOf(',')+1, input.indexOf(input.indexOf(',')+1, ',')).toInt();
      int b = input.substring(input.lastIndexOf(',')+1).toInt();

      SerialBT.print("n = ");
      SerialBT.print(n);
      SerialBT.print(", r = ");
      SerialBT.print(r);
      SerialBT.print(", g = ");
      SerialBT.print(g);
      SerialBT.print(", b = ");
      SerialBT.println(b);

      storedColors[n*3] = r;
      storedColors[n*3+1] = g;
      storedColors[n*3+2] = b;
      
    }
    //message looks like this (the 'c' can be any char between a, b, and c) --> ot#:c:#
    else if (input.substring(0,2).equals("ot") && input.length() > 3) {
      
    }
    //message looks like this --> oms# <device 1> <device 2>
    else if (input.substring(0,3).equals("oms") && input.length() > 4) {
      int a = input.indexOf('<');
      int b = input.indexOf('>', a+1);
      int c = input.indexOf('<', b+1);
      int d = input.indexOf('>', c+1);
      
      String device1 = input.substring(a+1, b); //gets the device names from the message
      String device2 = input.substring(c+1, d);
      
      Serial.println(2);
      int oSong = input.substring(3, a-1).toInt(); //gets the orchestra song number

      String message2 = "Trying to connect to " + device1 + " and " + device2;
      
      SerialBT.println(message2);
      
      delay(1000);
      SerialBT.end();
      delay(2000);
      SerialBT.begin("andrewRyan", true); //the 'true' means to start in master mode
      delay(2000);
      if (SerialBT.connect(device1)) { //connects to device1   ////// This crashes the ESP32, idk why, I have been testing with another board
        Serial.println("connected successfully");
      } else {
        while (!SerialBT.connected(10000)) {
          Serial.println("Trying to connect");
          delay(100);
          yield();
        }
        Serial.println("out of loop");
      }
      //ot0:b:12000
      String message = "ot";
      message += oSong;
      message += ":b:12000";
      SerialBT.print(message); //sends the trigger phrase
      long temp = millis(); //saves the time when the trigger phrase was sent

      if (SerialBT.disconnect()) {  //Disconnect from the device
        Serial.println("disconnected");
      }

      //  OK ITS TIME FOR DEVICE 2

      if (SerialBT.connect(device2)) { //connects to device1
        Serial.println("connected successfully");
      } else {
        while (!SerialBT.connected(10000)) {
          Serial.println("Trying to connect");
          delay(100);
          yield();
        }
        Serial.println("out of loop");
      }
      //ot0:b:12000
      message = "ot";
      message += oSong;
      message += ":c:0";

      delay(12000 - millis() + temp); //waits the delay-time
      SerialBT.print(message); //sends the trigger phrase

      if (SerialBT.disconnect()) {   //Disconnect from the device
        Serial.println("disconnected");
      }

      SerialBT.begin(btName);
      
    }
  }
}

void shufSelect() {
  hist[songNumber] = -1;
  int yeeticusFinch = random(0, songCount);
  int iiiii = 0;
  while (hist[yeeticusFinch] == -1) {
     yeeticusFinch = random(0, songCount);
     iiiii++;
     if (iiiii > songCount*0.7) {
        Serial.println("yeetin");
        for (int i = 0; i < songCount; i++) {
            hist[i] = i;
        }
     }
  }
  Serial.print("Playing: ");
  Serial.print(yeeticusFinch);
  Serial.print(" hist[yeeticusFinch]= ");
  Serial.println(hist[yeeticusFinch]);
  setSong(yeeticusFinch);
}

void setSong(int n) {
  fancySize = -1;
  fancySizeBase = -1;
  songNumber = n;
  hist[songNumber] = -1;
  tin = 0;
  bin = 0;
  trebleTime = 0;
  trebleStamp = 0;
  baseTime = 0;
  baseStamp = 0;
  compressed = true;
  compressedBase = true;
  //Serial.print(1);
  if (tempMelody != NULL) {
    free(tempMelody);
    tempMelody = NULL;
  }
  //Serial.print(2);
  if (tempRhythmn != NULL) {
    free(tempRhythmn);
    tempRhythmn = NULL;
  }
  //Serial.print(3);
  tempMelLength = 0;
  tempRhyLength = 0;
  //Serial.print(4);
  if (tempMelodyBase != NULL) {
    Serial.printf("%0x\n", tempMelodyBase);
    free(tempMelodyBase);
    tempMelodyBase = NULL;
  }
 // Serial.print(5);
  if (tempRhythmnBase != NULL) {
    free(tempRhythmnBase);
    tempRhythmnBase = NULL;
  }
  //Serial.print(6);
  tempMelLengthBase = 0;
  tempRhyLengthBase = 0;

  freq1 = 0; //Frequency to be played
  dur1 = 0; //Duration to be played
  repFreq1 = -1; 
  repDur1 = -1;
  fin = 0; //Treble frequency index
  din = 0; //Treble duration index
  decodedTreble = false;
  freq1b = 0; //Frequency to be played
  dur1b = 0; //Duration to be played
  repFreq1b = -1; 
  repDur1b = -1;
  finb = 0; //Treble frequency index
  dinb = 0; //Treble duration index
  decodedBase = false;

  //All these numbers were derived through tedious trial and error
  if (songNumber == 0) {
    tmod = 0.2f;
    yeetDur = 0.5f;
  } else if (songNumber == 1) {
    tmod = 0.2f;
    yeetDur = 0.9f;
  } else if (songNumber == 2) {
    tmod = 0.2f;
    yeetDur = 0.5f;
  } else if (songNumber == 3) {
    tmod = 0.1f;
    yeetDur = 0.5f;
  } else if (songNumber == 4) {
    tmod = 0.2f;
    yeetDur = 0.5f;
  } else if (songNumber == 5) {
    tmod = 0.25f;
    yeetDur = 0.9f;
  } else if (songNumber == 6) {
    tmod = 0.8f;
    yeetDur = 0.7f;
  } else if (songNumber == 7) {
    tmod = 0.5f;
    yeetDur = 0.7f;
  } else if (songNumber == 8) {
    tmod = 0.8f;
    yeetDur = 0.9f;
  } else if (songNumber == 9) {
    tmod = 0.6f;
    yeetDur = 0.5f;
  } else if (songNumber == 10) {
    tmod = 0.4f;
    yeetDur = 0.3f;
  } else if (songNumber == 11) {
    tmod = 0.8f;
    yeetDur = 0.6f;
  } else if (songNumber == 12) {
    tmod = 0.8f;
    yeetDur = 0.8f;
  } else if (songNumber == 13) {
    tmod = 0.65f;
    yeetDur = 0.8f;
  } else if (songNumber == 14) {
    tmod = 0.87f;
    yeetDur = 0.5f;
  } else if (songNumber == 15) {
    tmod = 0.4f;
    yeetDur = 0.6f;
  } else if (songNumber == 16) {
    tmod = 0.8f;
    yeetDur = 0.6f;
  } else if (songNumber == 17) {
    tmod = 0.8f;
    yeetDur = 0.6f;
  } else if (songNumber == 18) {
    tmod = 0.7f;
    yeetDur = 0.6f;
  } else if (songNumber == 19) {
    tmod = 0.8f;
    yeetDur = 0.6f;
  } else if (songNumber == 20) {
    tmod = 0.86f;
    yeetDur = 0.6f;
  } else if (songNumber == 21) {
    tmod = 0.8f;
    yeetDur = 0.6f;
  } else if (songNumber == 22) {
    tmod = 0.4f;
    yeetDur = 0.8f;
  } else if (songNumber == 23) {
    tmod = 0.8f;
    yeetDur = 0.8f;
  } else if (songNumber == 24) {
    tmod = 0.6f;
    yeetDur = 0.5f;
  } else if (songNumber == 25) {
    tmod = 0.8f;
    yeetDur = 0.6f;
  } else if (songNumber == 26) {
    tmod = 0.8f;
    yeetDur = 0.8f;
  } else if (songNumber == 27) {
    tmod = 0.84f;
    yeetDur = 0.65f;
  } else if (songNumber == 28) {
    tmod = 0.55f;
    yeetDur = 0.7f;
  } else if (songNumber == 29) {
    tmod = 0.85f;
    yeetDur = 0.6f;
  } else if (songNumber == 30) {
    tmod = 0.5f;
    yeetDur = 0.7f;
  } else if (songNumber == 31) {
    tmod = 0.8f;
    yeetDur = 0.6f;
  } else if (songNumber == 32) {
    tmod = 0.2f;
    yeetDur = 0.6f;
  } else if (songNumber == 33) {
    tmod = 0.6f;
    yeetDur = 0.6f;
  } else if (songNumber == 34) {
    tmod = 0.6f;
    yeetDur = 0.6f;
  } else if (songNumber == 35) {
    tmod = 0.6f;
    yeetDur = 0.6f;
  } else if (songNumber == 36) {
    tmod = 0.2f;
    yeetDur = 0.6f;
  } else if (songNumber == 37) {
    tmod = 0.7f;
    yeetDur = 0.5f;
  } else if (songNumber == 38) {
    tmod = 0.7f;
    yeetDur = 0.65f;
  } else if (songNumber == 39) {
    tmod = 0.7f;
    yeetDur = 0.4f;
  } else if (songNumber == 40) {
    tmod = 0.3f;
    yeetDur = 0.7f;
  } else if (songNumber == 41) {
    tmod = 0.9f;
    yeetDur = 0.6f;
  } else if (songNumber == 42) {
    tmod = 0.9f;
    yeetDur = 0.6f;
  } else if (songNumber == 43) {
    tmod = 0.9f;
    yeetDur = 0.5f;
  } else if (songNumber == 44) {
    tmod = 0.27f;
    yeetDur = 0.5f;
  } else if (songNumber == 45) {
    tmod = 0.24f;
    yeetDur = 0.7f;
  } else if (songNumber == 46) {
    tmod = 0.9f;
    yeetDur = 0.6f;
  } else if (songNumber == 47) {
    tmod = 0.9f;
    yeetDur = 0.6f;
  } else if (songNumber == 48) {
    tmod = 0.8f;
    yeetDur = 0.6f;
  } else if (songNumber == 49) {
    tmod = 0.85f;
    yeetDur = 0.6f;
  } else if (songNumber == 50) {
    tmod = 0.25f;
    yeetDur = 0.6f;
  } else if (songNumber == 51) {
    tmod = 0.84f;
    yeetDur = 0.4f;
  } else if (songNumber == 52) {
    tmod = 1;
    yeetDur = 0.65f;
  } else if (songNumber == 53) {
    tmod = 0.87f;
    yeetDur = 0.7f;
  } else if (songNumber == 54) {
    tmod = 0.8f;
    yeetDur = 0.8f;
  } else if (songNumber == 55) {
    tmod = 0.7f;
    yeetDur = 0.5f;
  } else if (songNumber == 56) {
    tmod = 0.2f;
    yeetDur = 0.75f;
  } else if (songNumber == 57) {
    tmod = 0.9f;
    yeetDur = 0.9f;
  } else if (songNumber == 58) {
    tmod = 0.85f;
    yeetDur = 0.6f;
  } else if (songNumber == 59) {
    tmod = 0.85f;
    yeetDur = 0.6f;
  } else if (songNumber == 60) {
    tmod = 0.5f;
    yeetDur = 0.6f;
  } else if (songNumber == 61) {
    tmod = 0.9f;
    yeetDur = 0.6f;
  } else if (songNumber == 62) {
    tmod = 0.6f; 
    yeetDur = 0.76f;
  } else if (songNumber == 63) {
    tmod = 0.75f; 
    yeetDur = 0.65f;
  } else if (songNumber == 64) {
    tmod = 0.75f; 
    yeetDur = 0.7f;
  } else if (songNumber == 65) {
    tmod = 0.3f; 
    yeetDur = 0.5f;
  } else if (songNumber == 66) {
    tmod = 0.3f; 
    yeetDur = 0.8f; 
  } else if (songNumber == 67) {
    tmod = 0.7f; 
    yeetDur = 0.6f; 
  } else if (songNumber == 68) {
    tmod = 0.7f; 
    yeetDur = 0.75f; 
  } else if (songNumber == 69) {
    tmod = 0.7f; 
    yeetDur = 0.8f; 
  } else if (songNumber == 70) {
    tmod = 0.6f; 
    yeetDur = 0.7f; 
  } else if (songNumber == 71) {
    tmod = 0.9f;
    yeetDur = 0.6f;
  } else if (songNumber == 72) {
    tmod = 0.9f;
    yeetDur = 0.6f;
  } else if (songNumber == 73 || songNumber == 74) {
    tmod = 0.8f;
    yeetDur = 0.6f;
  } else if (songNumber == 75) {
    tmod = 0.95f;
    yeetDur = 0.65f;
  } else if (songNumber == 76 || songNumber == 77 || songNumber == 78) {
    tmod = 0.3f; 
    yeetDur = 0.5f;
  } else if (songNumber == 79 || songNumber == 80 || songNumber == 81) {
    tmod = 0.7f; 
    yeetDur = 0.8f; 
  } else if (songNumber == 82) {
    tmod = 0.18f;
    yeetDur = 0.65f;
  } else if (songNumber == 83) {
    tmod = 0.25f;
    yeetDur = 0.65f;
  } else if (songNumber == 84 || songNumber == 85) {
    tmod = 0.75f;
    yeetDur = 0.65f;
  } else if (songNumber == 86) {
    tmod = 0.2f;
    yeetDur = 0.65f;
  } else if (songNumber == 87 || songNumber == 88 || songNumber == 89) {
    tmod = 0.8f;
    yeetDur = 0.7f;
  } else if (songNumber == 90 || songNumber == 91 || songNumber == 92) {
    tmod = 0.25f;
    yeetDur = 0.6f;
  } else if (songNumber == 93) {
    tmod = 0.6f;
    yeetDur = 0.8f;
  } else if (songNumber == 94 || songNumber == 95) {
    tmod = 0.66f;
    yeetDur = 0.6f;
  } 
  
  
}

void SetPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  leds[n].r = r;
  leds[n].g = g;
  leds[n].b = b;
}

void rainbow() {
  for (int i = 0; i < NUMPIXELS; i++) {
    
      Wheel(i, (i*1+(jj[i])) & 255); //Array jj is just to stagger the LEDs, no udea why i ham multiplying by 1
      jj[i]++; 
      jj[i]%=256;
      yield();
  }
  
  FastLED.show();
  
}

void Wheel(int i, byte WheelPos) { //SetPixelColor(index, r, g, b)
  if(WheelPos < 85) {
    SetPixelColor(i, WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    SetPixelColor(i, 255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    SetPixelColor(i, 0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

uint32_t color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
