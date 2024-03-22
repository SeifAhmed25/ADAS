/*
 * PRIVATEh.h
 *
 * Created: 3/20/2024 2:08:37 PM
 *  Author: seif
 */ 


#ifndef PRIVATEH_H_
#define PRIVATEH_H_

#define EEARH *(volatile u8*)(0x3F)
#define EEARL *(volatile u8*)(0x3E)

#define EEDR *(volatile u8*)(0x3D)
#define EECR *(volatile u8*)(0x3C)

#define EERE 0
#define EEWE 1
#define EEMWE 2
#define EERIE 3

#endif /* PRIVATEH_H_ */