.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "x: %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)x at -8(%rbp)
	pushq $0 # (int)#0 at -16(%rbp)
.main.0:
# (3) <[int][ASSIGN], (int)x, 3>
	movq $3, -8(%rbp)
# (4) <[JUMP_LT], <2>, (int)x, 3>
	movq -8(%rbp), %rax
	movq $3, %rbx
	cmpq %rbx, %rax
	jl .main.2
# (4) <[JUMP], <8>>
	jmp .main.8
.main.2:
# (5) <[int][ADD], (int)x, (int)x, 1>
	movq -8(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (6) <[int][ADD], (int)#0, (int)x, (int)x>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	addq %rbx, %rbx
	movq %rbx, -16(%rbp)
# (6) <[int][ADD], (int)x, (int)#0, 4>
	movq -8(%rbp), %rax
	movq -16(%rbp), %rbx
	movq $4, %rcx
	addq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (7) <[JUMP_LT], <5>, (int)x, 3>
	movq -8(%rbp), %rax
	movq $3, %rbx
	cmpq %rbx, %rax
	jl .main.5
# (7) <[JUMP], <6>>
	jmp .main.6
.main.5:
# (8) <[int][SUB], (int)x, (int)x, 100>
	movq -8(%rbp), %rax
	movq $100, %rbx
	subq %rbx, %rax
	movq %rax, -8(%rbp)
.main.6:
# (10) <[JUMP_GT], <7>, (int)x, 3>
	movq -8(%rbp), %rax
	movq $3, %rbx
	cmpq %rbx, %rax
	jg .main.7
# (10) <[JUMP], <8>>
	jmp .main.8
.main.7:
# (11) <[int][ADD], (int)x, (int)x, 1234>
	movq -8(%rbp), %rax
	movq $1234, %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
.main.8:
# (14) <[JUMP_GT], <9>, (int)x, 3>
	movq -8(%rbp), %rax
	movq $3, %rbx
	cmpq %rbx, %rax
	jg .main.9
# (14) <[JUMP], <15>>
	jmp .main.15
.main.9:
# (15) <[int][ADD], (int)x, (int)x, 7>
	movq -8(%rbp), %rax
	movq $7, %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (16) <[int][ADD], (int)#0, (int)x, (int)x>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	addq %rbx, %rbx
	movq %rbx, -16(%rbp)
# (16) <[int][ADD], (int)x, (int)#0, 4>
	movq -8(%rbp), %rax
	movq -16(%rbp), %rbx
	movq $4, %rcx
	addq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (17) <[JUMP_LT], <12>, (int)x, 3>
	movq -8(%rbp), %rax
	movq $3, %rbx
	cmpq %rbx, %rax
	jl .main.12
# (17) <[JUMP], <13>>
	jmp .main.13
.main.12:
# (18) <[int][SUB], (int)x, (int)x, 100>
	movq -8(%rbp), %rax
	movq $100, %rbx
	subq %rbx, %rax
	movq %rax, -8(%rbp)
.main.13:
# (20) <[JUMP_GT], <14>, (int)x, 3>
	movq -8(%rbp), %rax
	movq $3, %rbx
	cmpq %rbx, %rax
	jg .main.14
# (20) <[JUMP], <15>>
	jmp .main.15
.main.14:
# (21) <[int][ADD], (int)x, (int)x, 1234>
	movq -8(%rbp), %rax
	movq $1234, %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
.main.15:
# (24) <[JUMP_EQ], <16>, (int)x, 3>
	movq -8(%rbp), %rax
	movq $3, %rbx
	cmpq %rbx, %rax
	je .main.16
# (24) <[JUMP], <21>>
	jmp .main.21
.main.16:
# (25) <[int][ADD], (int)#0, (int)x, (int)x>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	addq %rbx, %rbx
	movq %rbx, -16(%rbp)
# (25) <[int][ADD], (int)x, (int)#0, 4>
	movq -8(%rbp), %rax
	movq -16(%rbp), %rbx
	movq $4, %rcx
	addq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (26) <[JUMP_LT], <18>, (int)x, 3>
	movq -8(%rbp), %rax
	movq $3, %rbx
	cmpq %rbx, %rax
	jl .main.18
# (26) <[JUMP], <19>>
	jmp .main.19
.main.18:
# (27) <[int][SUB], (int)x, (int)x, 100>
	movq -8(%rbp), %rax
	movq $100, %rbx
	subq %rbx, %rax
	movq %rax, -8(%rbp)
.main.19:
# (29) <[JUMP_GT], <20>, (int)x, 3>
	movq -8(%rbp), %rax
	movq $3, %rbx
	cmpq %rbx, %rax
	jg .main.20
# (29) <[JUMP], <21>>
	jmp .main.21
.main.20:
# (30) <[int][ADD], (int)x, (int)x, 1234>
	movq -8(%rbp), %rax
	movq $1234, %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
.main.21:
# (34) <[int][CALL], (int)#0, printf, "x: %d\n", (int)x>
	leaq _string_main.0(%rip), %rdi
	movq -8(%rbp), %rsi
	movq $0, %rax
	call printf
# (36) <[int][RETURN], (int)x>
	movq -8(%rbp), %rax
# stack size is 24
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
