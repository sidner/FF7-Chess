:- use_module(library(socket)).
:-reconsult('list_func.pl').


/* FACTS */
/*Pieces P1*/
name('R', 'King').
name('D', 'Duke').
name('P', 'Prince').
name('K', 'Knight').
name('S1', 'Sargent1').
name('S2', 'Sargent2').
name('E', 'Esquire').
name('C', 'Castle').
name('G', 'Green').
name('A', 'Archer').
name('L1', 'Lancer1').
name('L2', 'Lancer2').
name('r', 'king').
name('d', 'duke').
name('p', 'prince').
name('k', 'knight').
name('s1', 'sargent1').
name('s2', 'sargent2').
name('e', 'esquire').
name('c', 'castle').
name('g', 'green').
name('a', 'archer').
name('l1', 'lancer1').
name('l2', 'lancer2').

all_pieces(['R','D','P','K1','K2','S1','S2','E','A','L1','L2', 'r','d','p','k1','k2','s1','s2','e','a','l1','l2']).
all_structs(['C','G', 'c','g']).
terrain(['M','F']).
	
structP1(['C','G']).
pieceP1(['R','D','P','K1','K2','S1','S2','E','A','L1','L2']).
structP2(['c','g']).
pieceP2(['r','d','p','k1','k2','s1','s2','e','a','l1','l2']).
empty('_').
emptylist(['_','_']).
royaltyP1(['R','D','P']).
royaltyP2(['r','d','p']).

mountedP1(['D','P','K1','K2']).
mountedP2(['d','p','k1','k2']).

onfootP1(['R','S1','S2','A','L1','L2']).
onfootP2(['r','s1','s2','a','l1','l2']).




%**************** SERVER *****************

init:-create_server(5000).

create_server(Port) :-
        tcp_socket(Socket),
        tcp_bind(Socket, Port),
        tcp_listen(Socket, 5),
        tcp_open_socket(Socket, AcceptFd, _),
	dispatch(AcceptFd).

dispatch(AcceptFd) :-
        tcp_accept(AcceptFd, Socket, Peer),
        thread_create(ignore(process_client(Socket, Peer)), _,
                      [ detached(true)
                      ]),
        dispatch(AcceptFd).

process_client(Socket, _Peer) :-
        setup_call_cleanup(tcp_open_socket(Socket, In, Out),
                           handle_service(In, Out),
                           close_connection(In, Out)).

close_connection(In, Out) :-
        close(In, [force(true)]),
        close(Out, [force(true)]).

handle_service(In, Out) :-
	read(In, Int),
	writeln(Int),
	(   
		(
			Int == 'disconnect',
			call_request(Int,Term),
			format(Out, '~q.~n',[Term]),
			flush_output(Out),
			true
		);   
		call_request(Int,Result),
		format(Out, '~q.~n', [Result]),
	    flush_output(Out),
	    handle_service(In, Out)
	).

call_request(hello,'hello').	

call_request(disconnect,'Goodbye').

call_request(test,Term):-Term='teste'.

call_request(validate_move(Board,Piece,Xf,Yf),Result):-
	((validate_move(Board,Piece,Xf,Yf),
        get_element(Board,PieceatEnd,Xf,Yf,0),
        checkPlayer(Piece,PieceatEnd),
        Result = 'true');
	(Result = 'false')).
	
call_request(validate_insert(Board,Piece,X,Y),Result):-
	((validate_insert(Board,Piece,X,Y),Result = 'true');
	(Result = 'false')).
	
call_request(_,'Invalid').


%*******************FEUDAL**********************


checkPlayer(Piece,PieceatEnd):-
        (
            (
                Piece = '_'
            );
            (
                pieceP1(Pieces),
                membro(Pieces,Piece),
                \+membro(Pieces,PieceatEnd)
            );
            (
                pieceP2(Pieces),
                membro(Pieces,Piece),
                \+membro(Pieces,PieceatEnd)
            )
        ).


