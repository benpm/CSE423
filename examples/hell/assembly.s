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
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)i
	push $0 # (int)#0
	push $0 # (int)#1
	push $0 # (int)j
	push $0 # (int)k
	push $0 # (int)zzzz
	push $0 # (int)#2
	push $0 # (int)#3
	push $0 # (int)#4
.funA.0:
# (6) <[int][ADD], (int)i, (int)x, (int)x>
	mov -8(%rbp), %rax
	mov 16(%rbp), %rbx
	add %rbx, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (7) <[int][MINUS], (int)#0, (int)z>
	mov -16(%rbp), %rax
	mov 32(%rbp), %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (7) <[int][ADD], (int)#1, (int)x, (int)#0>
	mov -24(%rbp), %rax
	mov 16(%rbp), %rbx
	mov -16(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (7) <[int][MUL], (int)j, (int)y, (int)#1>
	mov -32(%rbp), %rax
	mov 24(%rbp), %rbx
	mov -24(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -32(%rbp)
# (8) <[int][MUL], (int)#0, (int)i, (int)j>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov -32(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (8) <[int][MUL], (int)k, (int)#0, (int)j>
	mov -40(%rbp), %rax
	mov -16(%rbp), %rbx
	mov -32(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -40(%rbp)
# (9) <[JUMP_EQ], <4>, (int)z, 0>
	mov 32(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .funA.4
# (9) <[JUMP], <5>>
	jmp .funA.5
.funA.4:
# (10) <[int][ASSIGN], (int)z, 1>
	mov 32(%rbp), %rax
	mov $1, %rbx
	mov %rbx, %rax
	mov %rax, 32(%rbp)
.funA.5:
# (12) <[int][MINUS], (int)#0, (int)z>
	mov -16(%rbp), %rax
	mov 32(%rbp), %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (12) <[int][MOD], (int)#1, (int)x, (int)#0>
	mov 16(%rbp), %rax
	mov -24(%rbp), %rbx
	mov -16(%rbp), %rcx
	cqo 
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -24(%rbp)
# (12) <[int][MUL], (int)j, (int)y, (int)#1>
	mov -32(%rbp), %rax
	mov 24(%rbp), %rbx
	mov -24(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -32(%rbp)
# (14) <[int][ASSIGN], (int)zzzz, 0>
	mov -48(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -48(%rbp)
.funA.7:
# (14) <[JUMP_NEQ], <8>, (int)zzzz, (int)globalB>
	mov -48(%rbp), %rax
	mov globalB(%rip), %rbx
	cmp %rbx, %rax
	jne .funA.8
# (14) <[JUMP], <28>>
	jmp .funA.28
.funA.8:
# (15) <[JUMP_GE], <15>, (int)i, (int)j>
	mov -8(%rbp), %rax
	mov -32(%rbp), %rbx
	cmp %rbx, %rax
	jge .funA.15
.funA.9:
# (15) <[JUMP_EQ], <13>, (int)j, (int)k>
	mov -32(%rbp), %rax
	mov -40(%rbp), %rbx
	cmp %rbx, %rax
	je .funA.13
.funA.10:
# (15) <[JUMP_GE], <13>, (int)i, (int)k>
	mov -8(%rbp), %rax
	mov -40(%rbp), %rbx
	cmp %rbx, %rax
	jge .funA.13
.funA.11:
# (15) <[JUMP], <15>>
	jmp .funA.15
.funA.12:
# (15) <[JUMP], <13>>
	jmp .funA.13
.funA.13:
# (16) <[int][ADD], (int)i, (int)i, 10>
	mov -8(%rbp), %rax
	mov $10, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (17) <[int][MINUS], (int)globalA, (int)globalA, 7>
	mov globalA(%rip), %rax
	neg %rax
	mov %rax, %rax
	mov %rax, globalA(%rip)
.funA.15:
# (19) <[int][ADD], (int)i, (int)i, 2>
	mov -8(%rbp), %rax
	mov $2, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (20) <[int][MUL], (int)#0, 10, (int)globalB>
	mov -16(%rbp), %rax
	mov $10, %rbx
	mov globalB(%rip), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (20) <[int][ADD], (int)globalA, (int)globalA, (int)#0>
	mov globalA(%rip), %rax
	mov -16(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, globalA(%rip)
# (22) <[JUMP_GT], <18>, (int)i, 100>
	mov -8(%rbp), %rax
	mov $100, %rbx
	cmp %rbx, %rax
	jg .funA.18
# (22) <[JUMP], <21>>
	jmp .funA.21
.funA.18:
# (24) <[int][ADD], (int)#0, (int)k, (int)x>
	mov -16(%rbp), %rax
	mov -40(%rbp), %rbx
	mov 16(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (24) <[int][SUB], (int)#1, (int)#0, (int)z>
	mov -24(%rbp), %rax
	mov -16(%rbp), %rbx
	mov 32(%rbp), %rcx
	sub %rcx, %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
# (24) <[int][ADD], (int)#2, (int)#1, (int)globalB>
	mov -56(%rbp), %rax
	mov -24(%rbp), %rbx
	mov globalB(%rip), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -56(%rbp)
# (24) <[JUMP_NEQ], <19>, (int)#2, 0>
	mov -56(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	jne .funA.19
# (24) <[JUMP], <20>>
	jmp .funA.20
.funA.19:
# (25) <[int][MUL], (int)#0, (int)i, (int)j>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov -32(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (25) <[int][ADD], (int)#1, (int)k, (int)x>
	mov -24(%rbp), %rax
	mov -40(%rbp), %rbx
	mov 16(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (25) <[int][SUB], (int)#2, (int)#1, (int)z>
	mov -56(%rbp), %rax
	mov -24(%rbp), %rbx
	mov 32(%rbp), %rcx
	sub %rcx, %rbx
	mov %rbx, %rax
	mov %rax, -56(%rbp)
# (25) <[int][ADD], (int)#3, (int)#2, (int)globalB>
	mov -64(%rbp), %rax
	mov -56(%rbp), %rbx
	mov globalB(%rip), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -64(%rbp)
# (25) <[int][DIV], (int)#4, (int)#0, (int)#3>
	mov -16(%rbp), %rax
	mov -72(%rbp), %rbx
	mov -64(%rbp), %rcx
	cqo 
	idiv %rcx
	mov %rax, %rbx # save quotient
	mov %rbx, -72(%rbp)
# (25) <[int][RETURN], (int)#4>
	mov -72(%rbp), %rax
# stack size is 80
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.funA.20:
# (27) <[int][MUL], (int)#0, (int)i, (int)j>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov -32(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (27) <[int][ADD], (int)#1, (int)k, (int)x>
	mov -24(%rbp), %rax
	mov -40(%rbp), %rbx
	mov 16(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (27) <[int][SUB], (int)#2, (int)#1, (int)z>
	mov -56(%rbp), %rax
	mov -24(%rbp), %rbx
	mov 32(%rbp), %rcx
	sub %rcx, %rbx
	mov %rbx, %rax
	mov %rax, -56(%rbp)
# (27) <[int][ADD], (int)#3, (int)#2, (int)globalA>
	mov -64(%rbp), %rax
	mov -56(%rbp), %rbx
	mov globalA(%rip), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -64(%rbp)
# (27) <[int][ADD], (int)#4, (int)#0, (int)#3>
	mov -72(%rbp), %rax
	mov -16(%rbp), %rbx
	mov -64(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -72(%rbp)
# (27) <[int][RETURN], (int)#4>
	mov -72(%rbp), %rax
# stack size is 80
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.funA.21:
# (30) <[int][MINUS], (int)#0, 100>
	mov -16(%rbp), %rax
	mov $100, %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (30) <[JUMP_LT], <22>, (int)i, (int)#0>
	mov -8(%rbp), %rax
	mov -16(%rbp), %rbx
	cmp %rbx, %rax
	jl .funA.22
# (30) <[JUMP], <24>>
	jmp .funA.24
.funA.22:
# (32) <[int][MINUS], (int)globalB, (int)globalB, 2>
	mov globalB(%rip), %rax
	neg %rax
	mov %rax, %rax
	mov %rax, globalB(%rip)
# (33) <[JUMP], <28>>
	jmp .funA.28
.funA.24:
# (35) <[JUMP_EQ], <25>, (int)i, 0>
	mov -8(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .funA.25
# (35) <[JUMP], <27>>
	jmp .funA.27
.funA.25:
# (37) <[int][ADD], (int)#0, (int)globalB, (int)i>
	mov -16(%rbp), %rax
	mov globalB(%rip), %rbx
	mov -8(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (37) <[int][MUL], (int)globalA, (int)globalA, (int)#0>
	mov globalA(%rip), %rax
	mov -16(%rbp), %rbx
	imul %rax, %rbx
	mov %rbx, %rax
	mov %rax, globalA(%rip)
# (38) <[JUMP], <29>>
	jmp .funA.29
.funA.27:
# (14) <[int][ADD], (int)zzzz, (int)zzzz, 2>
	mov -48(%rbp), %rax
	mov $2, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -48(%rbp)
# (14) <[JUMP], <7>>
	jmp .funA.7
.funA.28:
# (41) <[int][MINUS], (int)#0, (int)i>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (41) <[int][MUL], (int)#1, (int)#0, (int)j>
	mov -24(%rbp), %rax
	mov -16(%rbp), %rbx
	mov -32(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (41) <[int][MUL], (int)#2, (int)z, (int)#1>
	mov -56(%rbp), %rax
	mov 32(%rbp), %rbx
	mov -24(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -56(%rbp)
# (41) <[int][RETURN], (int)#2>
	mov -56(%rbp), %rax
# stack size is 80
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.funA.29:
# (42) <[NO_OP]>
# (43) <[int][ADD], (int)#0, (int)globalA, (int)globalB>
	mov -16(%rbp), %rax
	mov globalA(%rip), %rbx
	mov globalB(%rip), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (43) <[int][RETURN], (int)#0>
	mov -16(%rbp), %rax
# stack size is 80
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.text
.globl funB
.type funB, @function
.data
# FUNCTION funB
# param (int)f at 16(%rbp)
.text
funB:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)#0
	push $0 # (int)#1
	push $0 # (int)#2
	push $0 # (int)#3
	push $0 # (int)#4
	push $0 # (int)#5
	push $0 # (int)#6
	push $0 # (int)#7
	push $0 # (int)z
	push $0 # (int)g
.funB.0:
# (48) <[int][MINUS], (int)f, (int)f, 1>
	mov 16(%rbp), %rax
	neg %rax
	mov %rax, %rax
	mov %rax, 16(%rbp)
# (49) <[JUMP_LT], <5>, (int)f, 10>
	mov 16(%rbp), %rax
	mov $10, %rbx
	cmp %rbx, %rax
	jl .funB.5
.funB.2:
# (49) <[JUMP_GE], <5>, (int)f, 23>
	mov 16(%rbp), %rax
	mov $23, %rbx
	cmp %rbx, %rax
	jge .funB.5
.funB.3:
# (49) <[JUMP], <4>>
	jmp .funB.4
.funB.4:
# (51) <[int][DIV], (int)#0, (int)f, 2>
	mov 16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov $2, %rcx
	cqo 
	idiv %rcx
	mov %rax, %rbx # save quotient
	mov %rbx, -8(%rbp)
# (51) <[int][CALL], (int)#1, funB, (int)#0>
	push -8(%rbp)
	mov -16(%rbp), %rax
	call funB
	add $8, %rsp
	mov %rax, -16(%rbp)
# (51) <[int][MINUS], (int)#2, 123>
	mov -24(%rbp), %rax
	mov $123, %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
# (51) <[int][MUL], (int)#3, (int)f, 2>
	mov -32(%rbp), %rax
	mov 16(%rbp), %rbx
	mov $2, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -32(%rbp)
# (51) <[int][MUL], (int)#4, (int)#3, (int)f>
	mov -40(%rbp), %rax
	mov -32(%rbp), %rbx
	mov 16(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -40(%rbp)
# (51) <[int][SUB], (int)#5, (int)#4, (int)f>
	mov -48(%rbp), %rax
	mov -40(%rbp), %rbx
	mov 16(%rbp), %rcx
	sub %rcx, %rbx
	mov %rbx, %rax
	mov %rax, -48(%rbp)
# (51) <[int][CALL], (int)#6, funA, (int)#2, 23, (int)#5>
	push -48(%rbp)
	push $23
	push -24(%rbp)
	mov -56(%rbp), %rax
	call funA
	add $24, %rsp
	mov %rax, -56(%rbp)
# (51) <[int][ADD], (int)#7, (int)#1, (int)#6>
	mov -64(%rbp), %rax
	mov -16(%rbp), %rbx
	mov -56(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -64(%rbp)
# (51) <[int][RETURN], (int)#7>
	mov -64(%rbp), %rax
# stack size is 88
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.funB.5:
# (52) <[JUMP_GE], <9>, (int)f, 10>
	mov 16(%rbp), %rax
	mov $10, %rbx
	cmp %rbx, %rax
	jge .funB.9
.funB.6:
# (52) <[int][MINUS], (int)#0, 10>
	mov -8(%rbp), %rax
	mov $10, %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (52) <[JUMP_LE], <9>, (int)f, (int)#0>
	mov 16(%rbp), %rax
	mov -8(%rbp), %rbx
	cmp %rbx, %rax
	jle .funB.9
.funB.7:
# (52) <[JUMP], <8>>
	jmp .funB.8
.funB.8:
# (54) <[int][ADD], (int)#0, (int)globalA, 69>
	mov -8(%rbp), %rax
	mov globalA(%rip), %rbx
	mov $69, %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (54) <[int][RETURN], (int)#0>
	mov -8(%rbp), %rax
# stack size is 88
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.funB.9:
# (55) <[JUMP_GE], <24>, (int)f, 10>
	mov 16(%rbp), %rax
	mov $10, %rbx
	cmp %rbx, %rax
	jge .funB.24
.funB.10:
# (55) <[int][MINUS], (int)#0, 100>
	mov -8(%rbp), %rax
	mov $100, %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (55) <[JUMP_LE], <24>, (int)f, (int)#0>
	mov 16(%rbp), %rax
	mov -8(%rbp), %rbx
	cmp %rbx, %rax
	jle .funB.24
.funB.11:
# (55) <[JUMP], <13>>
	jmp .funB.13
.funB.12:
# (56) <[int][ASSIGN], (int)z, 100>
	mov -72(%rbp), %rax
	mov $100, %rbx
	mov %rbx, %rax
	mov %rax, -72(%rbp)
.funB.13:
# (57) <[int][MUL], (int)#0, (int)f, (int)f>
	mov -8(%rbp), %rax
	mov 16(%rbp), %rbx
	imul %rbx, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (57) <[int][ADD], (int)f, (int)f, (int)#0>
	mov 16(%rbp), %rax
	mov -8(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, 16(%rbp)
.funB.14:
# (59) <[int][MUL], (int)#0, (int)z, 0>
	mov -8(%rbp), %rax
	mov -72(%rbp), %rbx
	mov $0, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (59) <[JUMP_NEQ], <15>, (int)z, (int)#0>
	mov -72(%rbp), %rax
	mov -8(%rbp), %rbx
	cmp %rbx, %rax
	jne .funB.15
# (59) <[JUMP], <24>>
	jmp .funB.24
.funB.15:
# (60) <[int][CALL], (int)#0, funA, 10, 20, (int)f>
	push 16(%rbp)
	push $20
	push $10
	mov -8(%rbp), %rax
	call funA
	add $24, %rsp
	mov %rax, -8(%rbp)
# (60) <[int][MINUS], (int)z, (int)z, (int)#0>
	mov -72(%rbp), %rax
	neg %rax
	mov %rax, %rax
	mov %rax, -72(%rbp)
# (61) <[JUMP_LT], <17>, (int)z, 10>
	mov -72(%rbp), %rax
	mov $10, %rbx
	cmp %rbx, %rax
	jl .funB.17
# (61) <[JUMP], <22>>
	jmp .funB.22
.funB.17:
# (62) <[int][ASSIGN], (int)g, (int)f>
	mov -80(%rbp), %rax
	mov 16(%rbp), %rbx
	mov %rbx, %rax
	mov %rax, -80(%rbp)
.funB.18:
# (62) <[int][MUL], (int)#0, (int)f, 2>
	mov -8(%rbp), %rax
	mov 16(%rbp), %rbx
	mov $2, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (62) <[JUMP_LT], <19>, (int)g, (int)#0>
	mov -80(%rbp), %rax
	mov -8(%rbp), %rbx
	cmp %rbx, %rax
	jl .funB.19
# (62) <[JUMP], <21>>
	jmp .funB.21
.funB.19:
# (63) <[int][MOD], (int)#0, 420, (int)z>
	mov $420, %rax
	mov -8(%rbp), %rbx
	mov -72(%rbp), %rcx
	cqo 
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -8(%rbp)
# (63) <[int][CALL], (int)#1, funA, 2, 2, 2>
	push $2
	push $2
	push $2
	mov -16(%rbp), %rax
	call funA
	add $24, %rsp
	mov %rax, -16(%rbp)
# (63) <[int][ADD], (int)#2, (int)#0, (int)#1>
	mov -24(%rbp), %rax
	mov -8(%rbp), %rbx
	mov -16(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (63) <[int][ADD], (int)z, (int)z, (int)#2>
	mov -72(%rbp), %rax
	mov -24(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -72(%rbp)
# (62) <[int][ADD], (int)g, (int)g, 1>
	mov -80(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -80(%rbp)
# (62) <[JUMP], <18>>
	jmp .funB.18
.funB.21:
# (65) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 88
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.funB.22:
# (67) <[int][MUL], (int)#0, (int)globalA, 1>
	mov -8(%rbp), %rax
	mov globalA(%rip), %rbx
	mov $1, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (67) <[int][MUL], (int)#1, (int)#0, 123>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov $123, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (67) <[int][RETURN], (int)#1>
	mov -16(%rbp), %rax
# stack size is 88
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
# (59) <[JUMP], <14>>
	jmp .funB.14
.funB.24:
# (72) <[JUMP_NEQ], <25>, (int)f, 0>
	mov 16(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	jne .funB.25
# (72) <[JUMP], <26>>
	jmp .funB.26
.funB.25:
# (73) <[int][MUL], (int)#0, (int)f, (int)f>
	mov -8(%rbp), %rax
	mov 16(%rbp), %rbx
	imul %rbx, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (73) <[int][MINUS], (int)#1, (int)globalB>
	mov -16(%rbp), %rax
	mov globalB(%rip), %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (73) <[int][SUB], (int)#2, 0, (int)#1>
	mov -24(%rbp), %rax
	mov $0, %rbx
	mov -16(%rbp), %rcx
	sub %rcx, %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
# (73) <[int][ADD], (int)#3, (int)#0, (int)#2>
	mov -32(%rbp), %rax
	mov -8(%rbp), %rbx
	mov -24(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -32(%rbp)
# (73) <[int][RETURN], (int)#3>
	mov -32(%rbp), %rax
# stack size is 88
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.funB.26:
# (77) <[int][SUB], (int)#0, (int)f, 1>
	mov -8(%rbp), %rax
	mov 16(%rbp), %rbx
	mov $1, %rcx
	sub %rcx, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (77) <[int][CALL], (int)#1, funB, (int)#0>
	push -8(%rbp)
	mov -16(%rbp), %rax
	call funB
	add $8, %rsp
	mov %rax, -16(%rbp)
# (77) <[int][RETURN], (int)#1>
	mov -16(%rbp), %rax
# stack size is 88
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.text
.globl main
.type main, @function
.data
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)accum
	push $0 # (int)i
	push $0 # (int)j
	push $0 # (int)k
	push $0 # (int)val
.main.0:
# (82) <[int][ASSIGN], (int)accum, 0>
	mov -8(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (83) <[int][MINUS], (int)i, 100>
	mov -16(%rbp), %rax
	mov $100, %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
.main.2:
# (83) <[JUMP_LT], <3>, (int)i, 100>
	mov -16(%rbp), %rax
	mov $100, %rbx
	cmp %rbx, %rax
	jl .main.3
# (83) <[JUMP], <12>>
	jmp .main.12
.main.3:
# (84) <[int][MINUS], (int)j, 100>
	mov -24(%rbp), %rax
	mov $100, %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
.main.4:
# (84) <[JUMP_LT], <5>, (int)j, 100>
	mov -24(%rbp), %rax
	mov $100, %rbx
	cmp %rbx, %rax
	jl .main.5
# (84) <[JUMP], <11>>
	jmp .main.11
.main.5:
# (85) <[int][MINUS], (int)k, 100>
	mov -32(%rbp), %rax
	mov $100, %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -32(%rbp)
.main.6:
# (85) <[JUMP_LT], <7>, (int)k, 100>
	mov -32(%rbp), %rax
	mov $100, %rbx
	cmp %rbx, %rax
	jl .main.7
# (85) <[JUMP], <10>>
	jmp .main.10
.main.7:
# (86) <[int][CALL], (int)val, funA, (int)i, (int)j, (int)k>
	push -32(%rbp)
	push -24(%rbp)
	push -16(%rbp)
	mov -40(%rbp), %rax
	call funA
	add $24, %rsp
	mov %rax, -40(%rbp)
# (88) <[int][ADD], (int)accum, (int)accum, (int)val>
	mov -8(%rbp), %rax
	mov -40(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (85) <[int][ADD], (int)k, (int)k, 1>
	mov -32(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -32(%rbp)
# (85) <[JUMP], <6>>
	jmp .main.6
.main.10:
# (84) <[int][ADD], (int)j, (int)j, 1>
	mov -24(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
# (84) <[JUMP], <4>>
	jmp .main.4
.main.11:
# (83) <[int][ADD], (int)i, (int)i, 1>
	mov -16(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (83) <[JUMP], <2>>
	jmp .main.2
.main.12:
# (92) <[int][MINUS], (int)i, 100>
	mov -16(%rbp), %rax
	mov $100, %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
.main.13:
# (92) <[JUMP_LT], <14>, (int)i, 100>
	mov -16(%rbp), %rax
	mov $100, %rbx
	cmp %rbx, %rax
	jl .main.14
# (92) <[JUMP], <17>>
	jmp .main.17
.main.14:
# (93) <[int][CALL], (int)val, funB, (int)i>
	push -16(%rbp)
	mov -40(%rbp), %rax
	call funB
	add $8, %rsp
	mov %rax, -40(%rbp)
# (95) <[int][ADD], (int)accum, (int)accum, (int)val>
	mov -8(%rbp), %rax
	mov -40(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (92) <[int][ADD], (int)i, (int)i, 1>
	mov -16(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (92) <[JUMP], <13>>
	jmp .main.13
.main.17:
# (97) <[int][RETURN], (int)accum>
	mov -8(%rbp), %rax
# stack size is 48
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
