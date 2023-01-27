#include <stdio.h>

#include <atom.h>
#include <molecule.h>

#include <SDL.h>
#include <SDL_ttf.h>

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

	mol->atoms[mol->atom_count] = (Atom){.bond_num = 0, .index = 0, .z = z, .max_bond = max_atom_bond[z]};
	mol->atom_count = 1;

	return 0;
}

int Molecule_renderer(Molecule *mol)
{
	if (mol->atom_count == 1)
	{
		Texture *tex = Texture_init();
		Texture_load_text(tex, atom_name[mol->atoms[0].z], (SDL_Color){0, 0, 0, 255}, gFont);

		Texture_render(tex, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, NULL, 0, NULL, 0);

		return 0;
	}

	fprintf(stderr, "[TODO] not implemented yet !!!");
	return 1;

	return 0;
}