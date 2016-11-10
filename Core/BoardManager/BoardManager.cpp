struct Coord
{
	int x;
	int y;
	
	Coord(int a, int b)
	{
		x = a;
		y = b;
	}
};

struct Move
{
	Tile tile;
	Coord coord;
	
	Move(Tile t, Coord c)
	{
		tile = t;
		coord = c;
	}
};

public class BoardManager
{
	Board board;
	Vector<Tile> tileOrder;
	int currentTile;
	
	Coord minCoord;
	Coord maxCoord;
	
	public BoardManager()
	{
		
	}

	public Board getBoard()
	{
		return board;
	}
	
	public void printBoard()
	{
		/// TODO: consider better visual?
		
		Tile[][] boardTiles = board.getTileMatrix();
		
		for(Tile[] row : boardTiles)
		{
			for(Tile[] tile : row)
			{
				if(tile == null)
				{
					std::cout << "-";
				}
				else
				{
					/// TODO: make this an enum / something better
					std::cout << tile.getTileType();
				}
			}
		}		
	}
		
	public void gameInit()
	{
		board = new Board();
		
		Coord center = new Coord(77,77);
		
		minCoord = center;
		maxCoord = center;
		
		// place inital center tile
		Tile startingTile = Tile.... /// TODO
		Move startingMove = new Move(startingTile, center);
		
		// create the Tile stack
		tileOrder = new TilePool(); // outside method?
	}
	
	public Tile nextTile()
	{
		return tileOrder.front();
	}
	
	public Vector<Tile> getTileOrder()
	{
		return tileOrder;
	}
	
	public Vector<Move> getLegalMoves(Tile tile)
	{
		Vector<Move> legalMoves = new Vector<Move>();
		Coord[] edgeLocations = board.getEdgeLocations();
		
		for(Coord edgeLocation : edgeLocations)
		{
			if(GameRules->isLegalMove(tile, edgeLocation))
			{
				legalMoves.push_back(new Move(tile, edgeLocation));
			}
		}
		return legalMoves;
	}
	
	public bool makeMove(Move move)
	{
		// already checked that this is legal
		
		// to implement based on Board implementaiton
		board->set(move.tile, move.coord);
		
		if(move.coord.x < minCoord.x) { minCoord.x = move.coord.x; }
		if(move.coord.y < minCoord.y) {	minCoord.y = move.coord.y; }
		if(move.coord.x > maxCoord.x) {	maxCoord.x = move.coord.x; }
		if(move.coord.y > maxCoord.y) {	maxCoord.x = move.coord.y; }
		
		// remove tile from list
		tileOrder.erase(tileOrder.begin());
		
		// consider checking whether the passed Tile == top?
	}
}
