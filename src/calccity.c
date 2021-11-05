#include "calccity.h"


const struct building buildings[41] = {

	// Menu 1
	{
		"TERRE",
		(unsigned char []){48, 49, 110, 111, 112, 113, 114, 120, 121, 122, 123, 124, 130, 131, 132, 133, 134},
		10, // cost 
		{1, 1}, //size
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // stat
		{0, 0, 0}, // taxes
		{0, 0, 0} // funds
	},

	{
		"EAU",
		(unsigned char []){139},
		15,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"FORET",
		(unsigned char []){76},
		15,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"HABITATIONS TYPE 1",
		(unsigned char []){66},
		100,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"HABITATIONS TYPE 2",
		(unsigned char []){67},
		150,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"HABITATIONS TYPE 3",
		(unsigned char []){68},
		200,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"BUREAUX TYPE 1",
		(unsigned char []){45},
		50,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"BUREAUX TYPE 2",
		(unsigned char []){46},
		100,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"BUREAUX TYPE 3",
		(unsigned char []){47},
		150,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"USINE TYPE 1",
		(unsigned char []){54},
		200,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"USINE TYPE 2",
		(unsigned char []){55},
		300,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"USINE TYPE 3",
		(unsigned char []){56},
		400,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"FERME TYPE 1",
		(unsigned char []){9},
		50,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"FERME TYPE 2",
		(unsigned char []){19},
		75,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"FERME TYPE 3",
		(unsigned char []){44},
		100,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},


	// Menu 2
	{
		"ROUTE",
		(unsigned char []){80, 81, 82, 83, 90, 91, 92, 93, 100, 101, 102},
		10,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"PORT",
		(unsigned char []){62, 63, 64, 65},
		500,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"AEROPORT",
		(unsigned char []){0, 1, 2, 12},
		3500,
		{2, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"RAIL",
		(unsigned char []){84, 85, 86, 87, 94, 95, 96, 97, 104, 105, 106},
		50,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"CENTRALE ELECTRIQUE 1",
		(unsigned char []){71},
		500,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"CENTRALE ELECTRIQUE 2",
		(unsigned char []){72},
		1000,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"CENTALE NUCLEAIRE",
		(unsigned char []){50, 51, 60, 61},
		25000,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"INCINERATEUR",
		(unsigned char []){3, 4, 13, 14},
		2500,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
	}

	{
		"STATION D'EPURATION",
		(unsigned char []){77},
		50,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"TERRAIN DE SPORT",
		(unsigned char []){78},
		250,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"AIRE DE JEUX",
		(unsigned char []){69},
		150,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"STADE",
		(unsigned char []){42, 43, 52, 53},
		10000,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"CASERNE DE POLICE",
		(unsigned char []){70},
		250,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"CASERNE DE POMPIERS",
		(unsigned char []){58},
		250,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"HOPITAL",
		(unsigned char []){59},
		250,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"CENTRE ECOLOGIQUE",
		(unsigned char []){75},
		2500,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"ECOLE TYPE 1",
		(unsigned char []){73},
		250,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"ECOLE TYPE 2",
		(unsigned char []){74},
		500,
		{1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"UNIVERSITE",
		(unsigned char []){28, 29, 38, 39},
		2500,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"EGLISE ET CIMETIERE",
		(unsigned char []){10, 11, 20, 21},
		2500,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},


	// Others buildings
	{
		"IMMEUBLE";
		(unsigned char []){5, 6, 15, 56},
		0,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
	}

	{
		"TOUR DE BUREAUX",
		(unsigned char []){7, 8, 17, 18},
		0,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"USINE",
		(unsigned char []){30, 31, 40, 41},
		0,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"CASERNE DE POLICE",
		(unsigned char []){26, 27, 36, 37},
		0,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"CASERNE DE POMPIERS",
		(unsigned char []){22, 23, 32, 33},
		0,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

	{
		"HOPITAL",
		(unsigned char []){24, 25, 34, 35},
		0,
		{2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	},

};