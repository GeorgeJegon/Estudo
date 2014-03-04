program Precisao_Maquina(output); 

function precisaoMaquinaSimples (r:integer):single; 
var 
    a, s : single;
begin 
    a := 1;
    s := a + r;
    while s>r do
        begin
            a := a/2;
            s := r + a;
        end;
    precisaoMaquinaSimples := 2*a;
end; 

function precisaoMaquinaDupla (r:integer):double; 
var 
    a, s : double;
begin 
    a := 1;
    s := a + r;
    while s>r do
        begin
            a := a/2;
            s := r + a;
        end;
    precisaoMaquinaDupla := 2*a;
end;

procedure precisaoMaquinaArray (r: array of integer); 
var 
    i,t: integer;
begin 
    t := Length(r)-1;
    for i:=0 to t do
        begin
            writeln('Valor de referência: ',r[i]);
            writeln('Precisão Dupla da Maquina: ', precisaoMaquinaSimples(r[i]));
            writeln('Precisão Dupla da Maquina: ', precisaoMaquinaDupla(r[i]));
            writeln('--------------------------------------------------------');
        end;
end;

var 
	ArrayRefs: array[0..8] of integer;
begin
    ArrayRefs[0] := 1;
	ArrayRefs[1] := 10;
	ArrayRefs[2] := 17;
	ArrayRefs[3] := 100;
	ArrayRefs[4] := 184;
	ArrayRefs[5] := 1000;
	ArrayRefs[6] := 1575;
	ArrayRefs[7] := 10000;
	ArrayRefs[8] := 17893;
    precisaoMaquinaArray(ArrayRefs);
end.  