validate_move(Board,Piece,Xf,Yf):-

	get_coordinates(Board,Piece,Xi,Yi),
	(	
		(
			pieceP1(Pieces),
			membro(Pieces,Piece),
			mountedP1(Mounted),
			name(King,'King'),
			name(Sargent1,'Sargent1'),
			name(Sargent2,'Sargent2'),
			name(Archer,'Archer'),
			name(Lancer1,'Lancer1'),
			name(Lancer2,'Lancer2'),
			name(Squire,'Esquire'),
			name(Archer,'Archer')
		);
		(
			pieceP2(Pieces),
			membro(Pieces,Piece),
			mountedP2(Mounted),
			name(King,'king'),
			name(Sargent1,'sargent1'),
			name(Sargent2,'sargent2'),
			name(Archer,'archer'),
			name(Lancer1,'lancer1'),
			name(Lancer2,'lancer2'),
			name(Squire,'esquire'),
			name(Archer,'archer')
		)
	),
	(
		(
			membro(Mounted,Piece),
			(
				(
					validate_horizontal_move(Board,Piece,Xf,Yf)
				);
				(
					validate_vertical_move(Board,Piece,Xf,Yf)
				);
				(
					validate_diagonal_move(Board,Piece,Xf,Yf)
				)
			)
		);
		(
			(
                            (
                            	Piece = Sargent1
                            );
                            (
				Piece = Sargent2
                            )
                        ),
			validate_diagonal_move(Board,Piece,Xf,Yf)
		);
		(
			Piece = King,
			Diffx is Xf - Xi,
			abs(Diffx,Adiffx),
			Diffy is Yf - Yi,
			abs(Diffy,Adiffy),
			(
				(
					Adiffx = 1,
					Adiffy = 1,
					validate_diagonal_move(Board,Piece,Xf,Yf)
				);
				(
					Adiffx = 0,
					Adiffy = 1,
					validate_vertical_move(Board,Piece,Xf,Yf)
				);
				(
					Adiffx = 1,
					Adiffy = 0,
					validate_horizontal_move(Board,Piece,Xf,Yf)
				)
			)
		);
		(	
			(
				(
					Piece = Lancer1
				);
				(
					Piece = Lancer2
				)
			),
			(	
				(
					validate_horizontal_move(Board,Piece,Xf,Yf)
				);
				(
					validate_vertical_move(Board,Piece,Xf,Yf)
				)
			)
		);
		(
			Piece = Squire,
			validate_l_move(Board,Piece,Xf,Yf)
		);
		(
			%Passar isto para um validate_move_archer isolado.
			Piece = Archer,
			true
		)
	).


check_victory(Board,Player):-
    (
        (
            Player = 2,
            name(Castle,'Castle'),
            name(King,'King'),
            name(Duke,'Duke'),
            name(Prince,'Prince')
        );
        (
            Player = 1,
            name(Castle,'castle'),
            name(King,'king'),
            name(Duke,'duke'),
            name(Prince,'prince')
        )
    ),
    (
        (
            \+get_coordinates(Board,Castle,_,_)
        );
        (
            \+get_coordinates(Board,King,_,_),
            \+get_coordinates(Board,Duke,_,_),
            \+get_coordinates(Board,Prince,_,_)
        )
    ).
            

get_coordinates(Board,Piece,X,Y):-get_coordinates(Board,Piece,X,Y,0).

get_coordinates([BoardH|_],Piece,X,Y,Y):-get_coordinates_line(BoardH,Piece,X).
get_coordinates([BoardH|BoardT],Piece,X,Y,Acc):-
	\+get_coordinates_line(BoardH,Piece,X),
	Acc1 is Acc + 1,
	get_coordinates(BoardT,Piece,X,Y,Acc1).

get_coordinates_line(Line,Piece,X):-get_coordinates_line(Line,Piece,X,0).

get_coordinates_line([[Piece,_]|_],Piece,X,X).
get_coordinates_line([[EleH,_]|LineT],Piece,X,Acc):-
	EleH \= Piece,
	Acc1 is Acc + 1,
	get_coordinates_line(LineT,Piece,X,Acc1).


get_element(Board,Elem,X,Y,Type):-get_element_board(Board,Elem,X,Y,Type,0).

get_element_board([BoardH|_],Elem,X,Y,Type,Y):-
	(
		(
			Type = 0,
			get_piece_line(BoardH,Elem,X)
		);
		(
			Type = 1,
			get_terrain_line(BoardH,Elem,X)
		)
	).
	
get_element_board([_|BoardT],Piece,X,Y,Type,Acc):-
	Acc < Y,
	Acc1 is Acc + 1,
	get_element_board(BoardT,Piece,X,Y,Type,Acc1).
	
