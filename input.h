/*
 * input.h
 *
 *  Created on: 05-11-2012
 *      Author: matfil
 */

#ifndef INPUT_H_
#define INPUT_H_


int exitfound (char inp[128]);
void printinput (char inp[128]);
int lettercheck (char inp[128]);
int rewrite (char inp[128],char out[16]);
void cutbraces (char inp[128]);
int jesttamkto (char inp[128]);
int buildmatrix (char inp[128], double matrix[10][10]);



#endif /* INPUT_H_ */
