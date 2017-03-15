#include "util.h"

#ifndef __KEYDEF_H_
#define __KEYDEF_H_

/*
									======== Key Map ========

			<P26>	<P27>	<P10>	<P11>	<P12>	<P13>	<P14>	<P15>	<P16>	<P17>
			C0		C1		C2		C3		C4		C5		C6		C7		C8		C9

<P23>		1		2		3		4		5		6		7		8		9		0
	R0		q		w		e		r		t		y		u		i		o		p
	
<P22>		(		)		!		?		\		[		]		{		}
	R1		a		s		d		f		g		h		j		k		l
		
<P21>				/		+		-		=		*		'		"		.		esc
	R2		sht		z		x		c		v		b		n		m		,		bsp
	
<P20>	
	R3				ctl		alt				space	space			fun		ent

*/

#define PC0 P26
#define PC1 P27
#define PC2 P10
#define PC3 P11
#define PC4 P12
#define PC5 P13
#define PC6 P14
#define PC7 P15
#define PC8 P16
#define PC9 P17

#define PR0 P23
#define PR1 P22
#define PR2 P21
#define PR3 P20

enum Cols {
	C0 = 0, C1 = 1, C2 = 2, C3 = 3, C4 = 4,
	C5 = 5, C6 = 6, C7 = 7, C8 = 8, C9 = 9
};

enum Rows {
	R0 = 0, R1 = 1, R2 = 2, R3 = 3
};

static uint8_t keyCode[2][4][10] = {
	/*Normal*/
	/*16: sht, 8: bsp, 17: ctl, 18: alt, 13: ent, 0: null*/
	{
		{ 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p' },
		{ 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',  0  },
		{  16, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',',  8  },
		{  0 ,  17,  18,  0 , ' ', ' ',  0 , 255, '\n', 0  }
	},
	/*Alter*/
	/*27: esc, 7: fun*/
	{
		{ '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' },
		{ '(', ')', '!', '?','\\', '[', ']', '{', '}',  0  },
		{  0 , '/', '+', '-', '=', '*','\'','\"', '.', 27  },
		{  0 ,  17,  18,  0 , ' ', ' ',  0 ,  7 , '\n', 0  }
	}
};

uint8_t _scan(char row, char exc, bit alt) {
	P1 = 0xFF; P2 = 0xFF;
	_nop_(); _nop_(); _nop_(); _nop_();
	switch (row) {
		case R0: PR0 = 0; PR1 = 1; PR2 = 1; PR3 = 1; break;
		case R1: PR0 = 1; PR1 = 0; PR2 = 1; PR3 = 1; break;
		case R2: PR0 = 1; PR1 = 1; PR2 = 0; PR3 = 1; break;
		case R3: PR0 = 1; PR1 = 1; PR2 = 1; PR3 = 0; break;
		default: PR0 = 1; PR1 = 1; PR2 = 1; PR3 = 1; break;
	}
	delay(1);
	
#define __SCAN_(port, col) if (port == 0 && exc != keyCode[alt][row][col]) return keyCode[alt][row][col]
	
	__SCAN_(PC0, C0); __SCAN_(PC1, C1); __SCAN_(PC2, C2); __SCAN_(PC3, C3); __SCAN_(PC4, C4);
	__SCAN_(PC5, C5); __SCAN_(PC6, C6); __SCAN_(PC7, C7); __SCAN_(PC8, C8); __SCAN_(PC9, C9);
	
	return 0xFF;
}

uint8_t scanKey() {
	uint8_t tmp = 0;
	tmp = _scan(R3, 0, 0);
	if (tmp == 17) {
		/*ctl + ?*/
		tmp = _scan(R3, 17, 0);
		if (tmp == 18) {
			while (tmp == 18) tmp = _scan(R3, 17, 0);
			ALT_LCK = !ALT_LCK;
			SHT_LCK = 0;
			return 0xFF;
		}
		tmp = _scan(R2, 0, 0);
		if (tmp == 16) {
			while (tmp == 16) tmp = _scan(R2, 0, 0);
			SHT_LCK = !SHT_LCK;
			ALT_LCK = 0;
			return 0xFF;
		} else if (tmp != 0xFF) return tmp + 0x80;
		tmp = _scan(R1, 0, ALT_LCK);
		if (tmp != 0xFF) return tmp + 0x80;
		tmp = _scan(R0, 0, ALT_LCK);
		if (tmp != 0xFF) return tmp + 0x80;
		return 0xFF;
	} else if (tmp == 18) {
		/*alt + ?*/
		tmp = _scan(R2, 16, !ALT_LCK);
		if (tmp != 0xFF) return tmp;
		tmp = _scan(R1, 0, !ALT_LCK);
		if (tmp != 0xFF) return tmp;
		tmp = _scan(R0, 0, !ALT_LCK);
		if (tmp != 0xFF) return tmp;
		return 0xFF;
	} else if (tmp != 0xFF) return tmp;
	tmp = _scan(R2, 0, ALT_LCK);
	if (tmp == 16) {
		/*sht + ?*/
		tmp = _scan(R2, 16, ALT_LCK);
		if (tmp != 0xFF) return tmp - ((tmp >= 'a' && tmp <= 'z') ? 0x20 : 0);
		tmp = _scan(R1, 0, ALT_LCK);
		if (tmp != 0xFF) return tmp - ((tmp >= 'a' && tmp <= 'z') ? 0x20 : 0);
		tmp = _scan(R0, 0, ALT_LCK);
		if (tmp != 0xFF) return tmp - ((tmp >= 'a' && tmp <= 'z') ? 0x20 : 0);
		return 0xFF;
	} else if (tmp != 0xFF) return tmp - ((SHT_LCK && (tmp >= 'a' && tmp <= 'z')) ? 0x20 : 0);
	tmp = _scan(R1, 0, ALT_LCK);
	if (tmp != 0xFF) return tmp - ((SHT_LCK && (tmp >= 'a' && tmp <= 'z')) ? 0x20 : 0);
	tmp = _scan(R0, 0, ALT_LCK);
	if (tmp != 0xFF) return tmp - ((SHT_LCK && (tmp >= 'a' && tmp <= 'z')) ? 0x20 : 0);
	
	return 0xFF;
}

#endif