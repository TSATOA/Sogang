TITLE FINAL_2

INCLUDE Irvine32.inc

.data
	str1 BYTE "Input: ",0
	str2 BYTE "Output: ",0
	numstr BYTE 33 DUP(0)
	numsize DWORD ?
	numsize1 DWORD ?
	numsize3 DWORD ?
	num1 DWORD ?
	num2 DWORD ?
	cnt DWORD ?
	cnt1 DWORD ?
	num3 DWORD ?
.code
main PROC
	rere:
	call Inputtwonum
	cmp numsize3,0
	je bre
	mov edx,OFFSET str2
	call WriteString
	add num1,'0'
	mov edx,num1
	mov edx,OFFSET num1
	call WriteString
	jmp rere
	bre:
	exit
main ENDP

Inputtwonum PROC
	pushad
	mov edx,OFFSET str1
	call WriteString
	mov ecx,33
	mov edx,OFFSET numstr
	call ReadString

	mov numsize,eax
	mov numsize1,eax
	mov numsize3,eax
	cmp numsize3,0
	je beee
	mov ecx,eax
	mov esi,0
	L1:
		cmp numstr[esi],' '
		je go1
		sub numstr[esi],'0'
		jmp go2
		go1:
		mov cnt,esi
		go2:
		inc esi
	Loop L1
	mov num1,0
	mov num2,0
	mov ecx,cnt
	mov cnt1,ecx
	mov esi,cnt
	mov ebx,1
	L2:
		dec cnt
		mov edx,cnt
		mov al,numstr[edx]

		mul ebx
		add num1,eax
		mov eax,ebx
		mov ebx,10
		mul ebx
		mov ebx,eax

		
	Loop L2

	
	mov eax,cnt1
	sub numsize,eax
	sub numsize,1


	mov ecx,numsize
	mov esi,numsize1
	mov ebx,1
	L3:
		dec numsize1
		mov edx,numsize1
		mov al,numstr[edx]

		mul ebx
		add num2,eax
		mov eax,ebx
		mov ebx,10
		mul ebx
		mov ebx,eax

	Loop L3
	mov eax,num2

	

	beee:
	popad
	ret
Inputtwonum ENDP

END main