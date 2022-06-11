#include "Navigator.h"

/*
private:
	vector<Port*> m_ports; //Vector of all ports
	vector<Route*> m_routes; //Vector of all routes
	string m_fileName; //File to read in
	*/

// Name: Navigator (string) - Overloaded Constructor
// Desc: Creates a navigator object to manage routes
// Preconditions:  Provided with a filename of ports to load
// Postconditions: m_filename is populated with fileName
Navigator::Navigator(string fileName)
{
	m_fileName = fileName;
}
// Name: Navigator (destructor)
// Desc: Deallocates all dynamic aspects of a Navigator
// Preconditions: There is an existing Navigator
// Postconditions: All ports and routes are cleared
Navigator::~Navigator()
{
	for(int i = 0; i< m_ports.size(); i++)
		free(m_ports[i]);
	
	for(int i=0; i< m_routes.size(); i++)
	{
		Port *temp = m_routes[i]->GetData(0);
		for(int i = 0; i<m_routes[i]->GetSize(); i++)
		{
			Port *temp2 = temp;
			temp = temp->GetNext();
			free(temp2);
		}
		free(m_routes[i]);
	}
}
// Name: Start
// Desc: Loads the file and calls the main menu
// Preconditions: m_fileName is populated
// Postconditions: All ports are loaded and the main menu runs
void Navigator::Start()
{
	ReadFile();
	MainMenu();
}
// Name: DisplayPorts
	  // Desc: Displays each port in m_ports
	  // Preconditions: At least one port is in m_ports
	  // Postconditions: Displays all ports. Uses overloaded << provided in Port.h
void Navigator::DisplayPorts()
{
	for(int i = 0; i< m_ports.size();i ++)
	{
		cout << i << ". " <<  *m_ports[i] << endl;
	}
}
// Name: ReadFile
// Desc: Reads in a file that has data about each port including name, location, degrees
//       north and degrees west. Dynamically allocates ports and stores them in m_ports
//       The vector can hold many ports.
// Preconditions: Valid file name of ports
// Postconditions: Dynamically allocates each port and enters it into m_ports
void Navigator::ReadFile()
{
	ifstream file(m_fileName);
	while(!file.eof())
	{
		string name, location, north, west;
		getline(file, name, ',');
		getline(file, location, ',');
		if(name.length() == 0)
			break;
		getline(file, north, ',');
		getline(file, west);
		double n = stod(north);
		double w = stod(west);
		m_ports.push_back(new Port(name, location, n, w));
		//cout << name << " " << location << " " << n << " " << w << endl;
	}
}
// Name: InsertNewRoute
// Desc: Dynamically allocates a new route with the user selecting each port in the route.
//       Route named based on the first and last port automatically
//       For example, Baltimore to Boston
//       Once route is created, inserted into m_routes.
// Preconditions: Populated m_routes
// Postconditions: Inserts a new route into m_routes
void Navigator::InsertNewRoute()
{
	Route *route = new Route();
	DisplayPorts();
	int inp = 0;
	while(inp != -1)
	{
		cout << "Enter the number of the port to add to your Route: (-1 to end)\n";
		cin >> inp;
		if(inp != -1)
			route->InsertEnd(m_ports[inp-1]->GetName(), m_ports[inp-1]->GetLocation(), m_ports[inp-1]->GetNorth(), m_ports[inp-1]->GetWest());
	}
	route->UpdateName();
	m_routes.push_back(route);
	cout << "Done Building a New Route named " << route->GetName() << endl;
}
// Name: MainMenu
	  // Desc: Displays the main menu and manages exiting
	  // Preconditions: Populated m_ports
	  // Postconditions: Exits when someone chooses 5
