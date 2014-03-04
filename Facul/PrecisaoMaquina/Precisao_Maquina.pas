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

begin
    writeln(precisaoMaquinaSimples(1)); 
    writeln(precisaoMaquinaDupla(1)); 
end.  
