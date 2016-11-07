public class BoardManager
{
	Board board;
	Stack<Tile> tileStack;

	public Board getBoard()
	{
		return board;
	}
	
	public void printBoard()
	{
		// text-based for now
		// eventually could be more GUI		
	}
		
	public void gameInit()
	{
		// create Board -> new Board();
		board = new Board();
		
		// place inital central tile -> makeMove(m)
		
		
		// create the Tile stack
		tileStack = new TilePool(); // some method inside
	}
	
	public Tile nextTile()
	{
		return tileStack->pop();
	}
	
	public Moves[] getLegalMoves(Tile tile)
	{
		// loop through edge locations, helper method vvvvv	
		return GameRules->isLegalMove(/* params */);
	}
	
	public bool makeMove(Move move)
	{
		// already checked that this is legal
		
		// to implement based on Board implementaiton
	}
}

struct Move
{
	Tile tile;
	Location location;
}