get_piece_line(Line,Piece,X):-get_piece_line(Line,Piece,X,0).

get_piece_line([[Piece,_]|_],Piece,X,X).
get_piece_line([_|PieceT],Piece,X,Acc):-
	Acc < X,
	Acc1 is Acc + 1,
	get_piece_line(PieceT,Piece,X,Acc1).

get_terrain_line(Line,Terrain,X):-get_terrain_line(Line,Terrain,X,0).
	
get_terrain_line([[_,Terrain]|_],Terrain,X,X).	
get_terrain_line([_|PieceT],Terrain,X,Acc):-
	Acc < X,
	Acc1 is Acc + 1,
	get_terrain_line(PieceT,Terrain,X,Acc1).




%*******************Transformar todos os inserts em validates************************
%************************************************************************************


/*Checks to see if the current house is empty or is a terrain*/ 
check_terrain([[_,Current]|_]):-
	terrain(Terrains),
	membro(Terrains,Current).

check_piece([[Current,_]|_]):-
	pieceP1(Pieces),
	membro(Pieces,Current).


/* calls check terrain to see if its anything there, if not calls final
validate_insert element piece*/
validate_insert_element_piece(Line):-
	\+check_terrain(Line),
	\+check_piece(Line).

/*Function to validate_insert Element into line.
One sorts through the line to get to the X element.
Then has one for if it is a terrain and will have another
for a set piece.*/		
validate_insert_element(Element,Line,X):- validate_insert_element(Element,Line,X,0).

/*Sorts through line until it reaches X*/
validate_insert_element(Element,[_LineH|LineT],X,Acc):-
	Acc < X,
	Acc1 is Acc + 1,
	validate_insert_element(Element,LineT,X,Acc1).
	
/*in case its a piece*/
validate_insert_element(Element,LineT,X,X):-
	terrain(Terrains),
	\+membro(Terrains,Element),
	all_pieces(Pieces),
	membro(Pieces,Element),
	validate_insert_element_piece(Element,LineT).


validate_insert(Element,Board,X,Y):- validate_insert(Element,Board,X,Y,0).

/*Selecting Line to alter*/
validate_insert(Element,Board,X,Y,Y):-
	nth0(0,Board,Line),
	validate_insert_element(Element,Line,X).
validate_insert(Element,[_BoardH|BoardT],X,Y,Acc):-
	Acc < Y,
	Acc1 is Acc + 1,
	validate_insert(Element,BoardT,X,Y,Acc1).


abs(X,Y):-
	X<0,
	Y is -X.
abs(X,X):-
	X>=0.

get_column(Board,X,Column):-
	length(Board,Size),
	get_column(Board,X,Column,Size,0).

get_column(_,_,[],Size,Size).
get_column(Board,X,[ColumnH|ColumnT],Size,Acc):-
	Acc < Size,
	nth0(Acc,Board,Line),
	nth0(X,Line,ColumnH),
	Acc1 is Acc + 1,
	get_column(Board,X,ColumnT,Size,Acc1).

