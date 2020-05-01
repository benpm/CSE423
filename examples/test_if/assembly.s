.text
.globl main
.type main, @function
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)x
	push $0 # (int)#0
.main.0:
# (3) <[int][ASSIGN], (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (4) <[JUMP_LT], <2>, (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	cmp %rbx, %rax
	jl .main.2
# (4) <[JUMP], <8>>
	jmp .main.8
.main.2:
# (5) <[int][ADD], (int)x, (int)x, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (6) <[int][ADD], (int)#0, (int)x, (int)x>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	add %rbx, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (6) <[int][ADD], (int)x, (int)#0, 4>
	mov -8(%rbp), %rax
	mov -16(%rbp), %rbx
	mov $4, %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (7) <[JUMP_LT], <5>, (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	cmp %rbx, %rax
	jl .main.5
# (7) <[JUMP], <6>>
	jmp .main.6
.main.5:
# (8) <[int][SUB], (int)x, (int)x, 100>
	mov -8(%rbp), %rax
	mov $100, %rbx
	sub %rbx, %rax
	mov %rax, %rax
	mov %rax, -8(%rbp)
.main.6:
# (10) <[JUMP_GT], <7>, (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	cmp %rbx, %rax
	jg .main.7
# (10) <[JUMP], <8>>
	jmp .main.8
.main.7:
# (11) <[int][ADD], (int)x, (int)x, 1234>
	mov -8(%rbp), %rax
	mov $1234, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.main.8:
# (14) <[JUMP_GT], <9>, (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	cmp %rbx, %rax
	jg .main.9
# (14) <[JUMP], <15>>
	jmp .main.15
.main.9:
# (15) <[int][ADD], (int)x, (int)x, 7>
	mov -8(%rbp), %rax
	mov $7, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (16) <[int][ADD], (int)#0, (int)x, (int)x>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	add %rbx, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (16) <[int][ADD], (int)x, (int)#0, 4>
	mov -8(%rbp), %rax
	mov -16(%rbp), %rbx
	mov $4, %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (17) <[JUMP_LT], <12>, (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	cmp %rbx, %rax
	jl .main.12
# (17) <[JUMP], <13>>
	jmp .main.13
.main.12:
# (18) <[int][SUB], (int)x, (int)x, 100>
	mov -8(%rbp), %rax
	mov $100, %rbx
	sub %rbx, %rax
	mov %rax, %rax
	mov %rax, -8(%rbp)
.main.13:
# (20) <[JUMP_GT], <14>, (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	cmp %rbx, %rax
	jg .main.14
# (20) <[JUMP], <15>>
	jmp .main.15
.main.14:
# (21) <[int][ADD], (int)x, (int)x, 1234>
	mov -8(%rbp), %rax
	mov $1234, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.main.15:
# (24) <[JUMP_EQ], <16>, (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	cmp %rbx, %rax
	je .main.16
# (24) <[JUMP], <21>>
	jmp .main.21
.main.16:
# (25) <[int][ADD], (int)#0, (int)x, (int)x>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	add %rbx, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (25) <[int][ADD], (int)x, (int)#0, 4>
	mov -8(%rbp), %rax
	mov -16(%rbp), %rbx
	mov $4, %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (26) <[JUMP_LT], <18>, (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	cmp %rbx, %rax
	jl .main.18
# (26) <[JUMP], <19>>
	jmp .main.19
.main.18:
# (27) <[int][SUB], (int)x, (int)x, 100>
	mov -8(%rbp), %rax
	mov $100, %rbx
	sub %rbx, %rax
	mov %rax, %rax
	mov %rax, -8(%rbp)
.main.19:
# (29) <[JUMP_GT], <20>, (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	cmp %rbx, %rax
	jg .main.20
# (29) <[JUMP], <21>>
	jmp .main.21
.main.20:
# (30) <[int][ADD], (int)x, (int)x, 1234>
	mov -8(%rbp), %rax
	mov $1234, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.main.21:
# (34) <[int][RETURN], (int)x>
	mov -8(%rbp), %rax
# stack size is 24
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
