.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "Error! Factorial of a negative number doesn't exist.\n"
_string_main.1: .asciz "Factorial of %d = %d\n"
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)fact
	push $0 # #0
	push $0 # (int)i
	push $0 # (int)#0
.main.0:
# (2) <[int][ASSIGN], (int)fact, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (3) <[JUMP_LT], <3>, 10, 0>
	mov $10, %rax
	mov $0, %rbx
	cmp %rbx, %rax
	jl .main.3
# (3) <[JUMP], <4>>
	jmp .main.4
.main.3:
# (4) <[CALL], #0, printf, "Error! Factorial of a negative number doesn't exist.\n">
	lea _string_main.0(%rip), %rdi
	mov $0, %rax
	call printf
.main.4:
# (6) <[int][ASSIGN], (int)i, 1>
	mov -24(%rbp), %rax
	mov $1, %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
.main.5:
# (6) <[JUMP_LE], <6>, (int)i, 10>
	mov -24(%rbp), %rax
	mov $10, %rbx
	cmp %rbx, %rax
	jle .main.6
# (6) <[JUMP], <8>>
	jmp .main.8
.main.6:
# (7) <[int][MUL], (int)fact, (int)fact, (int)i>
	mov -8(%rbp), %rax
	mov -24(%rbp), %rbx
	imul %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (6) <[int][ADD], (int)i, (int)i, 1>
	mov -24(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
# (6) <[JUMP], <5>>
	jmp .main.5
.main.8:
# (9) <[int][CALL], (int)#0, printf, "Factorial of %d = %d\n", 10, (int)fact>
	lea _string_main.1(%rip), %rdi
	mov $10, %rsi
	mov -8(%rbp), %rdx
	mov $0, %rax
	call printf
# (11) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 40
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