validate_l_move(Board,Piece,Xf,Yf):-
	get_coordinates(Board,Piece,Xi,Yi),
	length(Board,YMax),
	get_column(Board,0,Column),
	length(Column,XMax),
	Xf < XMax,
	Xf >= 0,
	Yf < YMax,
	Yf >= 0,
	(
		(
			Xt is Xi + 2,
			Xf = Xt,
			(
				(
					Yt is Yi + 1,
					Yf = Yt
				);
				(
					Yt is Yi - 1,
					Yf = Yt
				)
			),
			validate_horizontal_move(Board,Piece,Xf,Yi),
			validate_vertical_move(Board,Piece,Xf,Yi,Xf,Yf)
		);
		(
			Xt is Xi - 2,
			Xf = Xt,
			(
				(
					Yt is Yi + 1,
					Yf = Yt
				);
				(
					Yt is Yi - 1,
					Yf = Yt
				)
			),
			validate_horizontal_move(Board,Piece,Xf,Yi),
			validate_vertical_move(Board,Piece,Xf,Yi,Xf,Yf)
		);
		(
			Xt is Xi + 1,
			Xf = Xt,
			(
				(
					Yt is Yi + 2,
					Yf = Yt					
				);
				(
					Yt is Yi - 2,
					Yf = Yt
				)
			),
			validate_horizontal_move(Board,Piece,Xf,Yi),
			validate_vertical_move(Board,Piece,Xf,Yi,Xf,Yf)
		);
		(
			Xt is Xi - 1,
			Xf = Xt,
			(
				(
					Yt is Yi + 2,
					Yf = Yt					
				);
				(
					Yt is Yi - 2,
					Yf = Yt
				)
			),
			validate_horizontal_move(Board,Piece,Xf,Yi),
			validate_vertical_move(Board,Piece,Xf,Yi,Xf,Yf)
		);
		(
			Yt is Yi + 2,
			Yf = Yt,
			(
				(
					Xt is Xi + 1,
					Xf = Xt
				);
				(
					Xt is Xi - 1,
					Xf = Xt
				)
			),
			validate_vertical_move(Board,Piece,Xi,Yf),
			validate_horizontal_move(Board,Piece,Xi,Yf,Xf,Yf)
		);
		(
			Yt is Yi - 2,
			Yf = Yt,
			(
				(
					Xt is Xi + 1,
					Xf = Xt
				);
				(
					Xt is Xi - 1,
					Xf = Xt
				)
			),
			validate_vertical_move(Board,Piece,Xi,Yf),
			validate_horizontal_move(Board,Piece,Xi,Yf,Xf,Yf)
		);
		(
			Yt is Yi + 1,
			Yf = Yt,
			(
				(
					Xt is Xi + 2,
					Xf = Xt
				);
				(
					Xt is Xi - 2,
					Xf = Xt
				)
			),
			validate_vertical_move(Board,Piece,Xi,Yf),
			validate_horizontal_move(Board,Piece,Xi,Yf,Xf,Yf)
		);
		(
			Yt is Yi - 1,
			Yf = Yt,
			(
				(
					Xt is Xi + 2,
					Xf = Xt
				);
				(
					Xt is Xi - 2,
					Xf = Xt
				)
			),
			validate_vertical_move(Board,Piece,Xi,Yf),
			validate_horizontal_move(Board,Piece,Xi,Yf,Xf,Yf)
		)
	).
					
					
validate_diagonal_move(Board,Piece,Xf,Yf):-
	get_coordinates(Board,Piece,Xi,Yi),
	validate_diagonal_move(Board,Piece,Xi,Yi,Xf,Yf).
	
validate_diagonal_move(Board,Piece,Xi,Yi,Xf,Yf):-
	length(Board,YMax),
	get_column(Board,0,Column),
	length(Column,XMax),
	Xf < XMax,
	Xf >= 0,
	Yf < YMax,
	Yf >= 0,
	(
		(
			Yf > Yi,
			Xf > Xi,
			Diffx is Xf-Xi,
			Diffy is Yf-Yi,
			WayX is 0,
			WayY is 0
		);
		(
			Yf > Yi,
			Xf < Xi,
			Diffx is Xi-Xf,
			Diffy is Yf-Yi,
			WayX is 1,
			WayY is 0
		);
		(
			Yf < Yi,
			Xf > Xi,
			Diffx is Xf-Xi,
			Diffy is Yi-Yf,
			WayX is 0,
			WayY is 1
		);
		(
			Yf < Yi,
			Xf < Xi,
			Diffx is Xi-Xf,
			Diffy is Yi-Yf,
			WayX is 1,
			WayY is 1
		)
	),
	Diffx = Diffy,
	check_diagonal_houses(Board,Piece,Xi,Yi,WayX,WayY,Diffx).
	
check_diagonal_houses(Board,_,Xi,Yi,WayX,WayY,1):-
	(
		(
			WayX = 0,
			WayY = 0,
			Xf is Xi + 1,
			Yf is Yi + 1
		);
		(
			WayX = 1,
			WayY = 1,
			Xf is Xi - 1,
			Yf is Yi - 1
		);
		(
			WayX = 0,
			WayY = 1,
			Xf is Xi + 1,
			Yf is Yi - 1
		);
		(
			WayX = 1,
			WayY = 0,
			Xf is Xi - 1,
			Yf is Yi + 1
		)
	),
	get_element(Board,TerrainInWay,Xf,Yf,1),
	(
		(
			TerrainInWay = 'F'
		);
		(
			TerrainInWay = '_'
		)
	).