void Navigator::MainMenu()
{
	int inp = -1;
	while(inp != 5)
	{
		cout << "What would you like to do?:\n1. Create New Route\n2. Display Route\n3. Remove Port From Route\n4. Reverse Route\n5. Exit\n";
		cin >> inp;
		if(inp == 1)
		{
			InsertNewRoute();
		}
		else if(inp == 2)
		{
			DisplayRoute();
		}
		else if(inp == 3)
		{
			RemovePortFromRoute();
		}
		else if(inp == 4)
		{
			ReverseRoute();
		}
	}
	
}
// Name: ChooseRoute
// Desc: Allows user to choose a specific route to work with by displaying numbered list
// Preconditions: Populated m_routes
// Postconditions: Returns the index of the selected route minus 1
int Navigator::ChooseRoute()
{
	cout << "Which route would you like to use?\n";
	for(int i = 0; i< m_routes.size(); i++)
	{
		cout << i+1 << ". " << m_routes[i]->GetName() << endl;
	}
	int inp;
	cin >> inp;
	return inp-1;
}
// Name: DisplayRoute
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//       If no routes, indicates that there are no routes to display
//       User selects a route from list to display
//       Displays numbered list of each port in route
//       Displays total miles of a route using RouteDistance
// Preconditions: Routes has more than one port
// Postconditions: Displays all ports in a route and the total miles of the route
void Navigator::DisplayRoute()
{
	if(m_routes.size() == 0)
	{
		cout << "There are no routes to display\n";
	}
	else
	{
		int index = ChooseRoute();
		if(index >= m_routes.size())
		{
			cout << "Invalid number selected\n";
			return;
		}
		Route *route = m_routes[index];
		route->DisplayRoute();
		cout << "The total miles of this route is " << RouteDistance(m_routes[index]) <<" miles\n";
	}
}
// Name: RemovePortFromRoute()
	  // Desc: Using ChooseRoute, displays a numbered list of all routes.
	  //       User selects one of the routes to remove a port from.
	  //       Displays a numbered list of all ports in selected route.
	  //       User selects port to remove from list.
	  //       Removes port from route. If first or last port removed, updates name of route.
	  // Preconditions: Routes has more than one port
	  // Postconditions: Displays updated route with removed port and new name
void Navigator::RemovePortFromRoute()
{
	int index = ChooseRoute();
	m_routes[index]->DisplayRoute();
	cout << "Which port would you like to remove?\n";
	int inp;
	cin >> inp;
	m_routes[index]->RemovePort(inp-1);
	m_routes[index]->UpdateName();
	m_routes[index]->DisplayRoute();
	cout << "Route named "<< m_routes[index]->GetName()<< " updated\n";
}
// Name: RouteDistance
// Desc: Calculates the total distance of a route
//       Goes from port 1 to port 2 then port 2 to port 3 and repeats for
//       length of route. Calculates the distance using CalcDistance (provided)
//       Aggregates the total and returns the total in miles
// Preconditions: Populated route with more than one port
// Postconditions: Returns the total miles between all ports in a route
double Navigator::RouteDistance(Route* route)
{
	double sum = 0;
	Port *temp = route->GetData(0);
	for(int i = 0; i< route->GetSize() -1; i++)
	{
		double dist = CalcDistance(temp->GetNorth(), temp->GetWest(), temp->GetNext()->GetNorth(), temp->GetNext()->GetWest());
		sum += dist;
		temp = temp->GetNext();
	}
	return sum;
}
// Name: ReverseRoute
// Desc: Using ChooseRoute, users chooses route  and the route is reversed
//       If no routes in m_routes, indicates no routes available to reverse
//       Renames route based on new starting port and ending port
//       For example, Baltimore to Boston becomes Boston to Baltimore
// Preconditions: Populated m_routes
// Postconditions: Reverses a specific route by reversing the ports in place
//                 Must move ports, cannot just change data in ports.
void Navigator::ReverseRoute()
{
	int index = ChooseRoute();
	if(m_routes[index]->GetSize() == 0)
		cout << "No routes available to reverse\n";
	else
	{
		m_routes[index]->ReverseRoute();
		m_routes[index]->UpdateName();
	}
}
