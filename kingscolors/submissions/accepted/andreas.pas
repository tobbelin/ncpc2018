program landoftrees;
const PRIME : int64 = 1000000007;
var n, k, i, j: integer;
var T : array [0..2500,0..2500] of int64;
begin
  read(n);
  read(k);
  for i := 0 to n do
  begin
    T[0,i] := 0;
    T[i,0] := 0;
  end;
  T[0,0] := 1;
  for i := 1 to k do
  begin
    for j := 1 to n do
    begin
      T[i,j] := (i*T[i-1,j-1] + (i-1)*T[i, j-1]) mod PRIME;
    end;
  end; 
  writeln(T[k,n]); 
end.
