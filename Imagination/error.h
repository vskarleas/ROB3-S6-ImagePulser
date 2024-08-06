// #############################################################################
// # File error.h
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file error.h
 * @brief UINT et FATAL_ERROR déclaration
 *
 */
 
#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdio.h>
#include <stdlib.h>

/* type entier positif */
typedef unsigned int UINT;

/**
 * @brief macro affichant le message _m_ et s'arretant
 * 
 */
#define FATAL_ERROR(_m_) \
{ \
fprintf(stderr, "%s\n", _m_); \
exit(1); \
}

#endif
