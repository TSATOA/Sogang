TITLE final_1

INCLUDE Irvine32.inc
STRMAX = 40
.data
	str1 BYTE "Input: ",0
	str2 BYTE "Output: ",0
	string BYTE STRMAX+1 DUP(0)
	stringsize DWORD ?
	cnt DWORD ?
	minesi DWORD ?
.code

main PROC
	call Inputstring
	mov edx,OFFSET str2
	call WriteString
	call Changestring
	mov edx,OFFSET string
	call WriteString
	exit
main ENDP

Inputstring PROC
	pushad
	mov edx,OFFSET str1
	call WriteString
	mov ecx,STRMAX
	mov edx,OFFSET string
	call ReadString
	mov stringsize,eax
	popad
	ret
Inputstring ENDP

Changestring PROC
	pushad
	mov esi,0
	mov ebx,0
	re1:
	movzx eax, string[esi]
	inc esi
	cmp string[esi],' '
	je gopop
	push eax

	cmp esi,stringsize
	jne re1
	je br1

	gopop:
	pop eax
	mov string[ebx],al
	inc ebx

	mov edx,OFFSET string
	call WriteString
	call Crlf

	mov minesi,esi
	dec minesi
	cmp ebx,minesi
	je printspace
	jne gopop
	
	printspace:
	mov string[ebx],' '
	inc ebx
	jmp re1

	br1:
	pop eax
	mov string[ebx],al
	inc ebx

	mov cnt,ebx
	cmp cnt,esi
	je br2
	jne br1

	br2:
	popad
	ret
Changestring ENDP

END main