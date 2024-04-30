main:
	addi s5, zero, 50
	addi s4, zero, 8000
	addi s3, zero, 8008
	addi t2, zero, 3
	sll t4, s5, t2
	srli t4, t4, 2
	srl t4, t4, t2
	sw s5, 0(s4)
	lui a0, 15
	auipc t6, 4090
	addi a7, zero, -50
	sw a7, 4(s3)
	jal ra, L3
L2:
	sub s5, s5, a0
	beq s4, a0, L5
	blt t6, zero, L2
	bne a0, a0, L4
	bltu a0, a0, L3
	bge t1, a0, L6
L3:
	lb t0, 0(s4)
	lh t1, 0(s4)
	sb t1, 0(s4)
	sh a0, 0(s3)
	bne s5, a0, L5
L4:
	slti t6, t0, 10
	sltu tp, t4, t2
	sltiu t6, t0, 10
	slli t6, t6, 31
	ori t6, t6, 1
	lbu a5, 4(s3)
	lhu a6, 4(s3)
	bgeu a0, a0, L2
L5:
	andi s5, s5, 0
	and s1, s5, a0
	lw a1, 0(s3)
	xor a1, a1, s5
	xori a1, a1, 5
	addi a2, zero, 15
	add a2, zero, a2
	sra a3, a2, a1
	srai a4, a2, 5
	or t3, s5, s5
	bge t6, zero, L4
L6:
	add s0, zero, s5
	slt s0, s0, a0
	jalr zero, 0(ra)
	ecall