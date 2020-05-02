.text
.globl brute_force_fact
.type brute_force_fact, @function
.data
_string_brute_force_fact.0: .asciz "%d is not prime! %d divides it!\n"
_string_brute_force_fact.1: .asciz "%d is prime!\n"
# FUNCTION brute_force_fact
# param (int)i at 16(%rbp)
.text
brute_force_fact:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)n
	push $0 # (int)#0
.brute_force_fact.0:
# (3) <[int][ASSIGN], (int)n, 2>
	mov -8(%rbp), %rax
	mov $2, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.brute_force_fact.1:
# (3) <[JUMP_LT], <2>, (int)n, (int)i>
	mov -8(%rbp), %rax
	mov 16(%rbp), %rbx
	cmp %rbx, %rax
	jl .brute_force_fact.2
# (3) <[JUMP], <6>>
	jmp .brute_force_fact.6
.brute_force_fact.2:
# (4) <[int][MOD], (int)#0, (int)i, (int)n>
	mov 16(%rbp), %rax
	mov -16(%rbp), %rbx
	mov -8(%rbp), %rcx
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -16(%rbp)
# (4) <[JUMP_EQ], <3>, (int)#0, 0>
	mov -16(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .brute_force_fact.3
# (4) <[JUMP], <5>>
	jmp .brute_force_fact.5
.brute_force_fact.3:
# (5) <[int][CALL], (int)#0, printf, "%d is not prime! %d divides it!\n", (int)i, (int)n>
	lea _string_brute_force_fact.0(%rip), %rdi
	mov 16(%rbp), %rsi
	mov -8(%rbp), %rdx
	mov $0, %rax
	call printf
# (6) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 24
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.brute_force_fact.5:
# (3) <[int][ADD], (int)n, (int)n, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (3) <[JUMP], <1>>
	jmp .brute_force_fact.1
.brute_force_fact.6:
# (10) <[int][CALL], (int)#0, printf, "%d is prime!\n", (int)i>
	lea _string_brute_force_fact.1(%rip), %rdi
	mov 16(%rbp), %rsi
	mov $0, %rax
	call printf
# (11) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 24
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.text
.globl optimization_congruence_class
.type optimization_congruence_class, @function
.data
_string_optimization_congruence_class.0: .asciz "%d is prime!\n"
_string_optimization_congruence_class.1: .asciz "%d is not prime! 2 or 3 divides it\n"
_string_optimization_congruence_class.2: .asciz "%d is not prime! %d divides it!\n"
_string_optimization_congruence_class.3: .asciz "%d is prime!\n"
# FUNCTION optimization_congruence_class
# param (int)i at 16(%rbp)
.text
optimization_congruence_class:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)j
	push $0 # (int)#0
	push $0 # (int)#1
.optimization_congruence_class.0:
# (16) <[int][ASSIGN], (int)j, 5>
	mov -8(%rbp), %rax
	mov $5, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (18) <[JUMP_EQ], <4>, (int)i, 2>
	mov 16(%rbp), %rax
	mov $2, %rbx
	cmp %rbx, %rax
	je .optimization_congruence_class.4
.optimization_congruence_class.2:
# (18) <[JUMP_EQ], <4>, (int)i, 3>
	mov 16(%rbp), %rax
	mov $3, %rbx
	cmp %rbx, %rax
	je .optimization_congruence_class.4
.optimization_congruence_class.3:
# (18) <[JUMP], <6>>
	jmp .optimization_congruence_class.6
.optimization_congruence_class.4:
# (19) <[int][CALL], (int)#0, printf, "%d is prime!\n", (int)i>
	lea _string_optimization_congruence_class.0(%rip), %rdi
	mov 16(%rbp), %rsi
	mov $0, %rax
	call printf
