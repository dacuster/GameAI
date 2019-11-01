// C++ Library
#include <iostream>

// Dean Library
#include "Trackable.h"

// Common Library
#include "GridCell.h"

GridCell::GridCell(int index, int id, int val)
	:mIndex(index)
	,mID(id)
	,mValue(val)
{
}

std::ostream& operator<<(std::ostream& out, const GridCell& cell)
{
	out << cell.getIndex() << " " << cell.getID() << " " << cell.getValue() << " ";
	return out;
}

std::istream& operator>>(std::istream& in, GridCell& cell)
{
	in >> cell.mIndex >> cell.mID >> cell.mValue;
	return in;
}