check_diagonal_houses(Board,Piece,Xi,Yi,WayX,WayY,Diff):-
	(
		(
			WayX = 0,
			WayY = 0,
			Xf is Xi + 1,
			Yf is Yi + 1
		);
		(
			WayX = 1,
			WayY = 1,
			Xf is Xi - 1,
			Yf is Yi - 1
		);
		(
			WayX = 0,
			WayY = 1,
			Xf is Xi + 1,
			Yf is Yi - 1
		);
		(
			WayX = 1,
			WayY = 0,
			Xf is Xi - 1,
			Yf is Yi + 1
		)
	),
	get_element(Board,PieceInWay,Xf,Yf,0),
	get_element(Board,TerrainInWay,Xf,Yf,1),
	PieceInWay = '_',
	(
		(
			TerrainInWay = 'F'
		);
		(
			TerrainInWay = '_'
		)
	),
	Diff1 is Diff - 1,
	check_diagonal_houses(Board,Piece,Xf,Yf,WayX,WayY,Diff1).
		
validate_vertical_move(Board,Piece,Xf,Yf):-
	get_coordinates(Board,Piece,Xi,Yi),
	validate_vertical_move(Board,Piece,Xi,Yi,Xf,Yf).

validate_vertical_move(Board,Piece,Xi,Yi,Xf,Yf):-
	Xi = Xf,
	get_column(Board,Xi,Column),
	length(Column,SizeColumn),
	Yf < SizeColumn,
	Yf >= 0,
	(
		(
			Yf < Yi,
			Diff is Yi - Yf,
			check_each_house(Column,Piece,Yi,0,Diff),! %fails if there is a terrain that Piece cannot cross.
		);
		(
			Yf > Yi,
			Diff is Yf - Yi,
			check_each_house(Column,Piece,Yi,1,Diff),! %fails if there is a terrain that Piece cannot cross.
		);
		(
			Yf = Yi,
			false
		)
	).

validate_horizontal_move(Board,Piece,Xf,Yf):-
	get_coordinates(Board,Piece,Xi,Yi),
	validate_horizontal_move(Board,Piece,Xi,Yi,Xf,Yf).
	
validate_horizontal_move(Board,Piece,Xi,Yi,Xf,Yf):-
	Yi = Yf,
	nth0(Yf,Board,Line),
	length(Line,SizeLine),
	Xf < SizeLine,
	Xf >= 0,
	(
		(
			Xf < Xi,
			Diff is Xi - Xf,
			check_each_house(Line,Piece,Xi,0,Diff),! %fails if there is a terrain that Piece cannot cross.
		);
		(
			Xf > Xi,
			Diff is Xf - Xi,
			check_each_house(Line,Piece,Xi,1,Diff),! %fails if there is a terrain that Piece cannot cross.
		);
		(
			Xf = Xi,
			write('You are moving to the same house. That does not make sense.'),nl,false
		)
	).
	

check_each_house(Line,Piece,Xi,Way,1):-
	(
		(
			Way = 0,
			Xf is Xi - 1
		);
		(
			Way = 1,
			Xf is Xi + 1
		)
	),
	get_terrain_line(Line,TerrainInWay,Xf),
	mountedP1(MP1),
	mountedP2(MP2),
	junta(MP1,MP2,ALLM),
	(
		(
			TerrainInWay = 'M',
			false
		);
		(
			TerrainInWay = 'F',
			\+membro(ALLM,Piece)
		);
		(
			TerrainInWay = '_'
		)
	).		
check_each_house(Line,Piece,Xi,Way,Diff):-
	(
		(
			Way = 0,
			Xf is Xi - 1
		);
		(
			Way = 1,
			Xf is Xi + 1
		)
	),
	get_piece_line(Line,PieceInWay,Xf),
	(
		(
			all_pieces(Pieces),
			membro(Pieces,PieceInWay),
			fail
		);
		(
			get_terrain_line(Line,TerrainInWay,Xf),
			mountedP1(MP1),
			mountedP2(MP2),
			junta(MP1,MP2,ALLM),
			(
				(
					TerrainInWay = 'M',
					false
				);
				(
					TerrainInWay = 'F',
					\+membro(ALLM,Piece)
				);
				(
					TerrainInWay = '_'
				)
			)
		)
	),
	Diff1 is Diff - 1,
	check_each_house(Line,Piece,Xf,Way,Diff1).
