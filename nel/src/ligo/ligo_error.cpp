/** \file ligo_error.cpp
 * Error handling implementation
 *
 * $Id: ligo_error.cpp,v 1.5 2002/04/10 12:45:30 corvazier Exp $
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#include "ligo_error.h"

namespace NLLIGO
{

// ***************************************************************************

CLigoError::CLigoError()
{
	clear ();
}

// ***************************************************************************

void CLigoError::pushVertexError (TError code, uint id, uint edge)
{
	// Check if this vertex exist in the error list
	uint vertex;
	for (vertex=0; vertex<_VertexError.size(); vertex++)
	{
		if (_VertexError[vertex].Id == id)
		{
			_VertexError[vertex] = CVertex (code, id, edge);
			break;
		}
	}

	// Not found ?
	if (vertex == _VertexError.size())
	{
		// Add a vertex error
		_VertexError.push_back (CVertex (code, id, edge));
	}
}

// ***************************************************************************

uint CLigoError::numVertexError () const
{
	return _VertexError.size ();
}

// ***************************************************************************

CLigoError::TError CLigoError::getVertexError (uint error, uint &id, uint &edge) const
{
	const CVertex &vertex = _VertexError[error];
	id = vertex.Id;
	edge = vertex.Edge;
	return vertex.Code;
}

// ***************************************************************************

void CLigoError::clear ()
{
	MainError = NoError;
	_VertexError.clear ();
}

// ***************************************************************************

const char* CLigoError::_StringError[CLigoError::ErrorCount]=
{
	"No error",						// NoError
	"No vertex in the edge list",	// NoEdgeVertices
	"Opened edges detected",		// OpenedEdge
	"Mulitple edge on the boundary",// MultipleEdge
	"Vertex list invalid. One vertex should be a corner",	// VertexList
	"The vertex has not been inserted in the edge list",	// NotInserted
	"The vertex has been inserted in the edge list",		// Inserted
	"Flat zone, all vertices are in the same corner",		// FlatZone
	"The zone must have 4 edges to define a material",	// MustHave4Edges
	"A edge of the zone is not symetrical",		// NotSymetrical
	"Not the same number of vertex",	// NotSameVerticesNumber
	"Some vertices are not the same",	// NotSameVertex
	"No corner found",					// NoCornerFound
	"A edge has two times the same corner",	// TwoCornerVertices
	"A corner is missing in this edge", // CornerIsMissing
	"A boundary vertex is used by multiple edges", // VertexAlreadyUsed
	"Unkown error",						// UnknownError
};

// ***************************************************************************

const char* CLigoError::getStringError (TError errorCode)
{
	if (errorCode<=ErrorCount)
	{
		return _StringError[errorCode];
	}
	else
	{
		return _StringError[UnknownError];
	}
}

// ***************************************************************************

}
