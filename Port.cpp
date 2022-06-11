#include "Port.h"

Port::Port()
{
	m_next = 0;
}

Port::Port(string name, string loc, double x, double y)
{
	m_name = name;
	m_location = loc;
	m_north= x;
	m_west = y;
	m_next = 0;
}

Port::~Port()
{
	free(this);
}
	// Name: GetName()
	// Desc: Returns the name of the port
	// Preconditions: None
	// Postconditions: Returns the name of the port
string Port::GetName()
{
	return m_name;
}
	// Name: GetNext()
	// Desc: Returns the pointer to the next port
	// Preconditions: None (may return either port or nullptr)
	// Postconditions: Returns m_next;
Port* Port::GetNext()
{
	return m_next;
}
	// Name: GetNorth()
	// Desc: Returns the northern coordinates of the port
	// Preconditions: None
	// Postconditions: Returns the N coordinates of the port
double Port::GetNorth()
{
	return m_north;
}
	// Name: GetWest()
	// Desc: Returns the western coordinates of the port
	// Preconditions: None
	// Postconditions: Returns the W coordinates of the port
double Port::GetWest()
{
	return m_west;
}
	// Name: GetLocation()
	// Desc: Returns the description of where the port is located
	// Preconditions: None
	// Postconditions: Returns the description of where the port is located
string Port::GetLocation()
{
	return m_location;
}
	// Name: SetNext()
	// Desc: Updates the pointer to a new target (either a port or nullptr)
	// Preconditions: None
	// Postconditions: Sets the next port
void Port::SetNext(Port* next)
{
	m_next = next;
}
