#pragma once
#ifndef __MOLECULE__
#define __MOLECULE__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <texture.h>
#include <consts.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct bond_struct
{
	uint8_t type;
	uint16_t atom; // the index of the atom it is bonded to
} bond;

typedef struct atom_struct
{
	uint8_t z;				// the atomic number of the atom
	bond *bonds;			// all the bonds the aoms has
	uint8_t max_bond; // the maximum amout of bonds that this atom type can create
	uint8_t bond_num; // the current number of bonds connected to this atom
	uint16_t index;		// the index of this atom in the molecule
} Atom;

#define MOLECULE_INIT_SIZE 16
typedef struct molecule_struct
{
	Atom *atoms;
	uint16_t atom_count;
	uint16_t graph_size;
} Molecule;

Molecule *Molecule_create();

int Molecule_renderer(Molecule *mol, SDL_Color color);

/* ---------------------- adding atoms ---------------------- */
int Molecule_add_initial_atom(Molecule *mol, uint8_t z);

int Molecule_add_atom(Molecule *mol, uint8_t z, uint16_t index, uint8_t bond_type);

#endif // __MOLECULE__