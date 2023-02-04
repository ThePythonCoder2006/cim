#include <stdlib.h>
#include <string.h>

#include <atom.h>
#include <texture.h>
#include <consts.h>

const char atom_name[ATOM_COUNT][3] = {"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg"};

// a small temporary list of atom max bond levels
const uint8_t max_atom_bond[] = {
		1, // H
		0, // He
		0, // Li
		0, // Be
		3, // B
		4, // C
		3, // N
		2, // O
		1, // F
		0, // Ne
		0, // Na
		0, // Mg
		3, // Al
		4, // Si
		3, // P
		2, // S
		1, // Cl
		0, // Ar
		0, // K
		0, // Ca
};
const char bond_names[BONDS_COUNT][22] = {"bond_simple", "bond_double", "bond_triple", "bond_quadruple", "bond_quintuple", "bond_sextuple", "bond_wedge", "bond_dash", "bond_stereo_undefined"};

Texture *(bond_textures[BONDS_COUNT]);

int load_bonds(const char *folder_path)
{
	uint8_t success = 0;

	const int BUFF_SIZE = 64;
	char buff_const[BUFF_SIZE], buff[BUFF_SIZE];
	snprintf(buff_const, BUFF_SIZE, "%s", folder_path);

	for (uint8_t i = 0; i < BONDS_COUNT; ++i)
	{
		snprintf(buff, BUFF_SIZE, "%s/%s.png", buff_const, bond_names[i]);
		bond_textures[i] = Texture_init();
		if (Texture_load_from_file(bond_textures[i], buff) == 1 || bond_textures[i] == NULL)
		{
			fprintf(stderr, PRINTF_ERROR " could not load file \"%s\" !!! %s\n", buff, SDL_GetError());
			success = 1;
		}
	}

	return success;
}