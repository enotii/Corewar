.name "Pupa"
.comment "don't Lupa"
st r1, 73
st r6, -4
ld 63, r1
ld %0, r7
zjmp %55
live %66
ldi %-5, r3, r1
sti r1, %-173, r3
add r3, r4, r3
xor r5, r3, r6
zjmp %13
ld %0, r7
zjmp %-37
xor r3, r3, r3
zjmp %-207
st r1, r1
sti r1, %7, %1
live %66
sti r2, %-74, %-60
ld %4, r4
st r2, 512
ld %48, r5
sti r1, %-90, %1
sti r1, %150, %1
sti r1, %35, %1
sti r1, %33, %1
sti r1, %31, %1
sti r1, %29, %1
sti r1, %27, %1
live %66
live %66
live %66
live %66
live %66
zjmp %-25
xor r3, r3, r3
sti r1, %7, %1
live %66
fork %-45
sti r1, %28, %1
sti r1, %21, %9
sti r1, %14, %17
sti r1, %7, %25
live %66
fork %-220
live %66
fork %-13
live %66
fork %11
live %66
zjmp %-244
live %66
ldi %-5, r3, r1
sti r1, %17, r3
add r3, r4, r3
xor r5, r3, r6
zjmp %13
ld %0, r7
zjmp %-37
xor r3, r3, r3
zjmp %1
	sti r1,%:boucle,%25
	
boucle:	live %66
	fork %:goboucle0
	live %66
	fork %:boucle
	live %66
	fork %:goboucle1
	live %66
	zjmp %:goboucle0
goboucle1:	live %66
		ldi %-5,r3,r1
		sti r1,%17,r3
		add r3,r4,r3
		xor r5,r3,r6
		zjmp %:finboucle1
		ld %0,r7
		zjmp %:goboucle1
finboucle1:	xor r3,r3,r3
		zjmp %1
