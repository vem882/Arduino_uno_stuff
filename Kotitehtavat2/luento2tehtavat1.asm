


Tehtävä:

Alla oleva (rivit 33-44) koodi käännettiin Arduino IDE:llä. Tuloksena oli riviltö
30 alkava ATMEGA328P prosessorin assembly koodi. 

1) Selvitä Arduinon datalehteä
hyödyntäen (kappale 31 instruction set summary) kuinka monta assemply kielistä
käskyä syntyy loop() funktion c = a+b; C-kielisestä käskystä.
lds r24, 0x0104
lds r25, 0x0105
lds r18, 0x0102
lds r19, 0x0103
add r24, r18
adc r25, r19
sts 0x0101, r25
sts 0x0100, r24
Eli 8 kpl käskyä.

2) Kommentoi riviltä 49 alkava assembly koodi aina riville 82 asti. Hae siis
   ATMEGA328P datalehdestä selitykset assembly käskyille. Huomaa, että kaikki
   rivit välillä 49-82 eivät ole assembly koodia vaan välissä on myös C-kielisiä
   osia, jotka voidaan ajatella lukemista helpottaviksi kommenteiksi. Esimerkiksi
   rivit 60-64 ovat esimerkkejä sellaisista kommenteista.

3) Kerro oma mielipiteesi (kirjoita se koodin loppuun riviltä 80 alkaen) siitä, 
miksi esim 64 bittinen prosessori on paljon 
tehokkaampi kuin Arduinon ATMega328P, joka on 8-bittinen prosessori.

Vinkki ASM: koodin tulkitsemiseen:
ASM-koodirivi (alla) tulkitaan seuraavasti:
1e6:	0e 94 00 00 	call	0	; 0x0 <__vectors>

1e6:  				kertoo ASM käskyn osoitteen ohjelmamuistissa (Flash)	
0e 94 00 00 		kertoo ASM-käskyn bitteinä. Tässä tapauksessa 32-bittinen käsky
call  0     		kertoo käskyn Mnemonic muodon eli tuon binäärikäskyn ihmiselle helpomman muodon
; 0x0 <__vectors>	Kommentti, joka selittää ASM-käskyä.			

		
--------------------------------------------------------------------------
volatile int a,b,c;

void setup() {
   a = 101;
   b = 200;
}

void loop() {
   c = a+b;
}
---------------------------------------------------------------------------

volatile int a,b,c;

void setup() {
   a = 101;
 1aa:	85 e6       	ldi	r24, 0x65	; 101
 1ac:	90 e0       	ldi	r25, 0x00	; 0
 1ae:	90 93 05 01 	sts	0x0105, r25	; 0x800105 <a+0x1>
 1b2:	80 93 04 01 	sts	0x0104, r24	; 0x800104 <a>
   b = 200;
 1b6:	88 ec       	ldi	r24, 0xC8	; 200
 1b8:	90 e0       	ldi	r25, 0x00	; 0
 1ba:	90 93 03 01 	sts	0x0103, r25	; 0x800103 <b+0x1>
 1be:	80 93 02 01 	sts	0x0102, r24	; 0x800102 <b>
	
	setup();
    
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
 1c2:	c0 e0       	ldi	r28, 0x00	; 0
 1c4:	d0 e0       	ldi	r29, 0x00	; 0
}

void loop() {
   c = a+b;
 1c6:	80 91 04 01 	lds	r24, 0x0104	; 0x800104 <a> ##Lataa 'a-muuttujan pienimmät- bitit  muistipaikasta 0x0104 rekisteriin r24
 1ca:	90 91 05 01 	lds	r25, 0x0105	; 0x800105 <a+0x1> ##Lataa 'a-muuttujan suurimmat bitit muistipaikasta 0x0105 rekisteriin r25
 1ce:	20 91 02 01 	lds	r18, 0x0102	; 0x800102 <b> ##Lataa 'b-muuttujan pienimmät-bitit  muistipaikasta 0x0102 rekisteriin r18
 1d2:	30 91 03 01 	lds	r19, 0x0103	; 0x800103 <b+0x1> ##Lataa 'b-muuttujan suurimmat bitit muistipaikasta 0x0103 rekisteriin r19
 1d6:	82 0f       	add	r24, r18 ; ## Lisää 'a':n ja 'b':n pienimmät-bitit, tulos rekisteriin r24
 1d8:	93 1f       	adc	r25, r19 ; ## Lisää 'a':n ja 'b':n suurimmat bitti kantaen (carry), tallentaa rekisteriin r25
 1da:	90 93 01 01 	sts	0x0101, r25	; 0x800101 <_edata+0x1> ## Tallentaa tuloksen suurimmat bitti muistipaikkaan 0x0101 (c+1)
 1de:	80 93 00 01 	sts	0x0100, r24	; 0x800100 <_edata> ## Tallentaa tuloksen pienimmät bitit muistipaikan 0x0100 (c)
 1e2:	20 97       	sbiw	r28, 0x00	; 0 ## Subtract immediate from word
 1e4:	81 f3       	breq	.-32     	; 0x1c6 <main+0xa2> ##Hypätään, jos tulos on 0 osoitteeseen 0x1c6 (loop)(Branch if equal )
 1e6:	0e 94 00 00 	call	0	; 0x0 <__vectors> ##Kutsutaan funktiota osoitteessa 0 (Direct subroutine call )
 1ea:	ed cf       	rjmp	.-38     	; 0x1c6 <main+0xa2> ##Relative jump osoitteeseen 0x1c6 (loopin alku)

3)
64-bittinen prosessori on huomattavasti tehokkaampi, verrattuna Arduinon 8-bittiseen. 64-bittinen kykekee käsittelemään suurempia data-määriä ja isompia kokoja yhdellä syklillä. 64-bittiset prosessorit pystyvät osoittaa enemmän mustia, kuin 8-bittiset.

