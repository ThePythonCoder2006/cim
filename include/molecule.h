#pragma once
#ifndef __MOLECULE__
#define __MOLECULE__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <texture.h>
#include <atom.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

enum
{
	BOND_SIMPLE,
	BOND_DOUBLE,
	BOND_TRIPLE,
	BOND_QUADRUPLE,
	BOND_SEXTUPLE,
	BOND_WEDGE,
	BOND_DASH,
	BOND_STEREO_UNDEFINED,
	BONDS_COUNT
};

typedef struct bond_struct
{
	uint8_t type;
	uint16_t atom; // the index of the atom it is bonded to
} bond;

typedef struct atom_struct
{
	uint8_t z;				// the atomic number of the atom
	bond bonds[16];		// suppose an atom can only make 16 bonds (pretty sure this will be the case)
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

int Molecule_add_initial_atom(Molecule *mol, uint8_t z);

#endif // __MOLECULE__