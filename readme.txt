Bank Application Opis

Programski jezik: C++ sa uzetim funkcijama iz MFC klasa
Baza podataka: Microsoft Access

Aplikacija je osmišljena za sustave koje bi koristile banke odnosno zaposlenici koji rade u banci i oni bi upisivali nove korisnike,slali zahtjeve za kredite tih korisnika,gledali korisnikovo stanje na računu,stavljali novac ili ga oduzimali sa njegovog računa itd...

POKRETANJE APLIKACIJE

Kada se uđe u aplikaciju mora se unjeti NAME,SURNAME i PASSWORD od zaposlenika koji su u bazi "Bank Application Database" smješteni pod "Employees".

Npr. mogu se unjeti ovi zaposlenici:
1. NAME: LIA   SURNAME: LUNA   PASSWORD: c
2. NAME: RAYHAN   SURNAME: BOND   PASSWORD: 1234
3. NAME: NIA   SURNAME: RIVERA   PASSWORD: bank

Za ostale možete slobodno provijeriti u bazi pod "Employees".
Ova aplikacija nije osmišljena tako da zaposlenici dodaju jedni druge.Njih dodaje banka odnosno centar banke koje je zadužen za zapošljavanje novih radnika.

Nakon što se uđe u aplikaciju postoje četiri button-a i jedan edit control,lijevi button predstavlja "LOGOUT" odnosno on je zadužen za odjavljivanje zaposlenika i vraćanje na stranicu za prijvljivanje.

Nakon toga njemu sa desna slijedi button "LOAN APPLICATION" koji je zadužen za slanje zahtjeva za kredit centralnoj banci,koja kasnije odlučuje hoće li korisnik dobiti kredit ili neće.Kada se prtisne na njega otvara se DialogBox koji ispunjava zaposlenik na zahtjev korisnika i upisuje neke od slijedećih podataka:
(koliko novaca želite posuditi,kolika su vam godišnja primanja,dali imate nekretnine koje vam donose prihod...),kada se svi podaci unesu,upiše se NAME i SURNAME od koriniska i šalje se zahtjev samo ako je korisnik član banke,a ako nije zahtjev nemože biti poslan.U slučaju da je zahtijev poslan sprema se u bazu pod tablicu "LoanApplication".

Na trećem button-u "ADD USER" se dodaje korisnik nakon što se otvori DialogBox,upisuju se podaci tipa: Ime,prezime,adresa,Email,posao,itd.Zaboravio sam samo napomenuti da postoji button RESET koji briše sve podatke koji su bili upisani do sada na otvorenom DialogBox-u,isti takav button postoji i na "LOAN APPLICATION" DialogBox-u.Isto kao i kod "LOAN APPLICATION" DialogBox-a tako i ovdje,podaci se šalju i spremaju u bazu,ali pod tablicom "Users".

Četvrti button "SEARCH" služi za pretraživanje korisnika koji su u bazi podataka pod tablicom "Users",nakon što se u edit control upiše ime i prezime korisnika,npr: "JON HAMILTON" ili možete sami dodati svojeg korisnika i upisati pritiskom na "ADD USER" button.Pritiskom na button "SEARCH" otvara se nova stranica koja otvara korisnikov profil i pokazuje sve njegove podatke.Na toj stranci se može obrisati korisnik pritiskom na button "DELETE",zatim se može izaći iz korinikovog profila pritiskom na tipku "EXIT" i postoje još dvije edit control-e koje nam služe za dodavanje ili oduzimanje novaca na korisnikov račun pritiskom na button-e "INCREASE" ili "DECREASE".
