#pragma once

#include "Enums.h"

struct Coord
{
	int i, j;
	Coord() { i = -1; j = -1; }
	Coord(int _i, int _j) { i = _i; j = _j; }

};

struct CoordType :public Coord
{
	PieceType piece_type;
	CoordType() { piece_type = PIECE_NONE; }
	CoordType(Coord& coord, PieceType _piece_type) { i = coord.i; j = coord.j; piece_type = _piece_type; }
};

struct CoordScore :public CoordType
{
	int Score;
	CoordScore() { Score = 0; }
	CoordScore(CoordType& coord, int _Score) { i = coord.i; j = coord.j; piece_type = coord.piece_type; Score = _Score; }
};