# (20) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.optimization_congruence_class.6:
# (23) <[int][MOD], (int)#0, (int)i, 2>
	mov 16(%rbp), %rax
	mov -16(%rbp), %rbx
	mov $2, %rcx
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -16(%rbp)
# (23) <[JUMP_EQ], <9>, (int)#0, 0>
	mov -16(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .optimization_congruence_class.9
.optimization_congruence_class.7:
# (23) <[int][MOD], (int)#0, (int)i, 3>
	mov 16(%rbp), %rax
	mov -16(%rbp), %rbx
	mov $3, %rcx
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -16(%rbp)
# (23) <[JUMP_EQ], <9>, (int)#0, 0>
	mov -16(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .optimization_congruence_class.9
.optimization_congruence_class.8:
# (23) <[JUMP], <11>>
	jmp .optimization_congruence_class.11
.optimization_congruence_class.9:
# (24) <[int][CALL], (int)#0, printf, "%d is not prime! 2 or 3 divides it\n", (int)i>
	lea _string_optimization_congruence_class.1(%rip), %rdi
	mov 16(%rbp), %rsi
	mov $0, %rax
	call printf
# (25) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.optimization_congruence_class.11:
# (28) <[int][MUL], (int)#0, (int)j, (int)j>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	imul %rbx, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (28) <[JUMP_LT], <12>, (int)#0, (int)i>
	mov -16(%rbp), %rax
	mov 16(%rbp), %rbx
	cmp %rbx, %rax
	jl .optimization_congruence_class.12
# (28) <[JUMP], <19>>
	jmp .optimization_congruence_class.19
.optimization_congruence_class.12:
# (29) <[int][MOD], (int)#0, (int)i, (int)j>
	mov 16(%rbp), %rax
	mov -16(%rbp), %rbx
	mov -8(%rbp), %rcx
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -16(%rbp)
# (29) <[JUMP_EQ], <15>, (int)#0, 0>
	mov -16(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .optimization_congruence_class.15
.optimization_congruence_class.13:
# (29) <[int][ADD], (int)#0, (int)j, 2>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov $2, %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (29) <[int][MOD], (int)#1, (int)i, (int)#0>
	mov 16(%rbp), %rax
	mov -24(%rbp), %rbx
	mov -16(%rbp), %rcx
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -24(%rbp)
# (29) <[JUMP_EQ], <15>, (int)#1, 0>
	mov -24(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .optimization_congruence_class.15
.optimization_congruence_class.14:
# (29) <[JUMP], <17>>
	jmp .optimization_congruence_class.17
.optimization_congruence_class.15:
# (30) <[int][CALL], (int)#0, printf, "%d is not prime! %d divides it!\n", (int)i, (int)j>
	lea _string_optimization_congruence_class.2(%rip), %rdi
	mov 16(%rbp), %rsi
	mov -8(%rbp), %rdx
	mov $0, %rax
	call printf
# (31) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.optimization_congruence_class.17:
# (33) <[int][ADD], (int)j, (int)j, 6>
	mov -8(%rbp), %rax
	mov $6, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (28) <[JUMP], <11>>
	jmp .optimization_congruence_class.11
.optimization_congruence_class.19:
# (36) <[int][CALL], (int)#0, printf, "%d is prime!\n", (int)i>
	lea _string_optimization_congruence_class.0(%rip), %rdi
	mov 16(%rbp), %rsi
	mov $0, %rax
	call printf
# (37) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 32
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
	push $0 # (int)i
	push $0 # (int)#0
.main.0:
# (42) <[int][ASSIGN], (int)i, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.main.1:
# (42) <[JUMP_LT], <2>, (int)i, 100>
	mov -8(%rbp), %rax
	mov $100, %rbx
	cmp %rbx, %rax
	jl .main.2
# (42) <[JUMP], <5>>
	jmp .main.5
.main.2:
# (43) <[int][CALL], (int)#0, brute_force_fact, (int)i>
	push -8(%rbp)
	mov -16(%rbp), %rax
	call brute_force_fact
	add $8, %rsp
	mov %rax, -16(%rbp)
# (44) <[int][CALL], (int)#0, optimization_congruence_class, (int)i>
	push -8(%rbp)
	mov -16(%rbp), %rax
	call optimization_congruence_class
	add $8, %rsp
	mov %rax, -16(%rbp)
# (42) <[int][ADD], (int)i, (int)i, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (42) <[JUMP], <1>>
	jmp .main.1
.main.5:
# (47) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 24
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
