#include "Route.h"

// Name: Route() - Default Constructor
// Desc: Used to build a new Route (linked list) make up of ports
// Preconditions: None
// Postconditions: Creates a new Route where m_head and m_tail point to nullptr and size = 0
Route::Route()
{
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}
// Name: SetName(string)
// Desc: Sets the name of the route (usually first port to last port)
// Preconditions: None
// Postconditions: Sets name of route
void  Route::SetName(string name)
{
	m_name = name;
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}
// Name: ~Route() - Destructor
// Desc: Used to destruct a strand of Route
// Preconditions: There is an existing Route strand with at least one port
// Postconditions: Route is deallocated (including all dynamically allocated ports)
//                 to have no memory leaks!
Route::~Route()
{
	Port *temp = m_head;
	for(int i = 0; i<m_size; i++)
	{
		Port *temp2 = temp;
		temp = temp->GetNext();
		free(temp2);
	}
}
// Name: InsertEnd (string, string, double double)
// Desc: Creates a new port using the data passed to it.
//       Inserts the new port at the end of the route
// Preconditions: Takes in a Port
//                Requires a Route
// Postconditions: Adds the new port to the end of a route
void Route::InsertEnd(string name, string loc, double x, double y)
{
	Port *port = new Port(name, loc, x, y);
	port->SetNext(0);
	if(m_size == 0)
	{
		m_head = port;
		m_tail = port;
		
	}
	else
	{
		m_tail->SetNext(port);
		m_tail = m_tail->GetNext();
	}
	m_size ++;
}
// Name: RemovePort(int index)
	  // Desc: Removes a port from the route at the index provided
	  //       Hint: Special cases (first port, last port, middle port)
	  // Preconditions: Index must be less than the size of the route
	  //       Cannot make route less than two ports. If the route has
	  //       two or fewer ports, fails.
	  // Postconditions: Name may be updated. Size is reduced. Route has one less port.
void Route::RemovePort(int port)
{
	if(port >= m_size)
		return;
	Port *temp = m_head;
	Port *prev = 0;
	for(int i = 0; i< port; i++)
	{
		prev = temp;
		temp = temp->GetNext();
	}
	if(prev == 0) //first port removed
	{
		m_head = m_head->GetNext();
		if(m_tail == temp)
			m_tail = nullptr;
		free(temp);
	}
	else if(temp == m_tail)
	{
		prev->SetNext(nullptr);
		m_tail = prev;
		free(temp);
		
	}
	else
	{
		cout << "Test3";
		prev->SetNext(temp->GetNext());
		cout << "Test1";
		free(temp);
		cout << "Test2";
	}
	m_size--;
}
// Name: GetName()
// Desc: Returns the name of the route (Usually starting port to last port)
//       For example: Baltimore to Brunswick
// Preconditions: Requires a Route
// Postconditions: Returns m_name;
string Route::GetName()
{
	return m_name;
}
// Name: UpdateName()
// Desc: Updates m_name based on the name of the first port in the route
//       and the last port in the route
//       For example: Baltimore to Brunswick
// Preconditions: Requires a Route with at least two ports
// Postconditions: Returns m_name;
string Route::UpdateName()
{
	string str = m_head->GetName() + " to " + m_tail->GetName();
	m_name = str;
	return str;
}
// Name: GetSize()
	  // Desc: Returns the number of ports in a route
	  // Preconditions: Requires a Route
	  // Postconditions: Returns m_size;
int Route::GetSize()
{
	return m_size;
}
// Name: ReverseRoute
// Desc: Reverses a route
// Preconditions: Reverses the Route
// Postconditions: Route is reversed in place; nothing returned
void Route::ReverseRoute()
{
	m_tail = m_head;
    Port* current = m_head;
    Port *prev = nullptr, *next = nullptr;
	while (current != nullptr)
	{
    	next = current->GetNext();
		current->SetNext(prev);
		prev = current;
		current = next;
    }
    m_head = prev;
}
// Name: GetData (int)
// Desc: Returns a port at a specific index
// Preconditions: Requires a Route
// Postconditions: Returns the port from specific item
Port* Route::GetData(int index)
{
	Port *temp = m_head;
	for(int i = 0; i< index; i++)
		temp = temp->GetNext();
	return temp;
}
// Name: DisplayRoute
// Desc: Displays all of the ports in a route
// Preconditions: Requires a Route
// Postconditions: Displays all of the ports in a route
// Formatted: Baltimore, Maryland (N39.209 W76.517)
void Route::DisplayRoute()
{
	Port *temp = m_head;
	for(int i = 0; i< m_size; i++)
	{
			cout << i+1 << ". " << *temp <<  "(N" << temp->GetNorth() << " W" << temp->GetWest() << ")\n";
			temp = temp->GetNext();
	}
}
