#ifndef ROBOTSYSVARS_H
#define ROBOTSYSVARS_H

#define SETSYSVAR(location, name) const int name = location

//
//robot system locations constant integers
//
const int dirup = 1;
const int dirdn = 2;
const int dirright = 3;
const int dirleft = 4;
const int aimright = 5;
const int aimleft = 6;
const int shoot = 7;
const int shootval = 8;
const int backshot = 9;
const int aimshoot = 10;

const int robage = 14;
const int masssys = 15;
const int maxvelsys = 16;
const int timersys = 17;
const int Aimsys = 18;
const int SetAim = 19;

const int bodgain = 194;
const int bodloss = 195;
const int velscalar = 196;
const int velsx = 197;
const int veldx = 198;
const int veldn = 199;
const int velup = 200;
const int hit = 201;
const int shflav = 202;
const int pain = 203;
const int pleas = 204;

const int shangsys = 209;

const int edgesys = 214;
const int fixedsys = 215;
const int fixpos = 216;
const int daytime = 218;
const int xpos = 219;
const int ypos = 217;
const int Kills = 220;
const int HitAngsys = 221;
const int Repro = 300;
const int mrepro = 301;
const int sexrepro = 302;
const int energy = 310;
const int bodysys = 311;
const int fdbody = 312;
const int strbody = 313;
const int setboy = 314;
const int rdboy = 315;

const int mkvirus = 335;
const int DnaLenSys = 336;
const int Vtimer = 337;
const int VshootSys = 338;
const int GenesSys = 339;

const int thisgene = 341;
const int SUNsys = 400;

const int memval = 473;
const int memloc = 474;

const int reffixed = 477;

const int EyeStart = 501;
const int EyeMid = 505;
const int EyeEnd = 509;

const int mtie = 550;
const int deltie = 551;
const int currtiesys = 552;
const int readtielen = 553;
const int writetielen = 554;
const int tieangle = 555;
SETSYSVAR(556, numties);
SETSYSVAR(557, lastport);
SETSYSVAR(558, lastphase);

const int refmulti = 686;
const int refshell = 687;
const int refbody = 688;
const int refxpos = 689;
const int refypos = 690;
const int refvelscalar = 695;
const int refvelsx = 696;
const int refveldx = 697;
const int refveldn = 698;
const int refvelup = 699;
const int occurrstart = 700;
const int refaim = 711;
const int reftie = 712;
const int refpoison = 713;
const int refvenom = 714;
const int refkills = 715;
const int mystart = 721;
const int myend = 731;
const int out1 = 800;
const int out2 = 801;
const int out3 = 802;
const int out4 = 803;
const int out5 = 804;
const int out6 = 805;
const int out7 = 806;
const int out8 = 807;
const int out9 = 808;
const int out10= 809;
const int in1 = 810;
const int in2 = 811;
const int in3 = 812;
const int in4 = 813;
const int in5 = 814;
const int in6 = 815;
const int in7 = 816;
const int in8 = 817;
const int in9 = 818;
const int in10= 819;

const int mkslime = 820;
const int slimesys = 821;
const int mkshell = 822;
const int shellsys = 823;
const int mkvenom = 824;
const int venomsys = 825;
const int mkpoison = 826;
const int poison = 827;
const int wastesys = 828;
const int pwastesys = 829;
const int paralyzed = 837;
const int poisoned = 838;

#endif
