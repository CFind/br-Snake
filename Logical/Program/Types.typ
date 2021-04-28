
TYPE
	Food : 	STRUCT 
		xLoc : UINT;
		yLoc : UINT;
	END_STRUCT;
	Direction : 
		(
		Left := 0,
		Right := 1,
		Up := 2,
		Down := 3
		);
	Color : 
		(
		Green := 191,
		Red := 51
		);
	snakeNode : 	STRUCT 
		xLoc : UINT;
		yLoc : UINT;
	END_STRUCT;
	Html_typ : 	STRUCT 
		Node : ARRAY[0..90]OF snakeNode;
		Food : Food;
	END_STRUCT;
END_TYPE
