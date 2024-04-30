main:
addi s1,zero,0
addi so,zero,1
addi,to,zero,10
for: 
	bge s0,t0,done
	add s1,s1,s0
	slli s0,s0,1
	j for
done: 
ecall