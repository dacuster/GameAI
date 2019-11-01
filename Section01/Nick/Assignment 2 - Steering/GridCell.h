#pragma once

class GridCell : public Trackable
{
	friend std::ostream& operator<< (std::ostream& out, const GridCell& cell);
	friend std::istream& operator>> (std::istream& out, GridCell& cell);

public:
	explicit GridCell(int index=-1, int id=-1, int val=-1);
	~GridCell() {};

	int getIndex() const { return mIndex; };
	int getID() const { return mID; };
	int getValue() const { return mValue; };

	void setID(int newID) { mID = newID; };
	void setIndex(int index) { mIndex = index; };
	void setValue(int val) { mValue = val; }
private:
	int mIndex;
	int mID=-1;
	int mValue=-1;
};

std::ostream& operator<< (std::ostream& out, const GridCell& cell);
std::istream& operator>> (std::istream& in, GridCell& cell);
