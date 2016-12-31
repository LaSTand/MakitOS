
# 디폴트 동작

default :
	make.exe img

# 파일 생성 규칙

ipl.bin : ipl.nas Makefile
	nask.exe ipl.nas ipl.bin ipl.lst

helloos.img : ipl.bin Makefile
	edimg.exe   imgin:fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0   imgout:helloos.img

# 커맨드

asm :
	make.exe -r ipl.bin

img :
	make.exe -r helloos.img

run :
	make.exe img
	copy helloos.img qemu\fdimage0.bin
	make.exe -C qemu

install :
	make.exe img
	imgtol.com w a: helloos.img

clean :
	-del ipl.bin
	-del ipl.lst

src_only :
	make.exe clean
	-del helloos.img
