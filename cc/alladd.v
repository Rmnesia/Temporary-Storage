module test(A, B, M, S, Cout);
input[31:0] A,B; 
input M;
output[31:0] S;
output Cout;
wire[32:0] C;
wire[31:0] Bxor;
assign C[0] = M;
genvar i;
generate
	for (i=0;i<32;i=i+1)
	begin : label
		assign Bxor[i] = B[i]^M; 
		FA f(A[i], Bxor[i], C[i], C[i+1], S[i]);
	end
endgenerate
assign Cout = C[32]^C[31];
endmodule
