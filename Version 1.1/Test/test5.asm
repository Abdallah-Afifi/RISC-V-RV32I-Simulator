aaddi s0,zero,1  #int pow=1;
addi s1,zerp 0  #int x=0;
add t0,zero,128
while: 
	beg,s0,t0,end #if pow=128 end loop
	mul s0,s0,2 #pow=pow*2
	addi s1,s1,1 #x++
	j while
end: 
	jalr zero
ecall