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
	push $0 # (int)n at -8(%rbp)
	push $0 # (int)#0 at -16(%rbp)
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
	cqo 
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
_string_optimization_congruence_class.1: .asciz "%d is not prime! 2 divides it\n"
_string_optimization_congruence_class.2: .asciz "%d is not prime! 3 divides it\n"
_string_optimization_congruence_class.3: .asciz "%d is not prime! %d divides it!\n"
_string_optimization_congruence_class.4: .asciz "%d is prime!\n"
# FUNCTION optimization_congruence_class
# param (int)i at 16(%rbp)
.text
optimization_congruence_class:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)j at -8(%rbp)
	push $0 # (int)#0 at -16(%rbp)
	push $0 # (int)#1 at -24(%rbp)
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
	cqo 
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -16(%rbp)
# (23) <[JUMP_EQ], <7>, (int)#0, 0>
	mov -16(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .optimization_congruence_class.7
# (23) <[JUMP], <9>>
	jmp .optimization_congruence_class.9
.optimization_congruence_class.7:
# (24) <[int][CALL], (int)#0, printf, "%d is not prime! 2 divides it\n", (int)i>
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
.optimization_congruence_class.9:
# (26) <[int][MOD], (int)#0, (int)i, 3>
	mov 16(%rbp), %rax
	mov -16(%rbp), %rbx
	mov $3, %rcx
	cqo 
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -16(%rbp)
# (26) <[JUMP_EQ], <10>, (int)#0, 0>
	mov -16(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .optimization_congruence_class.10
# (26) <[JUMP], <12>>
	jmp .optimization_congruence_class.12
.optimization_congruence_class.10:
# (27) <[int][CALL], (int)#0, printf, "%d is not prime! 3 divides it\n", (int)i>
	lea _string_optimization_congruence_class.2(%rip), %rdi
	mov 16(%rbp), %rsi
	mov $0, %rax
	call printf
# (28) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
# (28) <[JUMP], <20>>
	jmp .optimization_congruence_class.20
.optimization_congruence_class.12:
# (30) <[JUMP_LT], <13>, 25, (int)i>
	mov $25, %rax
	mov 16(%rbp), %rbx
	cmp %rbx, %rax
	jl .optimization_congruence_class.13
# (30) <[JUMP], <20>>
	jmp .optimization_congruence_class.20
.optimization_congruence_class.13:
# (31) <[int][MOD], (int)#0, (int)i, 5>
	mov 16(%rbp), %rax
	mov -16(%rbp), %rbx
	mov $5, %rcx
	cqo 
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -16(%rbp)
# (31) <[JUMP_EQ], <16>, (int)#0, 0>
	mov -16(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .optimization_congruence_class.16
.optimization_congruence_class.14:
# (31) <[int][MOD], (int)#1, (int)i, 7>
	mov 16(%rbp), %rax
	mov -24(%rbp), %rbx
	mov $7, %rcx
	cqo 
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -24(%rbp)
# (31) <[JUMP_EQ], <16>, (int)#1, 0>
	mov -24(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .optimization_congruence_class.16
.optimization_congruence_class.15:
# (31) <[JUMP], <18>>
	jmp .optimization_congruence_class.18
.optimization_congruence_class.16:
# (32) <[int][CALL], (int)#0, printf, "%d is not prime! %d divides it!\n", (int)i, 5>
	lea _string_optimization_congruence_class.3(%rip), %rdi
	mov 16(%rbp), %rsi
	mov $5, %rdx
	mov $0, %rax
	call printf
# (33) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.optimization_congruence_class.18:
# (35) <[int][ADD], (int)j, (int)j, 6>
	mov -8(%rbp), %rax
	mov $6, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (30) <[JUMP], <12>>
	jmp .optimization_congruence_class.12
.optimization_congruence_class.20:
# (39) <[int][CALL], (int)#0, printf, "%d is prime!\n", (int)i>
	lea _string_optimization_congruence_class.0(%rip), %rdi
	mov 16(%rbp), %rsi
	mov $0, %rax
	call printf
# (40) <[int][RETURN], 0>
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
	push $0 # (int)i at -8(%rbp)
	push $0 # (int)#0 at -16(%rbp)
.main.0:
# (45) <[int][ASSIGN], (int)i, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.main.1:
# (45) <[JUMP_LT], <2>, (int)i, 100>
	mov -8(%rbp), %rax
	mov $100, %rbx
	cmp %rbx, %rax
	jl .main.2
# (45) <[JUMP], <5>>
	jmp .main.5
.main.2:
# (46) <[int][CALL], (int)#0, brute_force_fact, (int)i>
	push -8(%rbp)
	mov -16(%rbp), %rax
	call brute_force_fact
	add $8, %rsp
	mov %rax, -16(%rbp)
# (47) <[int][CALL], (int)#0, optimization_congruence_class, (int)i>
	push -8(%rbp)
	mov -16(%rbp), %rax
	call optimization_congruence_class
	add $8, %rsp
	mov %rax, -16(%rbp)
# (45) <[int][ADD], (int)i, (int)i, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (45) <[JUMP], <1>>
	jmp .main.1
.main.5:
# (50) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 24
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
