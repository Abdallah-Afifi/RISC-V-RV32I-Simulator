fact:
      addi  t1, zero, -3 # adjust stack for 2 items
      addi  t2, zero,  2
      mulhu   t3,t1,t2
      sw    ra, 4(sp) # save return address
      sw    a0, 0(sp) # save argument
      slti  t0,a0,1 # test for n < 1
      beq   t0, zero, L1
      addi  a0, zero, 1 # if so, result is 1
      addi  sp, sp, 8 # pop 2 items from stack
      jalr  zero, 0(ra) # and return
L1:  
      addi a0, a0, -1 # else decrement n
      jal  ra, fact # recursive call
      addi t0, a0, 0 # move result of fact(n-1)
      lw   a0, 0(sp) # restore original n
      lw   ra, 4(sp) # and return address
      addi sp, sp, 8 # pop 2 items from stack
      mul  a0, a0, t0 # multiply to get result
      jalr zero, 0(ra) # and return