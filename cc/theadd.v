module FA(Ai, Bi, Ci, Ci1, Si);
input Ai, Bi, Ci;
output Ci1, Si;
reg Ci1, Si;
reg T1, T2, T3;
always @(Ai or Bi or Ci)
begin
Si = Ai^Bi^Ci;
T1 = Ai&Ci;
T2 = Bi&Ci;
T3 = Ai&Bi;
Ci1 = T1|T2|T3;
end
endmodule
