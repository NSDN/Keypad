#include "util.h"

#ifndef __KEYDEF_H_
#define __KEYDEF_H_

typedef enum {
/*	P10			P11			P12			P13			P14			P15			P16			P17			P20				P21				P22				P23				P24					 */
	Key1 = '1',	Key2 = '2',	Key3 = '3',	Key4 = '4',	Key5 = '5',	Key6 = '6',	Key7 = '7',	Key8 = '8',	Key9 = '9',		Key0 = '0',		KeyMinus = '-',	KeyEqu = '=',	KeyBack = 8,	/*P33*/
	KeyTab = 9,	KeyQ = 'Q',	KeyW = 'W',	KeyE = 'E',	KeyR = 'R',	KeyT = 'T',	KeyY = 'Y',	KeyU = 'U',	KeyI = 'I',		KeyO = 'O',		KeyP = 'P',		KeyLB = '(',	KeyRB = ')',	/*P34*/
	KeyCL = 20,	KeyA = 'A',	KeyS = 'S',	KeyD = 'D',	KeyF = 'F',	KeyG = 'G',	KeyH = 'H',	KeyJ = 'J',	KeyK = 'K',		KeyL = 'L',		KeyMul = '*',	KeyPlus = '+',	KeyEnter = 10,	/*P35*/
	KeyUl ='_',	KeyZ = 'Z',	KeyX = 'X',	KeyC = 'C',	KeyV = 'V',	KeyB = 'B',	KeyN = 'N',	KeyM = 'M',	KeyCom = ',',	KeyPer = '.',	KeySla = '/',	KeyQuot = '\"',	KeyASla = '\\',	/*P36*/
	KeyCt = 17,	KeyAl = 18,				KeyEsc = 27,		  /*KeySp,*/	KeySp = 32,/*KeySp,*/				  /*KeyEsc,*/		  				/*KeyAl,		KeyCt*/			/*P37*/
	
} Key;

Key scanKey() {
	P3 |= 0xF8; P1 = 0xFF; P2 |= 0x1F;
	_nop_(); _nop_(); _nop_(); _nop_();
	P33 = 0; P34 = 1; P35 = 1; P36 = 1; P37 = 1;
	delay(1);
	if (P10 == 0) return Key1;
	if (P11 == 0) return Key2;
	if (P12 == 0) return Key3;
	if (P13 == 0) return Key4;
	if (P14 == 0) return Key5;
	if (P15 == 0) return Key6;
	if (P16 == 0) return Key7;
	if (P17 == 0) return Key8;
	if (P20 == 0) return Key9;
	if (P21 == 0) return Key0;
	if (P22 == 0) return KeyMinus;
	if (P23 == 0) return KeyEqu;
	if (P24 == 0) return KeyBack;
	
	P3 |= 0xF8; P1 = 0xFF; P2 |= 0x1F;
	_nop_(); _nop_(); _nop_(); _nop_();
	P33 = 1; P34 = 0; P35 = 1; P36 = 1; P37 = 1;
	delay(1);
	if (P10 == 0) return KeyTab;
	if (P11 == 0) return KeyQ;
	if (P12 == 0) return KeyW;
	if (P13 == 0) return KeyE;
	if (P14 == 0) return KeyR;
	if (P15 == 0) return KeyT;
	if (P16 == 0) return KeyY;
	if (P17 == 0) return KeyU;
	if (P20 == 0) return KeyI;
	if (P21 == 0) return KeyO;
	if (P22 == 0) return KeyP;
	if (P23 == 0) return KeyLB;
	if (P24 == 0) return KeyRB;
	
	P3 |= 0xF8; P1 = 0xFF; P2 |= 0x1F;
	_nop_(); _nop_(); _nop_(); _nop_();
	P33 = 1; P34 = 1; P35 = 0; P36 = 1; P37 = 1;
	delay(1);
	if (P10 == 0) return KeyCL;
	if (P11 == 0) return KeyA;
	if (P12 == 0) return KeyS;
	if (P13 == 0) return KeyD;
	if (P14 == 0) return KeyF;
	if (P15 == 0) return KeyG;
	if (P16 == 0) return KeyH;
	if (P17 == 0) return KeyJ;
	if (P20 == 0) return KeyK;
	if (P21 == 0) return KeyL;
	if (P22 == 0) return KeyMul;
	if (P23 == 0) return KeyPlus;
	if (P24 == 0) return KeyEnter;
	
	P3 |= 0xF8; P1 = 0xFF; P2 |= 0x1F;
	_nop_(); _nop_(); _nop_(); _nop_();
	P33 = 1; P34 = 1; P35 = 1; P36 = 0; P37 = 1;
	delay(1);
	if (P10 == 0) return KeyUl;
	if (P11 == 0) return KeyZ;
	if (P12 == 0) return KeyX;
	if (P13 == 0) return KeyC;
	if (P14 == 0) return KeyV;
	if (P15 == 0) return KeyB;
	if (P16 == 0) return KeyN;
	if (P17 == 0) return KeyM;
	if (P20 == 0) return KeyCom;
	if (P21 == 0) return KeyPer;
	if (P22 == 0) return KeySla;
	if (P23 == 0) return KeyQuot;
	if (P24 == 0) return KeyASla;
	
	P3 |= 0xF8; P1 = 0xFF; P2 |= 0x1F;
	_nop_(); _nop_(); _nop_(); _nop_();
	P33 = 1; P34 = 1; P35 = 1; P36 = 1; P37 = 0;
	delay(1);
	if (P10 == 0) return KeyCt;
	if (P11 == 0) return KeyAl;
	if (P13 == 0) return KeyEsc;
	if (P15 == 0) return KeySp;
	if (P16 == 0) return KeySp;
	if (P17 == 0) return KeySp;
	if (P21 == 0) return KeyEsc;
	if (P23 == 0) return KeyAl;
	if (P24 == 0) return KeyCt;
	
	return 0xFF;
}

#endif