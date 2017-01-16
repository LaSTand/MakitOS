; hello-os
; TAB=4

		ORG		0x7c00			; origin. Loading location in memory

; Standard FAT12 Format Floppy disk decsription

		JMP		entry
		DB		0x90
		DB		"HELLOIPL"		; boot sector name(Write freely)
		DW		512				; 1 sector size(should 512byte * n)
		DB		1				; cluster size(1 sector)
		DW		1				; Reserved the num of sector
		DB		2				; the num of FAT table
		DW		224				; num of root directory entry(usually 224)
		DW		2880			; the num of all sector(should 2880)
		DB		0xf0			; Media type
		DW		9				; One FAT table's sector number(should 9)
		DW		18				; how many sector in on track
		DW		2				; head number
		DD		0				; we do not use partition -> 0
		DD		2880			; write this drive size
		DB		0,0,0x29		; ??
		DD		0xffffffff		; volume serial number
		DB		"Jhwan OS"		; Disk name
		DB		"FAT12   "		; Format name(8 byte)
		RESB	18				; anyway remain 18 byte

; Main body

entry:
		MOV		AX, 0			; init register
		MOV		SS,AX
		MOV		SP,0x7c00
		MOV		DS,AX
		MOV		ES,AX

		MOV		SI,msg
putloop:
		MOV		AL,[SI]
		ADD		SI, 1			; SI++
		CMP		AL,0
		JE		fin
		MOV		AH, 0x0e		; one char (character code)
		MOV		BX, 15			; color code
		INT		0x10			; video BIOS call
		JMP		putloop
fin:
		HLT					; halt CPU
		JMP		fin			; Endless Loop

msg:
		DB		0x0a, 0x0a		; new line(twice)
		DB		"hello, world"
		DB		0x0a			; new line
		DB		0

		RESB	0x7dfe-$			; fill in with 0x00 until 0x7dfe

		DB		0x55, 0xaa