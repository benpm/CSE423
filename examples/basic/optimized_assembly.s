.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "Foo val: %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)#0 at -8(%rbp)
.main.0:
# (3) <[JUMP_GT], <2>, 420, 10>
	movq $420, %rax
	movq $10, %rbx
	cmpq %rbx, %rax
	jg .main.2
# (3) <[JUMP], <3>>
	jmp .main.3
.main.2:
.main.3:
# (6) <[int][CALL], (int)#0, printf, "Foo val: %d\n", 19>
	leaq _string_main.0(%rip), %rdi
	movq $19, %rsi
	movq $0, %rax
	call printf
# (7) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 16
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
