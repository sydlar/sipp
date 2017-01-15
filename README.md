# Enkel programmering på norsk med kompilering til C++

Dette er et eksperiment der jeg har laget et lite programmeringsspråk på norsk som skal gjøre det enkelt for mine egne barn å leke med programmering, f.eks. ved å lage enkle tekstbaserte spill. 

Kjernen i dette prosjektet er filen "sipp.hpp". Dette er et "header only"-bibliotek som i seg selv kan importeres og brukes i vanlig C++14-kode. Den intenderte bruken av "sipp.hpp" er å brukes i bakgrunnen, og la scriptet `runSippFile.sh` sørge for importering og kompilering.

Når jeg har arbeidet med dette hobbyprosjektet har jeg forfulgt flere spor, som ikke nødvendigvis har gjort prosjektet bedre eller mer barnevennlig:
- Lære seg template-programmering i C++14.
- Utforske ideen om å lage domenespesifikke språk: Siden C++ er et så avansert og fleksibelt språk, er det enkelt/nødvendig å definere språk som er hensiktsmessige i ulike situasjoner. Her har vi en situasjon der vi ønsker kontroll- og datastrukturer som egner seg for enkel programmering, med nøkkelord på norsk. (Hvis vi ser bort fra problemet med de veldig store og ubegripelige feilmeldingene, så må vi kunne si at dette fungerer fint) 

Det er antageligvis unødvendig å fortelle at dette systemet *overhodet ikke* inspirerte barna mine til å programmere. Hvis du er ute etter noe som kan inspirere barna, bør du heller satse på noe morsomt, som f.eks.  [scratch](http://scratch.mit.edu)

# Installasjon og bruk
Last ned filene, gå til katalogen, og kjør kommandoen

```
./install.sh
```

Installasjonsskriptet lager en lenke fra `~/.sipp` til den katalogen du står i, og lager en lenke  `~/bin/runSpp` til `runSippFile.sh`


Hvis du har skrevet et program i en fil `program.spp`, så kan du kjøre programmet på følgende måte:

```
runSpp program.spp
```

Dette bygger C++-kode, kompilerer koden og kjører programmet. Dersom dette ikke lykkes vil du oppleve å få tilbake en stor og ugjennomtrengelig feilmelding.

# Programmeringsspråket

Jeg har ikke laget en detaljert beskrivelse av språket, men katalogen `eksempler` inneholder eksempler som bruker de fleste aspektene ved språket. I filen `eksempler/test.spp` er det også lagt inn kommentarer som skal gjøre det litt enklere å forstå hva som foregår.

# Avhengigheter

- `sipp.hpp` er skrevet i **C++14**. Den er testet kompilert med g++5. (Se siste linje i runSippFile.sh). Systemet skal kun avhenge av standardbiblioteket i C++14.

- sipp-programmene kjøres ved hjelp av et **bash**-script som benytter **sed** og **awk**. Instalassjonsskriptet er også et **bash**-skript.
