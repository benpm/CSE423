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
# param (float)V at 16(%rbp)
# param (float)XKAD at 24(%rbp)
.text
fun:
	push %rbp
	mov %rsp, %rbp
	push $0 # (float)n1
	push $0 # (float)#0
.fun.0:
# (6) <[float][ADD], (float)n1, (float)XKAD, (float)V>
	mov -8(%rbp), %rax
	mov 24(%rbp), %rbx
	mov 16(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (7) <[float][MUL], (float)#0, (float)n1, 80>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov $80, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (7) <[float][RETURN], (float)#0>
	mov -16(%rbp), %rax
# stack size is 24
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.text
.globl main
.type main, @function
.data
_string.0: .asciz "n1: %d, n2: %d, n3: %d\n"
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)n1
	push $0 # (int)n2
	push $0 # (int)n3
	push $0 # (float)DF
	push $0 # (char)G
	push $0 # (int)i
	push $0 # (int)#0
	push $0 # (int)#1
	push $0 # (int)j
	push $0 # (int)x
	push $0 # (int)x2
	push $0 # (float)#1
	push $0 # (float)#0
.main.0:
# (13) <[int][ASSIGN], (int)n1, -9>
	mov -8(%rbp), %rax
	mov $-9, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (14) <[int][ASSIGN], (int)n2, 81>
	mov -16(%rbp), %rax
	mov $81, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (15) <[int][ASSIGN], (int)n3, 144>
	mov -24(%rbp), %rax
	mov $144, %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
# (16) <[float][ASSIGN], (float)DF, 64.800003>
	mov -32(%rbp), %rax
	mov $64.800003, %rbx
	mov %rbx, %rax
	mov %rax, -32(%rbp)
# (17) <[char][ASSIGN], (char)G, 'G'>
	mov -40(%rbp), %rax
	mov $G, %rbx
	mov %rbx, %rax
	mov %rax, -40(%rbp)
