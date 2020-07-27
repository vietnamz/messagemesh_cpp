#include <iostream>
#include <map>
#include <list>
#include <queue>
/*
 *
 *  min
 */

class Network {

public:
    //! default constructor.
    Network() = default;
    Network( const std::map< std::string, std::list<std::string> >& map )
    {
        routes = map;
    }

    /*!
     *  Depth first search algorithm to ensure the shortest path from start to end.
     */
    const std::list<std::string> DFS( const std::string& startNode, const std::string& endNode )
    {
        //! a queue to keep track all nodes that we already take.
        std::queue< std::string > nodes;
        nodes.push( startNode );

        std::list< std::string > visitedNodes;

        std::map<std::string, std::string> nodeAlreadySeen;
        nodeAlreadySeen[ startNode ] = std::string();

        // traverse the node that we have seen.
        while ( !nodes.empty() )
        {
            std::cout << " first node is " << nodes.front() << "\n";
            const std::string iter( nodes.front() );
            nodes.pop();
            visitedNodes.push_back( iter );
            //! stop once we get the end node.
            if ( iter == endNode )
            {
                std::cout << "Well done, We alredy foud it " << "\n";
                return reConstructMap( nodeAlreadySeen, startNode, endNode );
            }
            for( const std::string& neighbor : routes[ iter ])
            {
                if ( !isVisited( neighbor, visitedNodes ) )
                {
                    nodes.push( neighbor );
                    visitedNodes.push_back( neighbor );
                    nodeAlreadySeen[neighbor] = iter;
                    std::cout << "we expect nodeAlreadySeen " << iter << " on neighbor always the same " << nodeAlreadySeen[iter] << "\n";
                    // special case when we found the end node in the neighbors list.
                }
            }
        }
        return std::list< std::string >();
    }

private:

    const std::list< std::string> reConstructMap( const std::map<std::string, std::string>&  nodeAlreadySeen, std::string start, std::string end )
    {
        std::list< std::string > result;
        result.push_front( end );
        for( auto iter = nodeAlreadySeen.begin(); iter != nodeAlreadySeen.end(); iter++ )
        {
            if ( iter->second.size() != 0 )
            {
                result.push_front(iter->first);
            } else{
                result.push_front( iter->first );
                break;
            }
        }
        return result;
    }
    const bool isVisited( const std::string& aNodeToCheck, const std::list< std::string >& alreadySeenList )
    {
        for( const auto& iter : alreadySeenList )
        {
            if ( iter == aNodeToCheck )
            {
                return true;
            }
        }
        return false;
    }
    std::map< std::string, std::list<std::string> > routes;
};

/*
    network = {
    'Min'     : ['William', 'Jayden', 'Omar'],
    'William' : ['Min', 'Noam'],
    'Jayden'  : ['Min', 'Amelia', 'Ren', 'Noam'],
    'Ren'     : ['Jayden', 'Omar'],
    'Amelia'  : ['Jayden', 'Adam', 'Miguel'],
    'Adam'    : ['Amelia', 'Miguel', 'Sofia', 'Lucas'],
    'Miguel'  : ['Amelia', 'Adam', 'Liam', 'Nathan'],
    'Noam'    : ['Nathan', 'Jayden', 'William'],
    'Omar'    : ['Ren', 'Min', 'Scott'],
    ...
}
 */


int main() {
    std::map< std::string, std::list<std::string> > aMap;
    {
        std::list<std::string> neighbors;
        neighbors.push_back( "William" );
        neighbors.push_back( "Jayden" );
        neighbors.push_back( "Omar" );
        aMap["Min"] = neighbors;
    }

    {
        std::list<std::string> neighbors;
        neighbors.push_back( "Min" );
        neighbors.push_back( "Noam" );
        aMap["William"] = neighbors;
    }

    {
        std::list<std::string> neighbors;
        neighbors.push_back( "Min" );
        neighbors.push_back( "Amelia" );
        neighbors.push_back( "Ren" );
        neighbors.push_back("Noam");
        aMap["Jayden"] = neighbors;
    }

    {
        std::list<std::string> neighbors;
        neighbors.push_back( "Jayden" );
        neighbors.push_back( "Omar" );
        aMap["Ren"] = neighbors;
    }

    {
        std::list<std::string> neighbors;
        neighbors.push_back( "Jayden" );
        neighbors.push_back( "Miguel" );
        neighbors.push_back( "Adam" );
        aMap["Amelia"] = neighbors;
    }

    {
        std::list<std::string> neighbors;
        neighbors.push_back( "Amelia" );
        neighbors.push_back( "Miguel" );
        neighbors.push_back( "Sofia" );
        neighbors.push_back( "Lucas" );
        aMap["Adam"] = neighbors;
    }

    {
        std::list<std::string> neighbors;
        neighbors.push_back( "Amelia" );
        neighbors.push_back( "Adam" );
        neighbors.push_back( "Liam" );
        neighbors.push_back( "Nathan" );
        aMap["Miguel"] = neighbors;
    }

    {
        std::list<std::string> neighbors;
        neighbors.push_back( "Nathan" );
        neighbors.push_back( "Jayden" );
        neighbors.push_back( "William" );
        aMap["Noam"] = neighbors;
    }

    {
        std::list<std::string> neighbors;
        neighbors.push_back( "Ren" );
        neighbors.push_back( "Min" );
        neighbors.push_back( "Scott" );
        aMap["Omar"] = neighbors;
    }
    Network network( aMap );
    for( const std::string l : network.DFS( std::string( "Min" ), std::string( "Sofia" ) ) )
    {
        std::cout << l << "\n";
    }
    return 0;
}
