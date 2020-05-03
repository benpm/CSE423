.globl globA
.data
.align 8
.type globA, @object
.size globA, 8
globA: .quad 3
.globl globB
.data
.align 8
.type globB, @object
.size globB, 8
globB: .quad 4
.text
.globl fun
.type fun, @function
.data
# FUNCTION fun
# param (int)V at 16(%rbp)
# param (int)XKAD at 24(%rbp)
.text
fun:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)n1 at -8(%rbp)
	pushq $0 # (int)#0 at -16(%rbp)
.fun.0:
# (6) <[int][ADD], (int)n1, (int)XKAD, (int)V>
	movq -8(%rbp), %rax
	movq 24(%rbp), %rbx
	movq 16(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (7) <[int][MUL], (int)#0, (int)n1, 80>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	movq $80, %rcx
	imulq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (7) <[int][RETURN], (int)#0>
	movq -16(%rbp), %rax
# stack size is 24
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "test: %f\n"
_string_main.1: .asciz "n1: %d, n2: %d, n3: %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)#0 at -8(%rbp)
	pushq $0 # (int)#1 at -16(%rbp)
	pushq $0 # (int)#2 at -24(%rbp)
	pushq $0 # (int)n1 at -32(%rbp)
	pushq $0 # (int)n2 at -40(%rbp)
	pushq $0 # (int)n3 at -48(%rbp)
	pushq $0 # (int)DF at -56(%rbp)
	pushq $0 # (int)i at -64(%rbp)
	pushq $0 # (int)f at -72(%rbp)
	pushq $0 # (int)j at -80(%rbp)
	pushq $0 # (int)x at -88(%rbp)
	pushq $0 # (int)z at -96(%rbp)
	pushq $0 # (int)x2 at -104(%rbp)
.main.0:
# (13) <[int][MINUS], (int)#0, 2>
	movq -8(%rbp), %rax
	movq $2, %rbx
	negq %rbx
	movq %rbx, -8(%rbp)
# (13) <[int][DIV], (int)#1, 18, (int)#0>
	movq $18, %rax
	movq -16(%rbp), %rbx
	movq -8(%rbp), %rcx
	cqo 
	idivq %rcx
	movq %rax, -16(%rbp) # save quotient
# (13) <[int][MUL], (int)#2, 15, (int)#1>
	movq -24(%rbp), %rax
	movq $15, %rbx
	movq -16(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -24(%rbp)
# (13) <[int][MOD], (int)n1, (int)#2, 18>
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	movq $18, %rcx
	cqo 
	idivq %rcx
	movq %rdx, -32(%rbp) # save remainder
# (14) <[int][MUL], (int)n2, (int)n1, (int)n1>
	movq -40(%rbp), %rax
	movq -32(%rbp), %rbx
	imulq %rbx, %rbx
	movq %rbx, -40(%rbp)
# (15) <[int][ADD], (int)#0, (int)n1, (int)n1>
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	addq %rbx, %rbx
	movq %rbx, -8(%rbp)
# (15) <[int][ADD], (int)#1, (int)#0, (int)n2>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	movq -40(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (15) <[int][ADD], (int)n3, (int)#1, (int)n2>
	movq -48(%rbp), %rax
	movq -16(%rbp), %rbx
	movq -40(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -48(%rbp)
# (16) <[int][MUL], (int)DF, 8, (int)n2>
	movq -56(%rbp), %rax
	movq $8, %rbx
	movq -40(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -56(%rbp)
# (19) <[int][ASSIGN], (int)i, 0>
	movq $0, -64(%rbp)
.main.5:
# (19) <[int][MUL], (int)#0, (int)n2, (int)n1>
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	movq -32(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (19) <[int][DIV], (int)#1, (int)#0, 2>
	movq -8(%rbp), %rax
	movq -16(%rbp), %rbx
	movq $2, %rcx
	cqo 
	idivq %rcx
	movq %rax, -16(%rbp) # save quotient
# (19) <[JUMP_LT], <6>, (int)i, (int)#1>
	movq -64(%rbp), %rax
	movq -16(%rbp), %rbx
	cmpq %rbx, %rax
	jl .main.6
# (19) <[JUMP], <22>>
	jmp .main.22
.main.6:
# (20) <[int][ASSIGN], (int)f, 10>
	movq $10, -72(%rbp)
# (21) <[JUMP], <22>>
	jmp .main.22
.main.8:
# (22) <[int][ASSIGN], (int)j, 0>
	movq $0, -80(%rbp)
.main.9:
# (22) <[int][DIV], (int)#0, (int)n1, 2>
	movq -32(%rbp), %rax
	movq -8(%rbp), %rbx
	movq $2, %rcx
	cqo 
	idivq %rcx
	movq %rax, -8(%rbp) # save quotient
# (22) <[int][ADD], (int)#1, (int)n2, (int)#0>
	movq -16(%rbp), %rax
	movq -40(%rbp), %rbx
	movq -8(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (22) <[JUMP_LT], <10>, (int)j, (int)#1>
	movq -80(%rbp), %rax
	movq -16(%rbp), %rbx
	cmpq %rbx, %rax
	jl .main.10
# (22) <[JUMP], <21>>
	jmp .main.21
.main.10:
# (23) <[int][ASSIGN], (int)x, 0>
	movq $0, -88(%rbp)
.main.11:
# (24) <[JUMP_LT], <14>, (int)x, (int)n2>
	movq -88(%rbp), %rax
	movq -40(%rbp), %rbx
	cmpq %rbx, %rax
	jl .main.14
.main.12:
# (24) <[JUMP_GE], <20>, (int)x, (int)n2>
	movq -88(%rbp), %rax
	movq -40(%rbp), %rbx
	cmpq %rbx, %rax
	jge .main.20
# (24) <[JUMP], <14>>
	jmp .main.14
.main.13:
# (24) <[JUMP], <20>>
	jmp .main.20
.main.14:
# (25) <[int][ASSIGN], (int)z, 10>
	movq $10, -96(%rbp)
# (26) <[int][ASSIGN], (int)x2, 3>
	movq $3, -104(%rbp)
# (27) <[int][ADD], (int)#0, (int)z, (int)x>
	movq -8(%rbp), %rax
	movq -96(%rbp), %rbx
	movq -88(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (27) <[int][ADD], (int)x2, (int)x2, (int)#0>
	movq -104(%rbp), %rax
	movq -8(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, -104(%rbp)
# (28) <[int][MINUS], (int)n2, (int)n2, (int)x>
	movq -40(%rbp), %rax
	negq %rax
	movq %rax, -40(%rbp)
# (29) <[JUMP], <20>>
	jmp .main.20
.main.19:
# (24) <[JUMP], <11>>
	jmp .main.11
.main.20:
# (22) <[int][ADD], (int)j, (int)j, 1>
	movq -80(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -80(%rbp)
# (22) <[JUMP], <9>>
	jmp .main.9
.main.21:
# (19) <[int][ADD], (int)i, (int)i, 1>
	movq -64(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -64(%rbp)
# (19) <[JUMP], <5>>
	jmp .main.5
.main.22:
# (35) <[int][MUL], (int)#0, 101, 2>
	movq -8(%rbp), %rax
	movq $101, %rbx
	movq $2, %rcx
	imulq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (35) <[int][CALL], (int)#1, fun, (int)DF, (int)#0>
	pushq -8(%rbp)
	pushq -56(%rbp)
	movq -16(%rbp), %rax
	call fun
	addq $16, %rsp
	movq %rax, -16(%rbp)
# (35) <[int][CALL], (int)DF, fun, (int)#1, 9>
	pushq $9
	pushq -16(%rbp)
	movq -56(%rbp), %rax
	call fun
	addq $16, %rsp
	movq %rax, -56(%rbp)
# (36) <[int][CALL], (int)#0, printf, "test: %f\n", (int)DF>
	leaq _string_main.0(%rip), %rdi
	movq -56(%rbp), %rsi
	movq $0, %rax
	call printf
# (38) <[int][MUL], (int)#0, (int)DF, (int)globA>
	movq -8(%rbp), %rax
	movq -56(%rbp), %rbx
	movq globA(%rip), %rcx
	imulq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (38) <[int][MUL], (int)DF, (int)#0, (int)globB>
	movq -56(%rbp), %rax
	movq -8(%rbp), %rbx
	movq globB(%rip), %rcx
	imulq %rbx, %rcx
	movq %rcx, -56(%rbp)
# (40) <[int][MINUS], (int)#0, (int)DF>
	movq -8(%rbp), %rax
	movq -56(%rbp), %rbx
	negq %rbx
	movq %rbx, -8(%rbp)
# (40) <[int][SUB], (int)#1, 8, (int)#0>
	movq -16(%rbp), %rax
	movq $8, %rbx
	movq -8(%rbp), %rcx
	subq %rcx, %rbx
	movq %rbx, -16(%rbp)
# (40) <[JUMP_LT], <26>, (int)DF, (int)#1>
	movq -56(%rbp), %rax
	movq -16(%rbp), %rbx
	cmpq %rbx, %rax
	jl .main.26
# (40) <[JUMP], <37>>
	jmp .main.37
.main.26:
# (41) <[JUMP_NEQ], <27>, (int)n2, 10>
	movq -40(%rbp), %rax
	movq $10, %rbx
	cmpq %rbx, %rax
	jne .main.27
# (41) <[JUMP], <30>>
	jmp .main.30
.main.27:
# (42) <[int][MUL], (int)n1, (int)n1, 1>
	movq -32(%rbp), %rax
	movq $1, %rbx
	imulq %rax, %rbx
	movq %rbx, -32(%rbp)
# (43) <[int][MOD], (int)n1, (int)n1, 10>
	movq -32(%rbp), %rax
	movq $10, %rbx
	cqo 
	idivq %rbx
	movq %rdx, -32(%rbp) # save remainder
# (44) <[int][ADD], (int)n1, (int)n1, 1>
	movq -32(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -32(%rbp)
.main.30:
# (45) <[JUMP_GT], <36>, (int)n1, 2>
	movq -32(%rbp), %rax
	movq $2, %rbx
	cmpq %rbx, %rax
	jg .main.36
.main.31:
# (45) <[JUMP_EQ], <36>, (int)n2, 100>
	movq -40(%rbp), %rax
	movq $100, %rbx
	cmpq %rbx, %rax
	je .main.36
.main.32:
# (45) <[JUMP], <33>>
	jmp .main.33
.main.33:
# (46) <[int][MINUS], (int)#0, 6>
	movq -8(%rbp), %rax
	movq $6, %rbx
	negq %rbx
	movq %rbx, -8(%rbp)
# (46) <[int][ADD], (int)DF, (int)DF, (int)#0>
	movq -56(%rbp), %rax
	movq -8(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, -56(%rbp)
# (47) <[JUMP_EQ], <35>, (int)DF, 0>
	movq -56(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	je .main.35
# (47) <[JUMP], <36>>
	jmp .main.36
.main.35:
# (48) <[int][ASSIGN], (int)DF, 101>
	movq $101, -56(%rbp)
# (48) <[JUMP], <37>>
	jmp .main.37
.main.36:
# (51) <[int][DIV], (int)n1, (int)n1, 2>
	movq -32(%rbp), %rax
	movq $2, %rbx
	cqo 
	idivq %rbx
	movq %rax, -32(%rbp) # save quotient
.main.37:
# (54) <[int][CALL], (int)#0, printf, "n1: %d, n2: %d, n3: %d\n", (int)n1, (int)n2, (int)n3>
	leaq _string_main.1(%rip), %rdi
	movq -32(%rbp), %rsi
	movq -40(%rbp), %rdx
	movq -48(%rbp), %rcx
	movq $0, %rax
	call printf
# (56) <[JUMP], <40>>
	jmp .main.40
.main.39:
# (57) <[int][MINUS], (int)#0, 1>
	movq -8(%rbp), %rax
	movq $1, %rbx
	negq %rbx
	movq %rbx, -8(%rbp)
# (57) <[int][RETURN], (int)#0>
	movq -8(%rbp), %rax
# stack size is 112
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.main.40:
# (58) <[NO_OP]>
# (59) <[int][MUL], (int)#0, (int)n1, 2>
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	movq $2, %rcx
	imulq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (59) <[int][RETURN], (int)#0>
	movq -8(%rbp), %rax
# stack size is 112
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