# (20) <[int][ASSIGN], (int)i, 0>
	mov -48(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -48(%rbp)
.main.6:
# (20) <[int][MUL], (int)#0, (int)n2, (int)n1>
	mov -56(%rbp), %rax
	mov -16(%rbp), %rbx
	mov -8(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -56(%rbp)
# (20) <[int][DIV], (int)#1, (int)#0, 2>
	mov -56(%rbp), %rax
	mov -64(%rbp), %rbx
	mov $2, %rcx
	idiv %rcx
	mov %rax, %rbx # save quotient
	mov %rbx, -64(%rbp)
# (20) <[JUMP_LT], <7>, (int)i, (int)#1>
	mov -48(%rbp), %rax
	mov -64(%rbp), %rbx
	cmp %rbx, %rax
	jl .main.7
# (20) <[JUMP], <23>>
	jmp .main.23
.main.7:
# (22) <[JUMP], <23>>
	jmp .main.23
.main.9:
# (23) <[int][ASSIGN], (int)j, 0>
	mov -72(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -72(%rbp)
.main.10:
# (23) <[int][DIV], (int)#0, (int)n1, 2>
	mov -8(%rbp), %rax
	mov -56(%rbp), %rbx
	mov $2, %rcx
	idiv %rcx
	mov %rax, %rbx # save quotient
	mov %rbx, -56(%rbp)
# (23) <[int][ADD], (int)#1, (int)n2, (int)#0>
	mov -64(%rbp), %rax
	mov -16(%rbp), %rbx
	mov -56(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -64(%rbp)
# (23) <[JUMP_LT], <11>, (int)j, (int)#1>
	mov -72(%rbp), %rax
	mov -64(%rbp), %rbx
	cmp %rbx, %rax
	jl .main.11
# (23) <[JUMP], <22>>
	jmp .main.22
.main.11:
# (24) <[int][ASSIGN], (int)x, 0>
	mov -80(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -80(%rbp)
.main.12:
# (25) <[JUMP_LT], <15>, (int)x, (int)n2>
	mov -80(%rbp), %rax
	mov -16(%rbp), %rbx
	cmp %rbx, %rax
	jl .main.15
.main.13:
# (25) <[JUMP_GE], <21>, (int)x, (int)n2>
	mov -80(%rbp), %rax
	mov -16(%rbp), %rbx
	cmp %rbx, %rax
	jge .main.21
# (25) <[JUMP], <15>>
	jmp .main.15
.main.14:
# (25) <[JUMP], <21>>
	jmp .main.21
.main.15:
# (27) <[int][ASSIGN], (int)x2, 3>
	mov -88(%rbp), %rax
	mov $3, %rbx
	mov %rbx, %rax
	mov %rax, -88(%rbp)
# (28) <[int][ADD], (int)#0, 10, (int)x>
	mov -56(%rbp), %rax
	mov $10, %rbx
	mov -80(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -56(%rbp)
# (28) <[int][ADD], (int)x2, (int)x2, (int)#0>
	mov -88(%rbp), %rax
	mov -56(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -88(%rbp)
# (29) <[int][MINUS], (int)n2, (int)n2, (int)x>
	mov -16(%rbp), %rax
	neg %rax
	mov %rax, %rax
	mov %rax, -16(%rbp)
# (30) <[JUMP], <21>>
	jmp .main.21
.main.20:
# (25) <[JUMP], <12>>
	jmp .main.12
.main.21:
# (23) <[int][ADD], (int)j, (int)j, 1>
	mov -72(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -72(%rbp)
# (23) <[JUMP], <10>>
	jmp .main.10
.main.22:
# (20) <[int][ADD], (int)i, (int)i, 1>
	mov -48(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -48(%rbp)
# (20) <[JUMP], <6>>
	jmp .main.6
.main.23:
# (36) <[float][CALL], (float)#1, fun, (float)DF, 0.202000>
	push $0.202000
	push -32(%rbp)
	mov -96(%rbp), %rax
	call fun
	add $16, %rsp
	mov %rax, -96(%rbp)
# (36) <[float][CALL], (float)DF, fun, (float)#1, 0.900000>
	push $0.900000
	push -96(%rbp)
	mov -32(%rbp), %rax
	call fun
	add $16, %rsp
	mov %rax, -32(%rbp)
# (39) <[float][MUL], (float)#0, (float)DF, (int)globA>
	mov -104(%rbp), %rax
	mov -32(%rbp), %rbx
	mov globA(%rip), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -104(%rbp)
# (39) <[float][MUL], (float)DF, (float)#0, (int)globB>
	mov -32(%rbp), %rax
	mov -104(%rbp), %rbx
	mov globB(%rip), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -32(%rbp)
# (41) <[float][MINUS], (float)#0, (float)DF>
	mov -104(%rbp), %rax
	mov -32(%rbp), %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -104(%rbp)
# (41) <[float][SUB], (float)#1, 0.800000, (float)#0>
	mov -96(%rbp), %rax
	mov $0.800000, %rbx
	mov -104(%rbp), %rcx
	sub %rcx, %rbx
	mov %rbx, %rax
	mov %rax, -96(%rbp)
# (41) <[JUMP_LT], <26>, (float)DF, (float)#1>
	mov -32(%rbp), %rax
	mov -96(%rbp), %rbx
	cmp %rbx, %rax
	jl .main.26
# (41) <[JUMP], <43>>
	jmp .main.43
.main.26:
# (42) <[JUMP_NEQ], <27>, (int)n2, 10>
	mov -16(%rbp), %rax
	mov $10, %rbx
	cmp %rbx, %rax
	jne .main.27
# (42) <[JUMP], <31>>
	jmp .main.31
.main.27:
# (43) <[char][ASSIGN], (char)G, 'H'>
	mov -40(%rbp), %rax
	mov $H, %rbx
	mov %rbx, %rax
	mov %rax, -40(%rbp)
# (44) <[int][MUL], (int)n1, (int)n1, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	imul %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (45) <[int][MOD], (int)n1, (int)n1, 10>
	mov -8(%rbp), %rax
	mov $10, %rbx
	idiv %rbx
	mov %rdx, %rax # save remainder
	mov %rax, -8(%rbp)
# (46) <[int][ADD], (int)n1, (int)n1, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.main.31:
# (47) <[JUMP_GT], <39>, (int)n1, 2>
	mov -8(%rbp), %rax
	mov $2, %rbx
	cmp %rbx, %rax
	jg .main.39
.main.32:
# (47) <[JUMP_EQ], <36>, (char)G, 'H'>
	mov -40(%rbp), %rax
	mov $H, %rbx
	cmp %rbx, %rax
	je .main.36
.main.33:
# (47) <[JUMP_NEQ], <36>, (int)n2, 100>
	mov -16(%rbp), %rax
	mov $100, %rbx
	cmp %rbx, %rax
	jne .main.36
.main.34:
# (47) <[JUMP], <39>>
	jmp .main.39
.main.35:
# (47) <[JUMP], <36>>
	jmp .main.36
.main.36:
# (48) <[float][ADD], (float)DF, (float)DF, -0.600000>
	mov -32(%rbp), %rax
	mov $-0.600000, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -32(%rbp)
# (49) <[JUMP_EQ], <38>, (float)DF, 0.000000>
	mov -32(%rbp), %rax
	mov $0.000000, %rbx
	cmp %rbx, %rax
	je .main.38
# (49) <[JUMP], <39>>
	jmp .main.39
.main.38:
.main.39:
# (52) <[JUMP_GE], <40>, (char)G, 'H'>
	mov -40(%rbp), %rax
	mov $H, %rbx
	cmp %rbx, %rax
	jge .main.40
# (52) <[JUMP], <42>>
	jmp .main.42
.main.40:
# (53) <[int][MINUS], (int)n2, (int)n2, 16>
	mov -16(%rbp), %rax
	neg %rax
	mov %rax, %rax
	mov %rax, -16(%rbp)
# (54) <[int][MINUS], (int)n2, (int)n2, 1>
	mov -16(%rbp), %rax
	neg %rax
	mov %rax, %rax
	mov %rax, -16(%rbp)
.main.42:
# (56) <[int][DIV], (int)n1, (int)n1, 2>
	mov -8(%rbp), %rax
	mov $2, %rbx
	idiv %rbx
	mov %rax, %rax # save quotient
	mov %rax, -8(%rbp)
.main.43:
# (59) <[int][CALL], (int)#0, printf, "n1: %d, n2: %d, n3: %d\n", (int)n1, (int)n2, (int)n3>
	mov $0, %rax
	mov $3, %rsi
	lea _string.0(%rip), %rdi
	mov -8(%rbp), %rdx
	mov -16(%rbp), %rcx
	mov -24(%rbp), %r8
	call printf
# (61) <[JUMP], <46>>
	jmp .main.46
.main.45:
# (62) <[int][RETURN], -1>
	mov $-1, %rax
# stack size is 112
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.main.46:
# (63) <[NO_OP]>
# (64) <[int][MUL], (int)#0, (int)n1, 2>
	mov -56(%rbp), %rax
	mov -8(%rbp), %rbx
	mov $2, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -56(%rbp)
# (64) <[int][RETURN], (int)#0>
	mov -56(%rbp), %rax
# stack size is 112
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
