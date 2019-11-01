/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class DebugContent;
class GraphicsBuffer;

class DebugDisplay : public Trackable
{
public:
	DebugDisplay( const Vector2D& pos, DebugContent* pContent );
	~DebugDisplay();

	void draw( GraphicsBuffer* pTarget = NULL );

	void updateContent(DebugContent* pContent);

private:
	DebugContent* mpContent;
	Vector2D mPos;

};