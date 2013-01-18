.macro	ISR nr
.global	isr\nr
isr\nr:
	pushl	$0
	pushl	$\nr
	jmp	isr_common_handler
.endm
.macro	IRQ nr
.global	irq\nr
irq\nr:
	pushl	$0
	pushl	$\nr
	jmp	isr_common_handler
.endm

ISR	0
ISR	1
ISR	2
ISR	3
ISR	4
ISR	5
ISR	6
ISR	7
ISR	8
ISR	9
ISR	10
ISR	11
ISR	12
ISR	13
ISR	14
ISR	15
ISR	16
ISR	17
ISR	18
ISR	19
ISR	20
ISR	21
ISR	22
ISR	23
ISR	24
ISR	25
ISR	26
ISR	27
ISR	28
ISR	29
ISR	30
ISR	31

IRQ	32
IRQ	33
IRQ	34
IRQ	35
IRQ	36
IRQ	37
IRQ	38
IRQ	39
IRQ	40
IRQ	41
IRQ	42
IRQ	43
IRQ	44
IRQ	45
IRQ	46
IRQ	47

.extern	interrupt_hadler

isr_common_handler:
	push	%ebp
	push	%edi
	push	%esi
	push	%edx
	push	%ecx
	push	%ebx
	push	%eax

	mov		$0x10,	%ax
	mov		%ax,	%es
	mov		%ax,	%es

	push	%esp
	call	interrupt_handler
	mov		%eax,	%esp

	mov		$0x23,	%ax
	mov		%ax,	%ds
	mov		%ax,	%es

	pop		%eax
	pop		%ebx
	pop		%ecx
	pop		%edx
	pop		%esi
	pop		%edi
	pop		%ebp

	add		$8,		%esp

	iret



