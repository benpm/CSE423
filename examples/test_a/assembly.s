.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "i: %d, j: %d, k: %d\n"
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)i at -8(%rbp)
	push $0 # (int)j at -16(%rbp)
	push $0 # (int)k at -24(%rbp)
	push $0 # (int)#0 at -32(%rbp)
.main.0:
# (2) <[int][ASSIGN], (int)i, 0>
	mov -8(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (3) <[int][ASSIGN], (int)j, (int)i>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (4) <[int][ASSIGN], (int)k, 10>
	mov -24(%rbp), %rax
	mov $10, %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
# (5) <[int][ADD], (int)i, (int)i, (int)k>
	mov -8(%rbp), %rax
	mov -24(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (6) <[int][ADD], (int)j, (int)i, 7>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov $7, %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (7) <[int][ADD], (int)k, 4, 20>
	mov -24(%rbp), %rax
	mov $4, %rbx
	mov $20, %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (9) <[int][CALL], (int)#0, printf, "i: %d, j: %d, k: %d\n", (int)i, (int)j, (int)k>
	lea _string_main.0(%rip), %rdi
	mov -8(%rbp), %rsi
	mov -16(%rbp), %rdx
	mov -24(%rbp), %rcx
	mov $0, %rax
	call printf
# (11) <[int][RETURN], (int)i>
	mov -8(%rbp), %rax
# stack size is 40
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
