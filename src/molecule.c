#ifndef __MOLECULE__
#include <molecule.h>
#endif

Molecule *Molecule_create()
{
	Molecule *mol = malloc(sizeof(Molecule));

	mol->atoms = calloc(MOLECULE_INIT_SIZE, sizeof(Atom));
	mol->graph_size = MOLECULE_INIT_SIZE;
	mol->atom_count = 0;

	return mol;
}

int Molecule_add_initial_atom(Molecule *mol, uint8_t z)
{
	if (mol->atom_count >= 1)
	{
		fprintf(stderr, "molecule must not hold any atoms already !\n");
		return 1;
	}

	mol->atom_count = 1;
	mol->atoms[mol->atom_count] = (Atom){.bond_num = 0, .index = 0, .z = z};

	return 0;
}