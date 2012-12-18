junta([H|T],L2):-junta([H|T],L2,[]).

junta([],L2,L2).
junta([H|T],L2,[H|Y]):-
	junta(T,L2,Y).
	
membro([X|_T],X).
membro([_H|T],X):-
	membro(T,X).

ordenada([_]).	
ordenada([A,B|R]):-
	A=<B,
	ordenada([B|R]).
ordenada([]).

apaga_dup([X],[X]).
apaga_dup([A,B|T],[A|Res]):-
	A\=B,
	apaga_dup([B|T],Res).
apaga_dup([A,A|T],Res):-
	apaga_dup([A|T],Res).
	
		
apaga([P|T],P,T).
apaga([H|T],P,[H|T2]):-
	apaga(T,P,T2).
