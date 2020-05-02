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
	push $0 # (int)#0 at -24(%rbp)
.main.0:
# (2) <[int][ASSIGN], (int)i, 0>
	mov -8(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (3) <[int][ASSIGN], (int)j, 0>
	mov -16(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (5) <[int][ADD], (int)i, (int)i, 10>
	mov -8(%rbp), %rax
	mov $10, %rbx
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
# (9) <[int][CALL], (int)#0, printf, "i: %d, j: %d, k: %d\n", (int)i, (int)j, 24>
	lea _string_main.0(%rip), %rdi
	mov -8(%rbp), %rsi
	mov -16(%rbp), %rdx
	mov $24, %rcx
	mov $0, %rax
	call printf
# (11) <[int][RETURN], (int)i>
	mov -8(%rbp), %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
