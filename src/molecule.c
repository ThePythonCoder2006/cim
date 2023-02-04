#include <stdio.h>
#include <inttypes.h>

#include <atom.h>
#include <molecule.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

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

	mol->atoms[mol->atom_count] = (Atom){.bond_num = 0, .index = 0, .z = z, .max_bond = max_atom_bond[z], .bonds = calloc(max_atom_bond[z], sizeof(bond))};
	mol->atom_count = 1;

	return 0;
}

int Molecule_renderer(Molecule *mol, SDL_Color color)
{
	if (mol->atom_count == 1)
	{
		Texture *tex = Texture_init();
		Texture_load_text(tex, atom_name[mol->atoms[0].z], color, gFont);

		Texture_render(tex, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, NULL, 0, NULL, 0);

		return 0;
	}

	// fprintf(stderr, "[TODO] not implemented yet !!!\n");
	// return 1;

	Texture *tex = Texture_init();
	for (uint8_t i = 0; i < mol->atom_count; ++i)
	{
		Texture_load_text(tex, atom_name[mol->atoms[i].z], color, gFont);

		Texture_render(tex, SCREEN_WIDTH / 2 + BOND_LEN * i, SCREEN_HEIGHT / 2, NULL, 0, NULL, 0);
		for (uint8_t j = 0; j < mol->atoms[i].max_bond; ++i)
		{
			Texture_render(bond_textures[mol->atoms[i].bonds[j].type], SCREEN_WIDTH / 2 + BOND_LEN * i + j * 10, SCREEN_HEIGHT / 2, NULL, 90, &(SDL_Point){0, 0}, 0);
		}
	}

	return 0;
}

int Molecule_add_atom(Molecule *mol, uint8_t z, uint16_t index, uint8_t bond_type)
{
	if (index >= mol->atom_count)
	{
		fprintf(stderr, PRINTF_ERROR " atom index must be an already existing atom. %" PRIu16 " provided, max is %" PRIu16 "\n", index, mol->atom_count);
		return 1;
	}

	if (mol->graph_size == mol->atom_count) // if there is no space anymore in the list
	{
		fprintf(stderr, "[TODO] not implemented yet !!!\n");
		return 1;
	}

	// add the new atom in the list
	mol->atoms[mol->atom_count] = (Atom){.bond_num = 1, .max_bond = max_atom_bond[z], .z = z, .index = mol->atom_count, .bonds = calloc(max_atom_bond[z], sizeof(bond))};
	mol->atoms[mol->atom_count].bonds[0] = (bond){.type = bond_type, .atom = index}; // set the type of the bond on the new atom

	// add the bond to the already there atom
	mol->atoms[index].bonds[mol->atoms[index].bond_num - 1] = (bond){.type = bond_type, .atom = mol->atom_count};

	++mol->atom_count;

	return 0;
}