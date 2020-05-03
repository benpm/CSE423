.globl globalA
.data
.align 8
.type globalA, @object
.size globalA, 8
globalA: .quad 6874729
.globl globalB
.data
.align 8
.type globalB, @object
.size globalB, 8
globalB: .quad 222222
.text
.globl funA
.type funA, @function
.data
# FUNCTION funA
# param (int)x at 16(%rbp)
# param (int)y at 24(%rbp)
# param (int)z at 32(%rbp)
.text
funA:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)i at -8(%rbp)
	pushq $0 # (int)#0 at -16(%rbp)
	pushq $0 # (int)#1 at -24(%rbp)
	pushq $0 # (int)j at -32(%rbp)
	pushq $0 # (int)k at -40(%rbp)
	pushq $0 # (int)zzzz at -48(%rbp)
	pushq $0 # (int)#2 at -56(%rbp)
	pushq $0 # (int)#3 at -64(%rbp)
	pushq $0 # (int)#4 at -72(%rbp)
.funA.0:
# (6) <[int][ADD], (int)i, (int)x, (int)x>
	movq -8(%rbp), %rax
	movq 16(%rbp), %rbx
	addq %rbx, %rbx
	movq %rbx, -8(%rbp)
# (7) <[int][MINUS], (int)#0, (int)z>
	movq -16(%rbp), %rax
	movq 32(%rbp), %rbx
	negq %rbx
	movq %rbx, -16(%rbp)
