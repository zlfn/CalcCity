#include "calccity.h"


const struct building buildings[41] = {

	// Menu 1
	{
		.name = "TERRE",
		.id = (unsigned char []){48, 49, 110, 111, 112, 113, 114, 120, 121, 122, 123, 124, 130, 131, 132, 133, 134},
		.cost = 10,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "EAU",
		.id = (unsigned char []){139},
		.cost = 15,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "FORET",
		.id = (unsigned char []){76},
		.cost = 15,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "HABITATIONS TYPE 1",
		.id = (unsigned char []){66},
		.cost = 100,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "HABITATIONS TYPE 2",
		.id = (unsigned char []){67},
		.cost = 150,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "HABITATIONS TYPE 3",
		.id = (unsigned char []){68},
		.cost = 200,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "BUREAUX TYPE 1",
		.id = (unsigned char []){45},
		.cost = 50,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "BUREAUX TYPE 2",
		.id = (unsigned char []){46},
		.cost = 100,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "BUREAUX TYPE 3",
		.id = (unsigned char []){47},
		.cost = 150,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "USINE TYPE 1",
		.id = (unsigned char []){54},
		.cost = 200,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "USINE TYPE 2",
		.id = (unsigned char []){55},
		.cost = 300,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "USINE TYPE 3",
		.id = (unsigned char []){56},
		.cost = 400,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "FERME TYPE 1",
		.id = (unsigned char []){9},
		.cost = 50,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "FERME TYPE 2",
		.id = (unsigned char []){19},
		.cost = 75,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "FERME TYPE 3",
		.id = (unsigned char []){44},
		.cost = 100,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},


	// Menu 2
	{
		.name = "ROUTE",
		.id = (unsigned char []){80, 81, 82, 83, 90, 91, 92, 93, 100, 101, 102},
		.cost = 10,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "PORT",
		.id = (unsigned char []){62, 63, 64, 65},
		.cost = 500,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "AEROPORT",
		.id = (unsigned char []){0, 1, 2, 12},
		.cost = 3500,
		.size = {2, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "RAIL",
		.id = (unsigned char []){84, 85, 86, 87, 94, 95, 96, 97, 104, 105, 106},
		.cost = 50,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "CENTRALE ELECTRIQUE 1",
		.id = (unsigned char []){71},
		.cost = 500,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "CENTRALE ELECTRIQUE 2",
		.id = (unsigned char []){72},
		.cost = 1000,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "CENTALE NUCLEAIRE",
		.id = (unsigned char []){50, 51, 60, 61},
		.cost = 25000,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "INCINERATEUR",
		.id = (unsigned char []){3, 4, 13, 14},
		.cost = 2500,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0},
	}

	{
		.name = "STATION D'EPURATION",
		.id = (unsigned char []){77},
		.cost = 50,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "TERRAIN DE SPORT",
		.id = (unsigned char []){78},
		.cost = 250,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "AIRE DE JEUX",
		.id = (unsigned char []){69},
		.cost = 150,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "STADE",
		.id = (unsigned char []){42, 43, 52, 53},
		.cost = 10000,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "CASERNE DE POLICE",
		.id = (unsigned char []){70},
		.cost = 250,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "CASERNE DE POMPIERS",
		.id = (unsigned char []){58},
		.cost = 250,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "HOPITAL",
		.id = (unsigned char []){59},
		.cost = 250,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "CENTRE ECOLOGIQUE",
		.id = (unsigned char []){75},
		.cost = 2500,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "ECOLE TYPE 1",
		.id = (unsigned char []){73},
		.cost = 250,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "ECOLE TYPE 2",
		.id = (unsigned char []){74},
		.cost = 500,
		.size = {1, 1},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "UNIVERSITE",
		.id = (unsigned char []){28, 29, 38, 39},
		.cost = 2500,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "EGLISE ET CIMETIERE",
		.id = (unsigned char []){10, 11, 20, 21},
		.cost = 2500,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},


	// Others buildings
	{
		.name = "IMMEUBLE";
		.id = (unsigned char []){5, 6, 15, 56},
		.cost = 0,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0},
	}

	{
		.name = "TOUR DE BUREAUX",
		.id = (unsigned char []){7, 8, 17, 18},
		.cost = 0,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "USINE",
		.id = (unsigned char []){30, 31, 40, 41},
		.cost = 0,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "CASERNE DE POLICE",
		.id = (unsigned char []){26, 27, 36, 37},
		.cost = 0,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "CASERNE DE POMPIERS",
		.id = (unsigned char []){22, 23, 32, 33},
		.cost = 0,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

	{
		.name = "HOPITAL",
		.id = (unsigned char []){24, 25, 34, 35},
		.cost = 0,
		.size = {2, 2},
		.stat = {0},
		.taxes = {0},
		.funds = {0}
	},

};