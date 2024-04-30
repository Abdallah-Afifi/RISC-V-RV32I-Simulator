	addi s8, zero, 22 #k = 22
	addi s6, zero, 0 #i = 0
	addi s9, zero, 8000 #base address of Array A in s9
Loop: 
	slli a0, s6, 2 #multiplying by 4
	add a0, a0, s9 #adding value of a0 in s9 to get address A[i] in a0
	lw s1, 0(a0) #loading the value from address a0 to register s1
	bne s1, s8, Exit #checks if A[i] is not equal to k, if so it jumps to exit
	addi s6, s6, 1 #increment s6 by 1
	jal ra, Loop #for looping until conditioned met 
Exit: 
	ecall #terminates 