# (7) <[int][ADD], (int)#1, (int)x, (int)#0>
	movq -24(%rbp), %rax
	movq 16(%rbp), %rbx
	movq -16(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -24(%rbp)
# (7) <[int][MUL], (int)j, (int)y, (int)#1>
	movq -32(%rbp), %rax
	movq 24(%rbp), %rbx
	movq -24(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -32(%rbp)
# (8) <[int][MUL], (int)#0, (int)i, (int)j>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	movq -32(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (8) <[int][MUL], (int)k, (int)#0, (int)j>
	movq -40(%rbp), %rax
	movq -16(%rbp), %rbx
	movq -32(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -40(%rbp)
# (9) <[JUMP_EQ], <4>, (int)z, 0>
	movq 32(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	je .funA.4
# (9) <[JUMP], <5>>
	jmp .funA.5
.funA.4:
# (10) <[int][ASSIGN], (int)z, 1>
	movq $1, 32(%rbp)
.funA.5:
# (12) <[int][MINUS], (int)#0, (int)z>
	movq -16(%rbp), %rax
	movq 32(%rbp), %rbx
	negq %rbx
	movq %rbx, -16(%rbp)
# (12) <[int][MOD], (int)#1, (int)x, (int)#0>
	movq 16(%rbp), %rax
	movq -24(%rbp), %rbx
	movq -16(%rbp), %rcx
	cqo 
	idivq %rcx
	movq %rdx, -24(%rbp) # save remainder
# (12) <[int][MUL], (int)j, (int)y, (int)#1>
	movq -32(%rbp), %rax
	movq 24(%rbp), %rbx
	movq -24(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -32(%rbp)
# (14) <[int][ASSIGN], (int)zzzz, 0>
	movq $0, -48(%rbp)
.funA.7:
# (14) <[JUMP_NEQ], <8>, (int)zzzz, (int)globalB>
	movq -48(%rbp), %rax
	movq globalB(%rip), %rbx
	cmpq %rbx, %rax
	jne .funA.8
# (14) <[JUMP], <28>>
	jmp .funA.28
.funA.8:
# (15) <[JUMP_GE], <15>, (int)i, (int)j>
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	cmpq %rbx, %rax
	jge .funA.15
.funA.9:
# (15) <[JUMP_EQ], <13>, (int)j, (int)k>
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	cmpq %rbx, %rax
	je .funA.13
.funA.10:
# (15) <[JUMP_GE], <13>, (int)i, (int)k>
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	cmpq %rbx, %rax
	jge .funA.13
.funA.11:
# (15) <[JUMP], <15>>
	jmp .funA.15
.funA.12:
# (15) <[JUMP], <13>>
	jmp .funA.13
.funA.13:
# (16) <[int][ADD], (int)i, (int)i, 10>
	movq -8(%rbp), %rax
	movq $10, %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (17) <[int][MINUS], (int)globalA, (int)globalA, 7>
	movq globalA(%rip), %rax
	negq %rax
	movq %rax, globalA(%rip)
# (17) <[JUMP], <17>>
	jmp .funA.17
.funA.15:
# (19) <[int][ADD], (int)i, (int)i, 2>
	movq -8(%rbp), %rax
	movq $2, %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (20) <[int][MUL], (int)#0, 10, (int)globalB>
	movq -16(%rbp), %rax
	movq $10, %rbx
	movq globalB(%rip), %rcx
	imulq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (20) <[int][ADD], (int)globalA, (int)globalA, (int)#0>
	movq globalA(%rip), %rax
	movq -16(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, globalA(%rip)
.funA.17:
# (22) <[JUMP_GT], <18>, (int)i, 100>
	movq -8(%rbp), %rax
	movq $100, %rbx
	cmpq %rbx, %rax
	jg .funA.18
# (22) <[JUMP], <21>>
	jmp .funA.21
.funA.18:
# (24) <[int][ADD], (int)#0, (int)k, (int)x>
	movq -16(%rbp), %rax
	movq -40(%rbp), %rbx
	movq 16(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (24) <[int][SUB], (int)#1, (int)#0, (int)z>
	movq -24(%rbp), %rax
	movq -16(%rbp), %rbx
	movq 32(%rbp), %rcx
	subq %rcx, %rbx
	movq %rbx, -24(%rbp)
# (24) <[int][ADD], (int)#2, (int)#1, (int)globalB>
	movq -56(%rbp), %rax
	movq -24(%rbp), %rbx
	movq globalB(%rip), %rcx
	addq %rbx, %rcx
	movq %rcx, -56(%rbp)
# (24) <[JUMP_NEQ], <19>, (int)#2, 0>
	movq -56(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	jne .funA.19
# (24) <[JUMP], <20>>
	jmp .funA.20
.funA.19:
# (25) <[int][MUL], (int)#0, (int)i, (int)j>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	movq -32(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (25) <[int][ADD], (int)#1, (int)k, (int)x>
	movq -24(%rbp), %rax
	movq -40(%rbp), %rbx
	movq 16(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -24(%rbp)
# (25) <[int][SUB], (int)#2, (int)#1, (int)z>
	movq -56(%rbp), %rax
	movq -24(%rbp), %rbx
	movq 32(%rbp), %rcx
	subq %rcx, %rbx
	movq %rbx, -56(%rbp)
# (25) <[int][ADD], (int)#3, (int)#2, (int)globalB>
	movq -64(%rbp), %rax
	movq -56(%rbp), %rbx
	movq globalB(%rip), %rcx
	addq %rbx, %rcx
	movq %rcx, -64(%rbp)
# (25) <[int][DIV], (int)#4, (int)#0, (int)#3>
	movq -16(%rbp), %rax
	movq -72(%rbp), %rbx
	movq -64(%rbp), %rcx
	cqo 
	idivq %rcx
	movq %rax, -72(%rbp) # save quotient
# (25) <[int][RETURN], (int)#4>
	movq -72(%rbp), %rax
# stack size is 80
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
# (25) <[JUMP], <21>>
	jmp .funA.21
.funA.20:
# (27) <[int][MUL], (int)#0, (int)i, (int)j>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	movq -32(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (27) <[int][ADD], (int)#1, (int)k, (int)x>
	movq -24(%rbp), %rax
	movq -40(%rbp), %rbx
	movq 16(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -24(%rbp)
# (27) <[int][SUB], (int)#2, (int)#1, (int)z>
	movq -56(%rbp), %rax
	movq -24(%rbp), %rbx
	movq 32(%rbp), %rcx
	subq %rcx, %rbx
	movq %rbx, -56(%rbp)
# (27) <[int][ADD], (int)#3, (int)#2, (int)globalA>
	movq -64(%rbp), %rax
	movq -56(%rbp), %rbx
	movq globalA(%rip), %rcx
	addq %rbx, %rcx
	movq %rcx, -64(%rbp)
# (27) <[int][ADD], (int)#4, (int)#0, (int)#3>
	movq -72(%rbp), %rax
	movq -16(%rbp), %rbx
	movq -64(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -72(%rbp)
# (27) <[int][RETURN], (int)#4>
	movq -72(%rbp), %rax
# stack size is 80
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.funA.21:
# (30) <[int][MINUS], (int)#0, 100>
	movq -16(%rbp), %rax
	movq $100, %rbx
	negq %rbx
	movq %rbx, -16(%rbp)
# (30) <[JUMP_LT], <22>, (int)i, (int)#0>
	movq -8(%rbp), %rax
	movq -16(%rbp), %rbx
	cmpq %rbx, %rax
	jl .funA.22
# (30) <[JUMP], <24>>
	jmp .funA.24
.funA.22:
# (32) <[int][MINUS], (int)globalB, (int)globalB, 2>
	movq globalB(%rip), %rax
	negq %rax
	movq %rax, globalB(%rip)
# (33) <[JUMP], <28>>
	jmp .funA.28
.funA.24:
# (35) <[JUMP_EQ], <25>, (int)i, 0>
	movq -8(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	je .funA.25
# (35) <[JUMP], <27>>
	jmp .funA.27
.funA.25:
# (37) <[int][ADD], (int)#0, (int)globalB, (int)i>
	movq -16(%rbp), %rax
	movq globalB(%rip), %rbx
	movq -8(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (37) <[int][MUL], (int)globalA, (int)globalA, (int)#0>
	movq globalA(%rip), %rax
	movq -16(%rbp), %rbx
	imulq %rax, %rbx
	movq %rbx, globalA(%rip)
# (38) <[JUMP], <29>>
	jmp .funA.29
.funA.27:
# (14) <[int][ADD], (int)zzzz, (int)zzzz, 2>
	movq -48(%rbp), %rax
	movq $2, %rbx
	addq %rax, %rbx
	movq %rbx, -48(%rbp)
# (14) <[JUMP], <7>>
	jmp .funA.7
.funA.28:
# (41) <[int][MINUS], (int)#0, (int)i>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	negq %rbx
	movq %rbx, -16(%rbp)
# (41) <[int][MUL], (int)#1, (int)#0, (int)j>
	movq -24(%rbp), %rax
	movq -16(%rbp), %rbx
	movq -32(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -24(%rbp)
# (41) <[int][MUL], (int)#2, (int)z, (int)#1>
	movq -56(%rbp), %rax
	movq 32(%rbp), %rbx
	movq -24(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -56(%rbp)
# (41) <[int][RETURN], (int)#2>
	movq -56(%rbp), %rax
# stack size is 80
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.funA.29:
# (42) <[NO_OP]>
# (43) <[int][ADD], (int)#0, (int)globalA, (int)globalB>
	movq -16(%rbp), %rax
	movq globalA(%rip), %rbx
	movq globalB(%rip), %rcx
	addq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (43) <[int][RETURN], (int)#0>
	movq -16(%rbp), %rax
# stack size is 80
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.text
.globl funB
.type funB, @function
.data
# FUNCTION funB
# param (int)f at 16(%rbp)
.text
funB:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)#0 at -8(%rbp)
	pushq $0 # (int)#1 at -16(%rbp)
	pushq $0 # (int)#2 at -24(%rbp)
	pushq $0 # (int)#3 at -32(%rbp)
	pushq $0 # (int)#4 at -40(%rbp)
	pushq $0 # (int)#5 at -48(%rbp)
	pushq $0 # (int)#6 at -56(%rbp)
	pushq $0 # (int)#7 at -64(%rbp)
	pushq $0 # (int)z at -72(%rbp)
	pushq $0 # (int)g at -80(%rbp)
.funB.0:
# (48) <[int][MINUS], (int)f, (int)f, 1>
	movq 16(%rbp), %rax
	negq %rax
	movq %rax, 16(%rbp)
# (49) <[JUMP_LT], <5>, (int)f, 10>
	movq 16(%rbp), %rax
	movq $10, %rbx
	cmpq %rbx, %rax
	jl .funB.5
.funB.2:
# (49) <[JUMP_GE], <5>, (int)f, 23>
	movq 16(%rbp), %rax
	movq $23, %rbx
	cmpq %rbx, %rax
	jge .funB.5
.funB.3:
# (49) <[JUMP], <4>>
	jmp .funB.4
.funB.4:
# (51) <[int][DIV], (int)#0, (int)f, 2>
	movq 16(%rbp), %rax
	movq -8(%rbp), %rbx
	movq $2, %rcx
	cqo 
	idivq %rcx
	movq %rax, -8(%rbp) # save quotient
# (51) <[int][CALL], (int)#1, funB, (int)#0>
	pushq -8(%rbp)
	movq -16(%rbp), %rax
	call funB
	addq $8, %rsp
	movq %rax, -16(%rbp)
# (51) <[int][MINUS], (int)#2, 123>
	movq -24(%rbp), %rax
	movq $123, %rbx
	negq %rbx
	movq %rbx, -24(%rbp)
# (51) <[int][MUL], (int)#3, (int)f, 2>
	movq -32(%rbp), %rax
	movq 16(%rbp), %rbx
	movq $2, %rcx
	imulq %rbx, %rcx
	movq %rcx, -32(%rbp)
# (51) <[int][MUL], (int)#4, (int)#3, (int)f>
	movq -40(%rbp), %rax
	movq -32(%rbp), %rbx
	movq 16(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -40(%rbp)
# (51) <[int][SUB], (int)#5, (int)#4, (int)f>
	movq -48(%rbp), %rax
	movq -40(%rbp), %rbx
	movq 16(%rbp), %rcx
	subq %rcx, %rbx
	movq %rbx, -48(%rbp)
# (51) <[int][CALL], (int)#6, funA, (int)#2, 23, (int)#5>
	pushq -48(%rbp)
	pushq $23
	pushq -24(%rbp)
	movq -56(%rbp), %rax
	call funA
	addq $24, %rsp
	movq %rax, -56(%rbp)
# (51) <[int][ADD], (int)#7, (int)#1, (int)#6>
	movq -64(%rbp), %rax
	movq -16(%rbp), %rbx
	movq -56(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -64(%rbp)
# (51) <[int][RETURN], (int)#7>
	movq -64(%rbp), %rax
# stack size is 88
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.funB.5:
# (52) <[JUMP_GE], <9>, (int)f, 10>
	movq 16(%rbp), %rax
	movq $10, %rbx
	cmpq %rbx, %rax
	jge .funB.9
.funB.6:
# (52) <[int][MINUS], (int)#0, 10>
	movq -8(%rbp), %rax
	movq $10, %rbx
	negq %rbx
	movq %rbx, -8(%rbp)
# (52) <[JUMP_LE], <9>, (int)f, (int)#0>
	movq 16(%rbp), %rax
	movq -8(%rbp), %rbx
	cmpq %rbx, %rax
	jle .funB.9
.funB.7:
# (52) <[JUMP], <8>>
	jmp .funB.8
.funB.8:
# (54) <[int][ADD], (int)#0, (int)globalA, 69>
	movq -8(%rbp), %rax
	movq globalA(%rip), %rbx
	movq $69, %rcx
	addq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (54) <[int][RETURN], (int)#0>
	movq -8(%rbp), %rax
# stack size is 88
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.funB.9:
# (55) <[JUMP_GE], <24>, (int)f, 10>
	movq 16(%rbp), %rax
	movq $10, %rbx
	cmpq %rbx, %rax
	jge .funB.24
.funB.10:
# (55) <[int][MINUS], (int)#0, 100>
	movq -8(%rbp), %rax
	movq $100, %rbx
	negq %rbx
	movq %rbx, -8(%rbp)
# (55) <[JUMP_LE], <24>, (int)f, (int)#0>
	movq 16(%rbp), %rax
	movq -8(%rbp), %rbx
	cmpq %rbx, %rax
	jle .funB.24
.funB.11:
# (55) <[JUMP], <13>>
	jmp .funB.13
.funB.12:
# (56) <[int][ASSIGN], (int)z, 100>
	movq $100, -72(%rbp)
.funB.13:
# (57) <[int][MUL], (int)#0, (int)f, (int)f>
	movq -8(%rbp), %rax
	movq 16(%rbp), %rbx
	imulq %rbx, %rbx
	movq %rbx, -8(%rbp)
# (57) <[int][ADD], (int)f, (int)f, (int)#0>
	movq 16(%rbp), %rax
	movq -8(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, 16(%rbp)
.funB.14:
# (59) <[int][MUL], (int)#0, (int)z, 0>
	movq -8(%rbp), %rax
	movq -72(%rbp), %rbx
	movq $0, %rcx
	imulq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (59) <[JUMP_NEQ], <15>, (int)z, (int)#0>
	movq -72(%rbp), %rax
	movq -8(%rbp), %rbx
	cmpq %rbx, %rax
	jne .funB.15
# (59) <[JUMP], <24>>
	jmp .funB.24
.funB.15:
# (60) <[int][CALL], (int)#0, funA, 10, 20, (int)f>
	pushq 16(%rbp)
	pushq $20
	pushq $10
	movq -8(%rbp), %rax
	call funA
	addq $24, %rsp
	movq %rax, -8(%rbp)
# (60) <[int][MINUS], (int)z, (int)z, (int)#0>
	movq -72(%rbp), %rax
	negq %rax
	movq %rax, -72(%rbp)
# (61) <[JUMP_LT], <17>, (int)z, 10>
	movq -72(%rbp), %rax
	movq $10, %rbx
	cmpq %rbx, %rax
	jl .funB.17
# (61) <[JUMP], <22>>
	jmp .funB.22
.funB.17:
# (62) <[int][ASSIGN], (int)g, (int)f>
	movq 16(%rbp), -80(%rbp)
.funB.18:
# (62) <[int][MUL], (int)#0, (int)f, 2>
	movq -8(%rbp), %rax
	movq 16(%rbp), %rbx
	movq $2, %rcx
	imulq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (62) <[JUMP_LT], <19>, (int)g, (int)#0>
	movq -80(%rbp), %rax
	movq -8(%rbp), %rbx
	cmpq %rbx, %rax
	jl .funB.19
# (62) <[JUMP], <21>>
	jmp .funB.21
.funB.19:
# (63) <[int][MOD], (int)#0, 420, (int)z>
	movq $420, %rax
	movq -8(%rbp), %rbx
	movq -72(%rbp), %rcx
	cqo 
	idivq %rcx
	movq %rdx, -8(%rbp) # save remainder
# (63) <[int][CALL], (int)#1, funA, 2, 2, 2>
	pushq $2
	pushq $2
	pushq $2
	movq -16(%rbp), %rax
	call funA
	addq $24, %rsp
	movq %rax, -16(%rbp)
# (63) <[int][ADD], (int)#2, (int)#0, (int)#1>
	movq -24(%rbp), %rax
	movq -8(%rbp), %rbx
	movq -16(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -24(%rbp)
# (63) <[int][ADD], (int)z, (int)z, (int)#2>
	movq -72(%rbp), %rax
	movq -24(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, -72(%rbp)
# (62) <[int][ADD], (int)g, (int)g, 1>
	movq -80(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -80(%rbp)
# (62) <[JUMP], <18>>
	jmp .funB.18
.funB.21:
# (65) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 88
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
# (65) <[JUMP], <23>>
	jmp .funB.23
.funB.22:
# (67) <[int][MUL], (int)#0, (int)globalA, 1>
	movq -8(%rbp), %rax
	movq globalA(%rip), %rbx
	movq $1, %rcx
	imulq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (67) <[int][MUL], (int)#1, (int)#0, 123>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	movq $123, %rcx
	imulq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (67) <[int][RETURN], (int)#1>
	movq -16(%rbp), %rax
# stack size is 88
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.funB.23:
# (59) <[JUMP], <14>>
	jmp .funB.14
# (59) <[JUMP], <26>>
	jmp .funB.26
.funB.24:
# (72) <[JUMP_NEQ], <25>, (int)f, 0>
	movq 16(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	jne .funB.25
# (72) <[JUMP], <26>>
	jmp .funB.26
.funB.25:
# (73) <[int][MUL], (int)#0, (int)f, (int)f>
	movq -8(%rbp), %rax
	movq 16(%rbp), %rbx
	imulq %rbx, %rbx
	movq %rbx, -8(%rbp)
# (73) <[int][MINUS], (int)#1, (int)globalB>
	movq -16(%rbp), %rax
	movq globalB(%rip), %rbx
	negq %rbx
	movq %rbx, -16(%rbp)
# (73) <[int][SUB], (int)#2, 0, (int)#1>
	movq -24(%rbp), %rax
	movq $0, %rbx
	movq -16(%rbp), %rcx
	subq %rcx, %rbx
	movq %rbx, -24(%rbp)
# (73) <[int][ADD], (int)#3, (int)#0, (int)#2>
	movq -32(%rbp), %rax
	movq -8(%rbp), %rbx
	movq -24(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -32(%rbp)
# (73) <[int][RETURN], (int)#3>
	movq -32(%rbp), %rax
# stack size is 88
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.funB.26:
# (77) <[int][SUB], (int)#0, (int)f, 1>
	movq -8(%rbp), %rax
	movq 16(%rbp), %rbx
	movq $1, %rcx
	subq %rcx, %rbx
	movq %rbx, -8(%rbp)
# (77) <[int][CALL], (int)#1, funB, (int)#0>
	pushq -8(%rbp)
	movq -16(%rbp), %rax
	call funB
	addq $8, %rsp
	movq %rax, -16(%rbp)
# (77) <[int][RETURN], (int)#1>
	movq -16(%rbp), %rax
# stack size is 88
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.text
.globl main
.type main, @function
.data
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)accum at -8(%rbp)
	pushq $0 # (int)i at -16(%rbp)
	pushq $0 # (int)j at -24(%rbp)
	pushq $0 # (int)k at -32(%rbp)
	pushq $0 # (int)val at -40(%rbp)
.main.0:
# (82) <[int][ASSIGN], (int)accum, 0>
	movq $0, -8(%rbp)
# (83) <[int][MINUS], (int)i, 100>
	movq -16(%rbp), %rax
	movq $100, %rbx
	negq %rbx
	movq %rbx, -16(%rbp)
.main.2:
# (83) <[JUMP_LT], <3>, (int)i, 100>
	movq -16(%rbp), %rax
	movq $100, %rbx
	cmpq %rbx, %rax
	jl .main.3
# (83) <[JUMP], <12>>
	jmp .main.12
.main.3:
# (84) <[int][MINUS], (int)j, 100>
	movq -24(%rbp), %rax
	movq $100, %rbx
	negq %rbx
	movq %rbx, -24(%rbp)
.main.4:
# (84) <[JUMP_LT], <5>, (int)j, 100>
	movq -24(%rbp), %rax
	movq $100, %rbx
	cmpq %rbx, %rax
	jl .main.5
# (84) <[JUMP], <11>>
	jmp .main.11
.main.5:
# (85) <[int][MINUS], (int)k, 100>
	movq -32(%rbp), %rax
	movq $100, %rbx
	negq %rbx
	movq %rbx, -32(%rbp)
.main.6:
# (85) <[JUMP_LT], <7>, (int)k, 100>
	movq -32(%rbp), %rax
	movq $100, %rbx
	cmpq %rbx, %rax
	jl .main.7
# (85) <[JUMP], <10>>
	jmp .main.10
.main.7:
# (86) <[int][CALL], (int)val, funA, (int)i, (int)j, (int)k>
	pushq -32(%rbp)
	pushq -24(%rbp)
	pushq -16(%rbp)
	movq -40(%rbp), %rax
	call funA
	addq $24, %rsp
	movq %rax, -40(%rbp)
# (88) <[int][ADD], (int)accum, (int)accum, (int)val>
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (85) <[int][ADD], (int)k, (int)k, 1>
	movq -32(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -32(%rbp)
# (85) <[JUMP], <6>>
	jmp .main.6
.main.10:
# (84) <[int][ADD], (int)j, (int)j, 1>
	movq -24(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -24(%rbp)
# (84) <[JUMP], <4>>
	jmp .main.4
.main.11:
# (83) <[int][ADD], (int)i, (int)i, 1>
	movq -16(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -16(%rbp)
# (83) <[JUMP], <2>>
	jmp .main.2
.main.12:
# (92) <[int][MINUS], (int)i, 100>
	movq -16(%rbp), %rax
	movq $100, %rbx
	negq %rbx
	movq %rbx, -16(%rbp)
.main.13:
# (92) <[JUMP_LT], <14>, (int)i, 100>
	movq -16(%rbp), %rax
	movq $100, %rbx
	cmpq %rbx, %rax
	jl .main.14
# (92) <[JUMP], <17>>
	jmp .main.17
.main.14:
# (93) <[int][CALL], (int)val, funB, (int)i>
	pushq -16(%rbp)
	movq -40(%rbp), %rax
	call funB
	addq $8, %rsp
	movq %rax, -40(%rbp)
# (95) <[int][ADD], (int)accum, (int)accum, (int)val>
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (92) <[int][ADD], (int)i, (int)i, 1>
	movq -16(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -16(%rbp)
# (92) <[JUMP], <13>>
	jmp .main.13
.main.17:
# (97) <[int][RETURN], (int)accum>
	movq -8(%rbp), %rax
# stack size is 48
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
