addi s1, zero, 5
Fib:
	addi s2, zero, 0
	addi s3, zero, 1
	beq s1,zero, break
	addi t0, zero, 2
	Loop:
		add s4, s2, s3
		addi s2, s3, 0
		sub s3, s4, zero
		addi t0, t0, 1
		bge t0, s1, break2
		blt t0, s1, Loop
	break:
		addi x1, s2, 0
	break2:
		addi x1, s3, 0

ecall
