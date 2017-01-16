; hello-os
; TAB=4

; Standared FAT12 format Floppy disk 

		DB		0xeb, 0x4e, 0x90
		DB		"HELLOIPL"	; boot sector name(Write freely)
		DW		512			; 1 sector size(should 512byte * n)
		DB		1			; cluster size(1 sector)
		DW		1			; Reserved the num of sector
		DB		2			; the num of FAT table
		DW		224			; num of root directory entry(usually 224)
		DW		2880		; the num of all sector(should 2880)
		DB		0xf0		; Media type
		DW		9			; One FAT table's sector number(should 9)
		DW		18			; how many sector in on track
		DW		2			; head number
		DD		0			; we do not use partition -> 0
		DD		2880		; write this drive size
		DB		0,0,0x29	; ??
		DD		0xffffffff	; volume serial number
		DB		"Jhwan OS"	; Disk name
		DB		"FAT12   "	; Format name(8 byte)
		RESB	18			; anyway remain 18 byte

; Main program

		DB		0xb8, 0x00, 0x00, 0x8e, 0xd0, 0xbc, 0x00, 0x7c
		DB		0x8e, 0xd8, 0x8e, 0xc0, 0xbe, 0x74, 0x7c, 0x8a
		DB		0x04, 0x83, 0xc6, 0x01, 0x3c, 0x00, 0x74, 0x09
		DB		0xb4, 0x0e, 0xbb, 0x0f, 0x00, 0xcd, 0x10, 0xeb
		DB		0xee, 0xf4, 0xeb, 0xfd

; Messege part

		DB		0x0a, 0x0a		; newline twice
		DB		"HELLO~ Jhwan!!"
		DB		0x0a			; newline
		DB		0

		RESB	0x1fe-$				; fill with 0x00 until 0x001fe

		DB		0x55, 0xaa

; below write except bootsector

		DB		0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
		RESB	4600
		DB		0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
		RESB	1469432
