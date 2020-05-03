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
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)n at -8(%rbp)
	pushq $0 # (int)#0 at -16(%rbp)
.brute_force_fact.0:
# (3) <[int][ASSIGN], (int)n, 2>
	movq -8(%rbp), %rax
	movq $2, %rbx
	movq %rbx, %rax
	movq %rax, -8(%rbp)
.brute_force_fact.1:
# (3) <[JUMP_LT], <2>, (int)n, (int)i>
	movq -8(%rbp), %rax
	movq 16(%rbp), %rbx
	cmpq %rbx, %rax
	jl .brute_force_fact.2
# (3) <[JUMP], <6>>
	jmp .brute_force_fact.6
.brute_force_fact.2:
# (4) <[int][MOD], (int)#0, (int)i, (int)n>
	movq 16(%rbp), %rax
	movq -16(%rbp), %rbx
	movq -8(%rbp), %rcx
	cqo 
	idivq %rcx
	movq %rdx, %rbx # save remainder
	movq %rbx, -16(%rbp)
# (4) <[JUMP_EQ], <3>, (int)#0, 0>
	movq -16(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	je .brute_force_fact.3
# (4) <[JUMP], <5>>
	jmp .brute_force_fact.5
.brute_force_fact.3:
# (5) <[int][CALL], (int)#0, printf, "%d is not prime! %d divides it!\n", (int)i, (int)n>
	leaq _string_brute_force_fact.0(%rip), %rdi
	movq 16(%rbp), %rsi
	movq -8(%rbp), %rdx
	movq $0, %rax
	call printf
# (6) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 24
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.brute_force_fact.5:
# (3) <[int][ADD], (int)n, (int)n, 1>
	movq -8(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, %rax
	movq %rax, -8(%rbp)
# (3) <[JUMP], <1>>
	jmp .brute_force_fact.1
.brute_force_fact.6:
# (10) <[int][CALL], (int)#0, printf, "%d is prime!\n", (int)i>
	leaq _string_brute_force_fact.1(%rip), %rdi
	movq 16(%rbp), %rsi
	movq $0, %rax
	call printf
# (11) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 24
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.text
.globl optimization_congruence_class
.type optimization_congruence_class, @function
.data
_string_optimization_congruence_class.0: .asciz "%d is prime!\n"
_string_optimization_congruence_class.1: .asciz "%d is not prime! 2 divides it\n"
_string_optimization_congruence_class.2: .asciz "%d is not prime! 3 divides it\n"
_string_optimization_congruence_class.3: .asciz "%d is not prime! %d divides it!\n"
_string_optimization_congruence_class.4: .asciz "%d is prime!\n"
# FUNCTION optimization_congruence_class
# param (int)i at 16(%rbp)
.text
optimization_congruence_class:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)j at -8(%rbp)
	pushq $0 # (int)#0 at -16(%rbp)
	pushq $0 # (int)#1 at -24(%rbp)
.optimization_congruence_class.0:
# (16) <[int][ASSIGN], (int)j, 5>
	movq -8(%rbp), %rax
	movq $5, %rbx
	movq %rbx, %rax
	movq %rax, -8(%rbp)
# (18) <[JUMP_EQ], <4>, (int)i, 2>
	movq 16(%rbp), %rax
	movq $2, %rbx
	cmpq %rbx, %rax
	je .optimization_congruence_class.4
.optimization_congruence_class.2:
# (18) <[JUMP_EQ], <4>, (int)i, 3>
	movq 16(%rbp), %rax
	movq $3, %rbx
	cmpq %rbx, %rax
	je .optimization_congruence_class.4
.optimization_congruence_class.3:
# (18) <[JUMP], <6>>
	jmp .optimization_congruence_class.6
.optimization_congruence_class.4:
# (19) <[int][CALL], (int)#0, printf, "%d is prime!\n", (int)i>
	leaq _string_optimization_congruence_class.0(%rip), %rdi
	movq 16(%rbp), %rsi
	movq $0, %rax
	call printf
# (20) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 32
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.optimization_congruence_class.6:
# (23) <[int][MOD], (int)#0, (int)i, 2>
	movq 16(%rbp), %rax
	movq -16(%rbp), %rbx
	movq $2, %rcx
	cqo 
	idivq %rcx
	movq %rdx, %rbx # save remainder
	movq %rbx, -16(%rbp)
# (23) <[JUMP_EQ], <7>, (int)#0, 0>
	movq -16(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	je .optimization_congruence_class.7
# (23) <[JUMP], <9>>
	jmp .optimization_congruence_class.9
.optimization_congruence_class.7:
# (24) <[int][CALL], (int)#0, printf, "%d is not prime! 2 divides it\n", (int)i>
	leaq _string_optimization_congruence_class.1(%rip), %rdi
	movq 16(%rbp), %rsi
	movq $0, %rax
	call printf
# (25) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 32
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.optimization_congruence_class.9:
# (26) <[int][MOD], (int)#0, (int)i, 3>
	movq 16(%rbp), %rax
	movq -16(%rbp), %rbx
	movq $3, %rcx
	cqo 
	idivq %rcx
	movq %rdx, %rbx # save remainder
	movq %rbx, -16(%rbp)
# (26) <[JUMP_EQ], <10>, (int)#0, 0>
	movq -16(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	je .optimization_congruence_class.10
# (26) <[JUMP], <12>>
	jmp .optimization_congruence_class.12
.optimization_congruence_class.10:
# (27) <[int][CALL], (int)#0, printf, "%d is not prime! 3 divides it\n", (int)i>
	leaq _string_optimization_congruence_class.2(%rip), %rdi
	movq 16(%rbp), %rsi
	movq $0, %rax
	call printf
# (28) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 32
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
# (28) <[JUMP], <20>>
	jmp .optimization_congruence_class.20
.optimization_congruence_class.12:
# (30) <[JUMP_LT], <13>, 25, (int)i>
	movq $25, %rax
	movq 16(%rbp), %rbx
	cmpq %rbx, %rax
	jl .optimization_congruence_class.13
# (30) <[JUMP], <20>>
	jmp .optimization_congruence_class.20
.optimization_congruence_class.13:
# (31) <[int][MOD], (int)#0, (int)i, 5>
	movq 16(%rbp), %rax
	movq -16(%rbp), %rbx
	movq $5, %rcx
	cqo 
	idivq %rcx
	movq %rdx, %rbx # save remainder
	movq %rbx, -16(%rbp)
# (31) <[JUMP_EQ], <16>, (int)#0, 0>
	movq -16(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	je .optimization_congruence_class.16
.optimization_congruence_class.14:
# (31) <[int][MOD], (int)#1, (int)i, 7>
	movq 16(%rbp), %rax
	movq -24(%rbp), %rbx
	movq $7, %rcx
	cqo 
	idivq %rcx
	movq %rdx, %rbx # save remainder
	movq %rbx, -24(%rbp)
# (31) <[JUMP_EQ], <16>, (int)#1, 0>
	movq -24(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	je .optimization_congruence_class.16
.optimization_congruence_class.15:
# (31) <[JUMP], <18>>
	jmp .optimization_congruence_class.18
.optimization_congruence_class.16:
# (32) <[int][CALL], (int)#0, printf, "%d is not prime! %d divides it!\n", (int)i, 5>
	leaq _string_optimization_congruence_class.3(%rip), %rdi
	movq 16(%rbp), %rsi
	movq $5, %rdx
	movq $0, %rax
	call printf
# (33) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 32
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.optimization_congruence_class.18:
# (35) <[int][ADD], (int)j, (int)j, 6>
	movq -8(%rbp), %rax
	movq $6, %rbx
	addq %rax, %rbx
	movq %rbx, %rax
	movq %rax, -8(%rbp)
# (30) <[JUMP], <12>>
	jmp .optimization_congruence_class.12
.optimization_congruence_class.20:
# (39) <[int][CALL], (int)#0, printf, "%d is prime!\n", (int)i>
	leaq _string_optimization_congruence_class.0(%rip), %rdi
	movq 16(%rbp), %rsi
	movq $0, %rax
	call printf
# (40) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 32
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
	pushq $0 # (int)i at -8(%rbp)
	pushq $0 # (int)#0 at -16(%rbp)
.main.0:
# (45) <[int][ASSIGN], (int)i, 1>
	movq -8(%rbp), %rax
	movq $1, %rbx
	movq %rbx, %rax
	movq %rax, -8(%rbp)
.main.1:
# (45) <[JUMP_LT], <2>, (int)i, 100>
	movq -8(%rbp), %rax
	movq $100, %rbx
	cmpq %rbx, %rax
	jl .main.2
# (45) <[JUMP], <5>>
	jmp .main.5
.main.2:
# (46) <[int][CALL], (int)#0, brute_force_fact, (int)i>
	pushq -8(%rbp)
	movq -16(%rbp), %rax
	call brute_force_fact
	addq $8, %rsp
	movq %rax, -16(%rbp)
# (47) <[int][CALL], (int)#0, optimization_congruence_class, (int)i>
	pushq -8(%rbp)
	movq -16(%rbp), %rax
	call optimization_congruence_class
	addq $8, %rsp
	movq %rax, -16(%rbp)
# (45) <[int][ADD], (int)i, (int)i, 1>
	movq -8(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, %rax
	movq %rax, -8(%rbp)
# (45) <[JUMP], <1>>
	jmp .main.1
.main.5:
# (50) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 24
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
